//este programa on led PIC18F4550

#include <18F4550.h>
#fuses   HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,PUT,USBDIV,PLL5,CPUDIV1,NOMCLR,VREGEN
/*       _____                                   ______,____,_______,      ,______
 SE REQUIEREN PARA TRABAJAR LA USB, LOS TRABAJAR DIRECTAMENTE
 */
 // Importante revisar esta instrucción, el tiempo no coincide.
#use  delay(clock=48000000)//se debe utilizar un cristal de 20Mhz
#include <stdlib.h>
#include <mth.h>
//cargar librerias enviadas por el profesor
/* b7 b6 b5 b4 b3 b2 b1 b0
  |  |  |  |  |  |  |  |  |
  */
  
int   dato,suma
long  clave[4]
char  
short 
float 
//gps bota una trama de 80 bytes
//se pueden nombrar hasta 240 registros en la memoria ram, !comprobar
//la memoria flash 32k en el pic18f4550
// todos los programas deben estar indentados
//programa principal

void secuencia()
{
   for(;;)
   {
      output_high(pin_B0);
      delay_ms(1000);
      output_low(pin_B0);
      delay_ms(1000);// valores desde 1 hasta 65535
   }
}
      
void main()
{
   //configurar pines
   //puerto A 6 pines, a0 hasta a5, por defecto son salidas
   //puerto B 6
   //puerto D 8 pines
   //puerto E 3
   //33 pines de entrada(1) y salida(0)
   set_tris_A(0x35);/* 0011 0101
   RA0   SW         PIN   02
   RA1   ENTRADA1   PIN   03
   RA2   
   RA3
   RA4
   RA5
   */
   set_tris_B(0x00);/*0000 0000
   RB0   LED1     PIN   02
   RB1   LED2   PIN   03
   RB2   LED3
   RB3   LED4
   RB4   LED5
   RB5   LED6
   RB6   LED7
   RB7   LED8
   */
   
   //Habilitando y deshabilitando modulos...
   setup_timer_1(T1_disabled);
   setup_timer_2(T2_disabled,0,1);
   setup_timer_3(T3_disabled);
   setup_ccp1(CCP_OFF);
   setup_ADC(ADC_OFF);
   setup_VREF(FALSE);//no voltaje de referencia
   setup_COMPARATOR(NO_ANALOGS);//
   
   //limpie los puertos A y B
   OUTPUT_A(0x00);
   OUTPUT_B(0x00);
   
   //limpiar registros, probar limpiar todos los registros en assembler con =0
   ZERO_RAM
   
   output_high(pin_B0);
   delay_ms(1000);
   output_low(pin_B0);
   delay_ms(1000);// valores desde 1 hasta 65535
   
   reset_cpu();//vuelva a inicio y vuelva y arranque
   
   //otra opcion con metodos que se hacen antes del main
}
