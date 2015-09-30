////////////////////////////////////////////////////////////////////////////////////
//   Notas: Se pide por lcd una clave a introducir, despues hay un menu de opciones:
//            0->Introducir password  
//            1->Cambiar clave 
//         Los caracteres * o # son fin de instruccion/accion, si estamos en cambiar clave
//         o en comprobar clave, cada vez que se pulsen dichos caracteres se terminara
//         la accion. Para introducir clave, tecleamos caracteres hasta pulsar * o # y la clave
//         ya estara almacenada. Para comprobar clave, tecleamos caracteres hasta pulsar * o #
//         y se comprobara la clave introducida con la nuestra almacenada.
//         Tener en cuenta que hay que poner la directiva NOLVP para que el pin B4 sea de salida. 
//         Se utiliza variables globales:
//            ·c-> almacena letra pulsada del keypad
//            ·limit -> longitud de clave
//            ·i -> contador
//            ·var -> 1->Clave incorrecta
//            ·clave[16] -> almacena clave(maximo 16 caracteres)
//
//   Conexiones:      B0 -> D0 LCD/Columna 1 keypad
//               B1 -> D1 LCD/Columna 2 keypad         
//               B2 -> D2 LCD/Columna 3 keypad      
//               B3 -> D3 LCD/Columna 4 keypad        
//               B4 -> D4 LCD/Fila A keypad           
//               B5 -> D5 LCD/Fila B keypad   
//               B6 -> D6 LCD/Fila C keypad 
//               B7 -> D7 LCD/Fila D keypad 
//               A0 -> RS LCD
//               A1 -> RW LCD 
//               A2 -> E  LCD 
//               A3 -> Led red 
//               A5 -> Led green             
//////////////////////////////////////////////////////////////////////////////////
#include <16f648a.h>            //pic a utilizar          
#fuses XT,NOWDT,NOPROTECT,PUT,NOLVP,NOBROWNOUT,NOMCLR      //ordenes para el programador 
#use delay (clock=4000000)         //Fosc=4Mhz
#include<kbd4x4ABCD_PROTEUS.c>               //libreria manejo keypad
#include<lcd2.c>               //libreria manejo lcd 8bits   
#use fixed_io(a_outputs=PIN_A3,PIN_A5)   
#use fast_io(B)

///DEFINICION DE FUNCIONES
void nueva_clave(void);         //funcion que cambia clave
void comprueba_clave(void);      //funcion que comprueba clave

///VARIABLES GLOBALES
char clave[16],c,limit;
signed char i;
boolean var=0;

///PROGRAMA
void main(void)
{   
   lcd_init();            //inicializa lcd
   
   delay_ms(50);         //presentacion...
   output_low(PIN_A5);
   delay_ms(50);
   output_high(PIN_A3);
   delay_ms(50);
   output_low(PIN_A3);
   lcd_putc("   VsZeNeR'05\n     Clave");
   delay_ms(1000);         //...inicial
   
   nueva_clave();         //introducimos clave
   
   for(;;){   //bucle...
      lcd_putc("\f0->Password\n1->Cambia Clave");
      do{               //espera hasta...
         c=kbd_getc();   
         }while(c==0);   //...pulsar una tecla
         
      if(c=='1')         //ve a introducir nueva clave
         nueva_clave();
      if(c=='0')         //ve a comprobar clave
         comprueba_clave();
      }      //...infinito
}
///FUNCION CAMBIAR CLAVE
void nueva_clave(void){
   lcd_putc("\fNueva clave:\n");   //presentacion
   for(i=0;i<16;i++){
      do{               //espera hasta...
         c=kbd_getc();   
         }while(c==0);   //...pulsar una tecla
         
      if(c=='*' || c=='#'){      //si se pulsa * o # se sale de la funcion
         if(i==0){            //no se sale...
            lcd_putc("\nEscribe una!!!");
            delay_ms(500);
            lcd_putc("\n              ");
            lcd_gotoxy(1,2);
            i=-1;
            continue;         //...hasta poner una clave valida
            }
         break;               //salir de funcion nueva_clave
         }
      lcd_putc("*");
      limit=i+1;               //longitud de la clave
      clave[i]=c;               //almacena clave(maximo 16 caracteres)      
      }
}
///FUNCION COMPROBAR CLAVE
void comprueba_clave(void){
   lcd_putc("\fIntroduce clave:\n");   //presentacion
   
   for(i=0;;i++){   //bucle no sale...
      do{               //espera hasta...
         c=kbd_getc();   
         }while(c==0);   //...pulsar una tecla
      
      lcd_putc("*");
      
      if(c=='#' || c=='*'){      //si se pulsa * o # se sale de la funcion
         if(i==0){            //no se sale...
            lcd_putc("\nEscribe una!!!");
            delay_ms(500);
            lcd_putc("\n              ");
            lcd_gotoxy(1,2);
            i=-1;
            continue;
            }         //...poner una clave valida
         if(i!=limit)   //para ser correcto debe tener tb longitud correcta
            var=1;
         break;         //salimos si se pulsa tecla * o #
         }
      
      if(c!=clave[i])      //comprobacion de caracteres correctos
         var=1;         //No es correcto->clave incorrecta
      }         //...hasta pulsar * o #
      
   if(var>0){      //Clave incorrecta
      lcd_putc("\fClave\nIncorrecta!");
      output_high(PIN_A3);
      delay_ms(500);
      output_low(PIN_A3);
      }
   else{         //Clave correcta
      lcd_putc("\fClave\nCorrecta!");
      output_high(PIN_A5);
      delay_ms(500);
      output_low(PIN_A5);
      }
   var=0;         //reset var
}
