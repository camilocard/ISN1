/*
   /////////////////////////////////////////////////////////////////////////////
   //                                                                         //
   //    Dispositivo: PIC 18F4550         Compilador:  CCS vs3.227            //

         Autor: Mario Roberto Samudio
         Coautores: Audrey Monsalve y Camilo Cardenas
         
   //    Entorno IDE: PIC C Compiler      Simulador:   Ninguno                //
   //                                                                         //
   //    Notas: Contraseña con teclado matricial                              //
   //           y respuesta con luces led                                     //
   //    Notación:   Pin vacio (-----)                                        //
   //                Pulsador  (SWn)                                          //
   //                                                                         //
   //    Teclado matricial <KBD18F.c> debe estar en la carpeta de drivers     //
   //                                                                         //
   //                                                                         // 
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
#include <KBD18F.c>           // Teclado matricial
//#include <LCD4x20_3PIN.c>   // LCD

// Registros PIC18F4525
#byte FSR0H=0xfea
#byte POSTINC0=0xfee
#byte FSR0=0xfe9

/*Definiciones para: Pulsadores, leds de confirmación 
   y 4 más  para cada digito de la clave.             */
#define  SW01  PIN_D0
#define  SW02  PIN_D1

#define  LedRojo  pin_C7 // Led rojo que significa error
#define  LedVerde  pin_C6 // Led verde que significa éxito

#define  LED01 pin_D7
#define  LED02 pin_D6
#define  LED03 pin_D5
#define  LED04 pin_D4

// variables
int   clave[4]={0,0,0,0}, i=0, j=0, k=0, contador=0;
char  datom = '\0';

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

//Método que pide una contraseña
void teclado()
{
   // ContraseÃ±a definida en: *8BC
   //    clave[0] = 0x2a;// ===> *
   //    clave[1] = 0x38;// ===> 8
   //    clave[2] = 0x42;// ===> B
   //    clave[3] = 0x43;// ===> C

   // Ciclo que determina el ingreso de solo 4 digitos.
   for (i = 0; i < 4; i++)
   {
      // Condicionando el resultado de lectura para cada digito de la contraseña.
      switch(i+1)
      {
         // Caso para el digito 1.
         case 1:
            // Ciclo ajustado en 6 veces a la espera, lectura y asignación del digito.
            for (j = 0; j < 6; j++)
            {
               // Ciclo ajustado para obtener 10 iteraciones en aproximación a 1 segundo.
               for (k = 0; k < 100; k++)
               {
                  datom = kbd_getc();
                  delay_ms(10);
                  if (datom != '\0')
                  {
                     clave[i] = datom - 0x20; //quitando el ASCII clave[0] = 0x2a -0x20 = 0x0a
                     j = 6;
                     k = 100;
                  }
               }
            }

            // Si no hay inserción del digito entonces se asigna un numeral.
            if (datom == '\0')
            {
               output_high(LedRojo);
               output_high(pin_D7);
               delay_ms(2000);
               clave[i] = '#';
               output_low(LedRojo);
            }else
               output_high(pin_D7);

         break;

         // Para el caso del digito 2
         case 2:
            // Condicional que verifica si aún se mantiene presionada la tecla
            while(datom == (clave[i-1] + 0x20))// poniendo el ASCII para comprobar
            {
               datom = kbd_getc();

               // Alerta roja si mantiene la tecla presionada demasiado tiempo
               if (contador == 100)
               {
                  output_low(pin_D7);
                  output_high(LedRojo); //
                  contador = 0;   
               }
               contador++;
            }

            output_high(pin_D7);
            output_low(LedRojo);
            contador = 0;

            for (j = 0; j < 6; j++)
            {
               for (k = 0; k < 100; k++)
               {
                  datom = kbd_getc();
                  delay_ms(10);
                  if (datom != '\0')
                  {
                     swap(clave[i-1]);// Cambio de niveles
                     clave[i]= datom-0x30; // le quito el ascii
                     clave[i-1] += clave[i];                  
                     j = 6;
                     k = 100;
                  }
               }
            }

            if (datom == '\0')
            {
               output_high(LedRojo);
               output_high(pin_D6);
               delay_ms(2000);
               clave[i] = '#';
               output_low(LedRojo);
            }else
               output_high(pin_D6);
         break;

         case 3:
            while(datom == (clave[i-1] + 0x30))
            {
               datom = kbd_getc();
               if (contador == 100)
               {
                  output_low(pin_D6);
                  output_low(pin_D7);
                  output_high(LedRojo);
                  contador = 0;   
               }

               contador++;
            }

            output_high(pin_D6);
            output_high(pin_D7);
            output_low(LedRojo);
            contador = 0;

            for (j = 0; j < 6; j++)
            {
               for (k = 0; k < 100; k++)
               {
                  datom = kbd_getc();
                  delay_ms(10);
                  if (datom != '\0')
                  {
                     clave[i] = datom -0x40;
                     j = 6;
                     k = 100;
                  }
               }
            }

            if (datom == '\0')
            {
               output_high(LedRojo);
               output_high(pin_D5);
               delay_ms(2000);
               clave[i] = '#';
               output_low(LedRojo);
            }else
               output_high(pin_D5);
         break;

         case 4:
            while(datom == (clave[i-1] + 0x40))
            {
               datom = kbd_getc();
               if (contador == 100)
               {
                  output_low(pin_D7);
                  output_low(pin_D6);
                  output_low(pin_D5);
                  output_high(LedRojo);
                  contador = 0;   
               }

               contador++;
            }

            output_high(pin_D5);
            output_high(pin_D6);
            output_high(pin_D7);
            output_low(LedRojo);
            contador = 0;

            for (j = 0; j < 6; j++)
            {
               for (k = 0; k < 100; k++)
               {
                  datom = kbd_getc();
                  delay_ms(10);
                  if (datom != '\0')
                  {
                     swap(clave[i-1]);
                     clave[i] = datom -0x40;
                     clave[i-1] += clave[i];
                     j = 6;
                     k = 100;
                  }
               }
            }
            if (datom == '\0')
            {
               output_high(LedRojo);
               output_high(pin_D4);
               delay_ms(2000);
               clave[i] = '#';
               output_low(LedRojo);
            }else
               output_high(pin_D4);
         break;
      }
   }
}

// Método principal
void main()
{
   //limpiar registros, probar limpiar todos los registros en assembler con =0
   //limpiarRegistros();
   #zero_ram
   
   // Declaración de pines de puertos
   set_tris_A(0x00);/* (0000 0000)
      RA0   -----   PIN   02
      RA1   -----   PIN   03
      RA2   -----   PIN   04
      RA3   -----   PIN   05
      RA4   -----   PIN   06
      RA5   -----   PIN   07
   */

   // Configuración de pines para el teclado
   set_tris_B(0x0F);/* (0000 1111)
      RB0   COL0    PIN   40
      RB1   COL1    PIN   39
      RB2   COL2    PIN   38
      RB3   COL3    PIN   37
      RB4   Fila0   PIN   36
      RB5   Fila1   PIN   35
      RB6   Fila2   PIN   34
      RB7   Fila3   PIN   33
   */

   set_tris_C(0x00);/* (00-- -xxx)
      
      RC0   -----   PIN   15
      RC1   -----   PIN   16   
      RC2   -----   PIN   17
      RC6   LED01   PIN   25
      RC7   LED02   PIN   26
   */

   set_tris_D(0x00);/* (0000 xx00)
      RD0   SW01    PIN   19 --->Pulsador 1
      RD1   SW02    PIN   20 --->Pulsador 2
      RD2   -----   PIN   21
      RD3   -----   PIN   22
      RD4   LED03   PIN   27
      RD5   LED04   PIN   28
      RD6   LED05   PIN   29
      RD7   LED06   PIN   30
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


   //inicialización del teclado.
   kbd_init();

   // Llamando al método de inserción de contraseña.
   teclado();

   // Evaluación de la contraseña guardada (*8BC) con la contraseña ingresada
   if ((clave[0]== 0xA8) && (clave[2] == 0x23))  
   {
      output_low(pin_D7);
      output_low(pin_D6);
      output_low(pin_D5);
      output_low(pin_D4);

      // Confirmación de exito en intervalo progresivo
      for (i = 0; i < 100; ++i)
      {
         output_low(LedVerde);
         delay_ms(i);
         output_high(LedVerde);
         delay_ms(i);
      }

      delay_ms(5000);
      output_low(LedVerde);
   }else
   {
      output_low(pin_D7);
      output_low(pin_D6);
      output_low(pin_D5);
      output_low(pin_D4);

      // Confirmación del error en intervalo igual
      for (int i = 0; i < 3; ++i)
      {
         output_low(LedRojo);
         delay_ms(500);
         output_high(LedRojo);
         delay_ms(500);
      }

      delay_ms(5000);
      output_low(LedRojo);
   }

   // Variable contraseña debe quedar vacia para un nuevo intento
   clave=0;

   //vuelva a inicio y vuelva y arranque
   reset_cpu();
}