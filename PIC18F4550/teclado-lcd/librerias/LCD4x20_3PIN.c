// flex_lcd_3_pins.c

//Modificación de Flex_lcd por Duende_Azul y Akenafab
//Trabaja con 3 pines y 74VHC164
//8-Bit Serial-In, Parallel-Out Shift Register

//La LCD se usa en modo 4bits
//Revisar diagrama de conexion Adjunto

//No esta habilitada la lectura del LCD
//RW debe ir a gnd

//Definir pines antes de llamar libreria//
//#define LCD_E     PIN_A0
//#define LCD_CK    PIN_A1   
//#define LCD_DAT   PIN_A2

//========================================
int RS_bit;
#define lcd_type 2        // 0=5x7, 1=5x10, 2=2 lines
#define lcd_line_two 0x40 // LCD RAM address for the 2nd line


int8 const LCD_INIT_STRING[4] =
{
   0x20 | (lcd_type << 2), // Func set: 4-bit, 2 lines, 5x8 dots
   0xc,                    // Display on
   1,                      // Clear display
   6                       // Increment cursor
};

BYTE lcdline;

//-------------------------------------
void lcd_send_nibble(int8 nibble, int rs_bit)
{

   int x;
   if(RS_bit==1)
      nibble=nibble|0x10;

   for(x=0;x<5;x++)
   {
      output_bit(LCD_DAT,shift_right(&nibble,1,0));
      delay_cycles(1);
      output_low(LCD_CK);
      delay_us(1);
      output_high(LCD_CK);
   }

   output_high(LCD_E);
   delay_us(2);
   output_low(LCD_E);
}

//-----------------------------------
//----------------------------------------
// Send a byte to the LCD.
void lcd_send_byte(int8 address, int8 n)
{
   //output_low(LCD_RS);
   RS_bit=0;
   delay_us(100);


   if(address)
      //output_high(LCD_RS);
      RS_bit=1;
   else
      //output_low(LCD_RS);
      RS_bit=0;

   delay_cycles(1);


   output_low(LCD_E);

   lcd_send_nibble(n >> 4,RS_bit);
   lcd_send_nibble(n & 0xf,RS_bit);
}

//----------------------------
void lcd_init(void)
{
   int8 i;

   //output_low(LCD_RS);
   RS_bit=0;

   output_low(LCD_E);

   delay_ms(20);

   for(i=0 ;i < 3; i++)
   {
      lcd_send_nibble(0x03,RS_bit);
      delay_ms(5);
   }

   lcd_send_nibble(0x02,RS_bit);

   for(i=0; i < sizeof(LCD_INIT_STRING); i++)
   {
      lcd_send_byte(0, LCD_INIT_STRING[i]);
      delay_ms(5);
   }
}

//----------------------------

void lcd_gotoxy(int8 x, int8 y)
{
   int8 address;

   switch(y) {
      case 1 : address=0x80;break;
      case 2 : address=0xc0;break;
      case 3 : address=0x94;break;
      case 4 : address=0xd4;break;
   }
   address += x-1;
   lcd_send_byte(0, 0x80 | address);
}

//-----------------------------
void lcd_putc(char c)
{
   switch(c)
   {
      case '\f':                //limpia pantalla
         lcd_send_byte(0,1);
         lcdline=1;
         delay_ms(8);
      break;

      case '\n':                //cambio de linea
         lcd_gotoxy(1,++lcdline);
      break;

      case '\b':                //retrocede 1 caracter
         lcd_send_byte(0,0x10);
      break;

      case '\c':                //on display
         lcd_send_byte(0,0x0c);
      break;

      case '\g':                
         lcd_send_byte(0,0x0f); // prende cursor y parpadea
      break;  

      case '\h':                //retrocede 1 caracter
         lcd_send_byte(0,0x0f); // prende cursor y parpadea
      break;

      default:
         lcd_send_byte(1,c);
      break;
   }
}

//------------------------------

void lcd_cursor_vb(short visible, short blink)
{ 
   lcd_send_byte(0, 0xC|(visible<<1)|blink);
} 

