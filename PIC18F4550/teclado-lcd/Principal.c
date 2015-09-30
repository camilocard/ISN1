/*
   /////////////////////////////////////////////////////////////////////////////
   //                                                                         //
   //    Dispositivo: PIC 18F4550         Compilador:  CCS vs3.227            //
   //    Entorno IDE: PIC C Compiler      Simulador:   Ninguno                //
   //                                                                         //
   //    Notas: Contraseña con teclado matricial                              //
   //    Notación:   Pin vacio (-----)                                        //
   //                Pulsador  (SWn)                                          //
   //                                                                         //
   //    Teclado matricial <KBD18F.c> debe estar en la carpeta de drivers     //
   //                                                                         //
   /////////////////////////////////////////////////////////////////////////////
      
               ASCII            Valores equitativos             HEX
   |  '1' |  '2' |  '3' |  'A' |    <=========>    | 0x31 | 0x32 | 0x33 | 0x41 |
   |  '4' |  '5' |  '6' |  'B' |    <=========>    | 0x34 | 0x35 | 0x36 | 0x42 |
   |  '7' |  '8' |  '9' |  'C' |    <=========>    | 0x37 | 0x38 | 0x39 | 0x43 |
   |  '*' |  '0' |  '#' |  'D' |    <=========>    | 0x2a | 0x30 | 0x23 | 0x44 |

*/

#include <18F4550.h>
#fuses   HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,PUT,USBDIV,PLL5,CPUDIV1,NOMCLR,VREGEN

#use  delay(clock=4000000)//se debe utilizar un cristal de 4Mhz

#include <stdlib.h>
#include <KBD18F.c>        // Teclado matricial
//#include <LCD4x20_3PIN.c>  // LCD

// Registros PIC18F4525
#byte FSR0H=0xfea
#byte POSTINC0=0xfee
#byte FSR0=0xfe9

//Definiendo el puerto que utiliza el pulsador
#define  SW01 PIN_D0
#define  SW02 PIN_D1

// variables
int   clave[4],datoe[4], b, i, contador=0;
char  datom;
long  auxsegundos, segundos;


// Limpiar todos los registros
void limpiarRegistros()
{
   #asm
      lfsr  FSR0, 0 //primer_banco_ram
      next: clrf  POSTINC0
      btfss FSR0H,3  // ultimo_banco_ram  
      bra   next
   #endasm
}

//Metodo que pide una contraseña
void teclado()
{
   auxsegundos=0;
   segundos=0;
   b=6;
   //lcd_putc('\f'); // limpiar lcd

   for ( i = 0; i < 4; i++)
   {
      do{
         datom=kbd_getc();
         delay_ms(60);// si no oprimo una tecla este metodo me adiciona cualquier cosa despues de un tiempo
         // no puede pasar de 6 segundos sino se sale del if im
         if (datom!='\0')// si orpimió tecla?
         {
            switch(i+1)
            {
               case 1:
                  clave[0]= datom-0x20; // quita el ascii
                  swap(clave[0]);// Cambio de niveles
                  //lcd_gotoxy(6,1);
                  //printf(lcd_putc,"*");
                  delay_ms(50);
               break;

               case 2:
                  clave[1]= datom-0x30; // le quito el ascii
                  clave[0]=clave[0]+clave[1];// El lcd tiene por defecto avanzar
                  //printf(lcd_putc,"*");
                  delay_ms(50);
               break;

               case 3:
                  clave[2]= datom-0x40; // ñe quite el ascii
                  swap(clave[2]);// Cambio de niveles
                  //printf(lcd_putc,"*");
                  delay_ms(50);
               break;

               case 4:
                  clave[3]= datom-0x40; // le quito el ascii
                  clave[2]=clave[2]+clave[3];// El lcd tiene por defecto avanzar
                  //printf(lcd_putc,"*");
                  delay_ms(50);
               break;
            }

            i++;
            delay_ms(500);
            auxsegundos=0;
            segundos=0;
         }

         auxsegundos++;
         
         if (auxsegundos>20)
         {
            auxsegundos=0;
            segundos++;
         }
      }while(segundos<6 && (i<4));

      clave[i]='#';
      // lcd_gotoxy(b,1);
      // printf(lcd_putc,"*");
      b++;

      //resetea los contadores para medir los segundos
      auxsegundos=0;
      segundos=0;
   }
}

// Métodos Secuencias led
void secuencia0()
{
   contador = 0;
   while(contador<8)
   {
      output_high(pin_A0);
      delay_ms(25);
      output_low(pin_A0);
      delay_ms(25);
      output_high(pin_A1);
      delay_ms(25);
      output_low(pin_A1);
      delay_ms(25);
      output_high(pin_A2);
      delay_ms(25);
      output_low(pin_A2);
      delay_ms(25);
      output_high(pin_A3);
      delay_ms(25);
      output_low(pin_A3);
      delay_ms(25);
      output_high(pin_A4);
      delay_ms(25);
      output_low(pin_A4);
      delay_ms(25);
      output_high(pin_A5);
      delay_ms(25);
      output_low(pin_A5);
      delay_ms(25);
      output_high(pin_B0);
      delay_ms(25);
      output_low(pin_B0);
      delay_ms(25);
      output_high(pin_B1);
      delay_ms(25);
      output_low(pin_B1);
      delay_ms(25);
      output_high(pin_B2);
      delay_ms(25);
      output_low(pin_B2);
      delay_ms(25);
      output_high(pin_B3);
      delay_ms(25);
      output_low(pin_B3);
      delay_ms(25);
      output_high(pin_B4);
      delay_ms(25);
      output_low(pin_B4);
      delay_ms(25);
      output_high(pin_B5);
      delay_ms(25);
      output_low(pin_B5);
      delay_ms(25);
      output_high(pin_B6);
      delay_ms(25);
      output_low(pin_B6);
      delay_ms(25);
      output_high(pin_B7);
      delay_ms(25);
      output_low(pin_B7);
      delay_ms(25);
      output_high(pin_C6);
      delay_ms(25);
      output_low(pin_C6);
      delay_ms(25);
      output_high(pin_C7);
      delay_ms(25);
      output_low(pin_C7);
      delay_ms(25);
      output_high(pin_D4);
      delay_ms(25);
      output_low(pin_D4);
      delay_ms(25);
      output_high(pin_D5);
      delay_ms(25);
      output_low(pin_D5);
      delay_ms(25);
      output_high(pin_D6);
      delay_ms(25);
      output_low(pin_D6);
      delay_ms(25);
      output_high(pin_D7);
      delay_ms(25);
      output_low(pin_D7);
      delay_ms(25);

      contador+=1;
   }
}

void secuencia1()
{
   contador = 0;
   while(contador<2)
   {

      output_high(pin_A0);
      output_high(pin_A1);
      output_high(pin_A2);
      output_high(pin_A3);
      output_high(pin_A4);
      output_high(pin_A5);
      delay_ms(50);
      output_low(pin_A0);
      output_low(pin_A1);
      output_low(pin_A2);
      output_low(pin_A3);
      output_low(pin_A4);
      output_low(pin_A5);
      delay_ms(50);

      output_high(pin_B0);
      output_high(pin_B1);
      output_high(pin_B2);
      output_high(pin_B3);
      output_high(pin_B4);
      output_high(pin_B5);
      output_high(pin_B6);
      output_high(pin_B7);
      delay_ms(50);
      output_low(pin_B0);
      output_low(pin_B1);
      output_low(pin_B2);
      output_low(pin_B3);
      output_low(pin_B4);
      output_low(pin_B5);
      output_low(pin_B6);
      output_low(pin_B7);
      delay_ms(50);
      
      output_high(pin_C6);
      output_high(pin_C7);
      delay_ms(50);
      output_low(pin_C6);
      output_low(pin_C7);
      delay_ms(50);
   
      output_high(pin_D4);
      output_high(pin_D5);
      output_high(pin_D6);
      output_high(pin_D7);
      delay_ms(50);
      output_low(pin_D4);
      output_low(pin_D5);
      output_low(pin_D6);
      output_low(pin_D7);
      delay_ms(50);

      contador += 1;
   }
}

void secuencia2()
{
   contador = 0;

   while(contador<2)
   {
      output_high(pin_A0);
      delay_ms(10);
      output_low(pin_A0);
      delay_ms(10);
      output_high(pin_A1);
      delay_ms(10);
      output_low(pin_A1);
      delay_ms(10);
      output_high(pin_A2);
      delay_ms(10);
      output_low(pin_A2);
      delay_ms(10);
      output_high(pin_A3);
      delay_ms(10);
      output_low(pin_A3);
      delay_ms(10);
      output_high(pin_A4);
      delay_ms(10);
      output_low(pin_A4);
      delay_ms(10);
      output_high(pin_A5);
      delay_ms(10);
      output_low(pin_A5);
      delay_ms(10);
      output_high(pin_B0);
      delay_ms(10);
      output_low(pin_B0);
      delay_ms(10);
      output_high(pin_B1);
      delay_ms(10);
      output_low(pin_B1);
      delay_ms(10);
      output_high(pin_B2);
      delay_ms(10);
      output_low(pin_B2);
      delay_ms(10);
      output_high(pin_B3);
      delay_ms(10);
      output_low(pin_B3);
      delay_ms(10);
      output_high(pin_B4);
      delay_ms(10);
      output_low(pin_B4);
      delay_ms(10);
      output_high(pin_B5);
      delay_ms(10);
      output_low(pin_B5);
      delay_ms(10);
      output_high(pin_B6);
      delay_ms(10);
      output_low(pin_B6);
      delay_ms(10);
      output_high(pin_B7);
      delay_ms(10);
      output_low(pin_B7);
      delay_ms(10);
      output_high(pin_C6);
      delay_ms(10);
      output_low(pin_C6);
      delay_ms(10);
      output_high(pin_C7);
      delay_ms(10);
      output_low(pin_C7);
      delay_ms(10);
      output_high(pin_D4);
      delay_ms(10);
      output_low(pin_D4);
      delay_ms(10);
      output_high(pin_D5);
      delay_ms(10);
      output_low(pin_D5);
      delay_ms(10);
      output_high(pin_D6);
      delay_ms(10);
      output_low(pin_D6);
      delay_ms(10);
      output_high(pin_D7);
      delay_ms(10);
      output_low(pin_D7);
      delay_ms(10);

      contador +=1;

   }
}

void secuencia3()
{
   output_high(pin_E0);
   delay_ms(25);
   output_low(pin_E0);
   delay_ms(25);
}

void secuencia4()
{
   contador = 0;
   while(contador<2)
   {
      output_high(pin_A1);
      delay_ms(10);
      output_low(pin_A1);
      delay_ms(10);
      output_high(pin_A3);
      delay_ms(10);
      output_low(pin_A3);
      delay_ms(10);
      output_high(pin_A5);
      delay_ms(10);
      output_low(pin_A5);
      delay_ms(10);
      output_high(pin_B1);
      delay_ms(10);
      output_low(pin_B1);
      delay_ms(10);
      output_high(pin_B3);
      delay_ms(10);
      output_low(pin_B3);
      delay_ms(10);
      output_high(pin_B5);
      delay_ms(10);
      output_low(pin_B5);
      delay_ms(10);
      output_high(pin_B7);
      delay_ms(10);
      output_low(pin_B7);
      delay_ms(10);
      output_high(pin_C7);
      delay_ms(10);
      output_low(pin_C7);
      delay_ms(10);
      output_high(pin_D5);
      delay_ms(10);
      output_low(pin_D5);
      delay_ms(10);
      output_high(pin_D7);
      delay_ms(10);
      output_low(pin_D7);
      delay_ms(10);

      contador += 1;
   }
}

// Método principal
void main()
{
   set_tris_A(0x00);/* (0000 0000)
      RA0   LED1   PIN   02
      RA1   LED2   PIN   03
      RA2   LED3   PIN   04
      RA3   LED4   PIN   05
      RA4   LED5   PIN   06
      RA5   LED6   PIN   07
   */

   set_tris_B(0x00);/* (0000 0000)
      RB0   LED7    PIN   40
      RB1   LED8    PIN   39
      RB2   LED9    PIN   38
      RB3   LED10   PIN   37
      RB4   LED11   PIN   36
      RB5   LED12   PIN   35
      RB6   LED13   PIN   34
      RB7   LED14   PIN   33
   */

   set_tris_C(0x00);/* (00-- -xxx)
      
      RC0   -----   PIN   15
      RC1   -----   PIN   16   
      RC2   -----   PIN   17
      RC6   LED15   PIN   25
      RC7   LED16   PIN   26
   */

   // Configuración de Leds 17 hasta 20 y Pulsadores 1 y 2   
   set_tris_D(0x00);/* (0000 xx00)  Para el teclado (1111 0000)set_tris_D(0xF0)
      RD0   SW01    PIN   19 --->Pulsador 1
      RD1   SW02    PIN   20 --->Pulsador 2
      RD2   -----   PIN   21
      RD3   -----   PIN   22
      RD4   LED17   PIN   27
      RD5   LED18   PIN   28
      RD6   LED19   PIN   29
      RD7   LED20   PIN   30
   */

   set_tris_E(0x00);/* bits(---- xxxx)
      RE0   -----   PIN   08 
      RE1   -----   PIN   09
      RE2   -----   PIN   10
      RE3   -----   PIN   01
   */

   //Habilitando y deshabilitando modulos...
   setup_timer_1(T1_disabled);
   setup_timer_2(T2_disabled,0,1);
   setup_timer_3(T3_disabled);
   setup_ccp1(CCP_OFF);
   setup_ADC(ADC_OFF);
   setup_VREF(FALSE);//no voltaje de referencia
   setup_COMPARATOR(NO_ANALOGS);//
   
   //limpie los puertos
   OUTPUT_A(0x00);
   OUTPUT_B(0x00);
   OUTPUT_C(0X00);
   OUTPUT_D(0X00);

   //limpiar registros, probar limpiar todos los registros en assembler con =0
   limpiarRegistros();

   /*condicional para lanzar secuencia cuando
     el pulsador esté presionado. */
   output_float(SW01);
   output_float(SW02);
   while(TRUE)
   {
      if (input_state(SW01) == 1 && input_state(SW02) == 1)
      {
         secuencia1();
      }else if (input_state(SW01) == 0 && input_state(SW02) == 1)
      {
         secuencia2();
      }else if (input_state(SW01) == 1 && input_state(SW02) == 0)
      {
         secuencia4();
      }else
      {
      }
   }


   // Contraseña definida en: *8BC
   //    clave[0] = 0x2a;// ===> *
   //    clave[1] = 0x38;// ===> 8
   //    clave[2] = 0x42;// ===> B
   //    clave[3] = 0x43;// ===> C

   // teclado();
   // if ((clave[0]== 0xa8) & (clave[2] == 0x23))  
   // {
   //     secuencia1();
   // }else
   // {
   //    /* codigo */
   // }

   //vuelva a inicio y vuelva y arranque
   reset_cpu();
}
