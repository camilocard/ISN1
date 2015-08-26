//este programa on led

#include <18F4550.h>
#fuses   HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,PUT,USBDIV,PLL5,CPUDIV1,NOMCLR,VREGEN
/*       _____                                   ______,____,_______,      ,______
 SE REQUIEREN PARA TRABAJAR LA USB, LOS TRABAJAR DIRECTAMENTE
 */
#use  delay(clock=48000000)//se debe utilizar un cristal de 20Mhz
#include <stdlib.h>
//#include <mth.h>
//cargar librerias enviadas por el profesor
/* b7 b6 b5 b4 b3 b2 b1 b0
  |  |  |  |  |  |  |  |  |
  */
   
//gps bota una trama de 80 bytes
//se pueden nombrar hasta 240 registros en la memoria ram, !comprobar
//la memoria flash 32k en el pic18f4550
// todos los programas deben estar indentados
//programa principal

void secuencia()
{
   for(;;)
   {
      output_high(pin_A0);
      delay_ms(40);
      output_low(pin_A0);
      delay_ms(40);
      output_high(pin_A1);
      delay_ms(40);
      output_low(pin_A1);
      delay_ms(40);
      output_high(pin_A2);
      delay_ms(40);
      output_low(pin_A2);
      delay_ms(40);
      output_high(pin_A3);
      delay_ms(40);
      output_low(pin_A3);
      delay_ms(40);
      output_high(pin_A4);
      delay_ms(40);
      output_low(pin_A4);
      delay_ms(40);// valores desde 1 hasta 65535
   }
}
      
void main()
{
   
   //limpiar registros, probar limpiar todos los registros en assembler con =0
   //ZERO_RAM();
   //configurar pines
   //puerto A 6 pines, a0 hasta a5, por defecto son salidas
   //puerto B 6
   //puerto D 8 pines
   //puerto E 3
   //33 pines de entrada(1) y salida(0)
   set_tris_A(0x00);/* 0000 0000
   RA0   led1       PIN   02
   RA1   LED2       PIN   03
   RA2   LED3       PIN   04
   RA3   LED4       PIN   05
   RA4   LED5       PIN   06
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
   


   secuencia();
   
   //reset_cpu();//vuelva a inicio y vuelva y arranque
   
   //otra opcion con metodos que se hacen antes del main
}
