////////////////////////////////////////////////////////////////////////////////////
//                                   KBD.C                                        //
//               FUNCIONES PARA ESCANEO DE UN TECLADO MATRICIAL                   //
//                         4X4 HEXADECIMAL, EN EL PORTB                           //
//       kbd_init()       Debe ser invocada antes que las otras funciones.        //
//       c=lcd_getc(c)    Si há sido presionada una tecla devuelve el caracter c  //
//                  y lo salva en el char c, sino se presiona una tecla           //
//                  retorna el valor /0, esta función puede invocarse             //
//                  frecuentemente para no perder teclas pulsadas.                //    
//        NOTA: REQUIERE COLOCAR RESISTENCIAS (2.2K) EN LOS PINES DE COLUMNAS     //
//               PINES DE COLUMNAS DE RB0(COL0) A RB3(COL3))                      //
//               PINES DE FILAS DE RB4(ROW0)) A RB7(ROW3))                        // 
//                  MODIF.: ING. FRANK GIRALDO - UD                               //
////////////////////////////////////////////////////////////////////////////////////
/*////////////////////////////////////////////////////////////////////////////////// 
*    RB0 RB1 RB2 RB3   
*     |   |   |   |
*     c0  c1  c2  c3  
*   | 1 | 2 | 3 | F | r0 - RB4
*   | 4 | 5 | 6 | E | r1 - RB5
*   | 7 | 8 | 9 | D | r2 - RB6
*   | A | 0 | B | C | r3 - RB7
*
*   COLUMNS=OUTs
*   ROWS=INs
*   SE HABILITAN PULL-UP INTERNAS 
*   SE REQUIERE COLOCAR RESISTENCIAS (2.2K) EN LOS PINES DE COLUMNAS 
*
*///////////////////////////////////////////////////////////////////////////////////
//
// PORTA = 0xF80 || PORTB = 0xF81  ||  PORTC = 0xF82  || PORTD = 0xF83  || PORTE = 0xF84
#byte portkbd = 0XF81  //portkbd = PORTB

//Conexión del teclado:   (COL0 = Columna 0 es B0)
//                Bx:
#define COL0 (0 << 0)
#define COL1 (0 << 1)
#define COL2 (0 << 2)
#define COL3 (0 << 3)
#define ROW0 (1 << 4)
#define ROW1 (1 << 5)
#define ROW2 (1 << 6)
#define ROW3 (1 << 7)
#define ALL_ROWS (ROW3|ROW2|ROW1|ROW0)
#define ALL_PINS (ALL_ROWS|COL3|COL2|COL1|COL0)

char const KEYS[4][4] = {{'1','2','3','A'},
                         {'4','5','6','B'},
                         {'7','8','9','C'},
                         {'*','0','#','D'}};

#define KBD_DEBOUNCE_FACTOR 0.2
/* Modifique el valor de temporización antirrebote con (KBD_DEBOUNCE_FACTOR = n/333),
   en donde n es el número de veces por segundo en los que ud. invoca
   la función kbd_getc().  */

void kbd_init(){}

char kbd_getc( )
{
   static BYTE kbd_call_count;
   static short int kbd_down;
   static char last_key;
   static BYTE col;
   BYTE kchar;
   BYTE row;
   port_b_pullups(TRUE);
   kchar='\0';

   if(++kbd_call_count>KBD_DEBOUNCE_FACTOR)
   {
      switch (col)
      {
         case 0:
            set_tris_b(ALL_PINS&~COL0);
            portkbd=(0b1110);
         break;

         case 1:
            set_tris_b(ALL_PINS&~COL1);
            portkbd=(0b1101);
         break;

         case 2:
            set_tris_b(ALL_PINS&~COL2);
            portkbd=(0b1011);
         break;

         case 3:
            set_tris_b(ALL_PINS&~COL3);
            portkbd=(0b0111);
         break;
      }

      if(kbd_down)
      {
         if((portkbd & (ALL_ROWS))==(ALL_ROWS))
         {
            kbd_down=FALSE;
            kchar=last_key;
            last_key='\0';
         }
      }
      else
      {
         if((portkbd & (ALL_ROWS))!=(ALL_ROWS))
         {
            if((portkbd & ROW0) == 0)
               row = 0;
            else if((portkbd & ROW1) == 0)
               row = 1;
            else if((portkbd & ROW2) == 0)
               row = 2;
            else if((portkbd & ROW3) == 0)
               row = 3;

            last_key = KEYS[row][col];
            kbd_down = TRUE;
         }
         else
         {
            ++col;
            if(col==4)
               col=0;
         }
      }

      kbd_call_count=0;
   }
   
   kchar = last_key;
   set_tris_b(ALL_PINS);
   return(kchar);
}

/*char dato;
char tecla()
{
   dato='\0';
   while(dato=='\0')
   {
      dato=kbd_getc();
      delay_ms(100);
   }
return dato;
} */
