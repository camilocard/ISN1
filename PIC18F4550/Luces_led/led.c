//cambio explicacion Audrey
//este programa on led PIC18F4550

#include <18F4550.h>
#fuses   HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,PUT,USBDIV,PLL5,CPUDIV1,NOMCLR,VREGEN
/*       _____                                   ______,____,_______,      ,______
 SE REQUIEREN PARA TRABAJAR LA USB, LOS TRABAJAR DIRECTAMENTE
 */
#use  delay(clock=20000000)//se debe utilizar un cristal de 20Mhz
#include <stdlib.h>

// registros PIC18F4525
#byte FSR0H=0xfea
#byte POSTINC0=0xfee
#byte FSR0=0xfe9

//programa principal

void limpiarRegistros()
{
   // tambien podemos limpiar todos los registros en assembler
   #asm
      lfsr  FSR0, 0 //primer_banco_ram
      next: clrf  POSTINC0
      btfss FSR0H,3  // ultimo_banco_ram  
      bra   next
   #endasm
}

void secuencia1()
{
   for(;;)
   {
      output_high(pin_B0);
      delay_ms(1000);
      output_low(pin_B0);
      delay_ms(1000);// valores desde 1 hasta 65535
      OUTPUT_A(0xFF);
      delay_ms(1000);
      OUTPUT_A(0x00);
      delay_ms(1000);
   }
}

void secuencia2()
{
   for(;;)
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

   }
}
      
void main()
{
   set_tris_A(0x00);/* 0000 0000
   RA0   LED1   PIN   02
   RA1   LED2   PIN   03
   RA2   LED3   PIN   04
   RA3   LED4   PIN   05
   RA4   LED5   PIN   06
   RA5   LED6   PIN   07
   */
   set_tris_B(0x00);/*0000 0000
   RB0   LED7    PIN   40
   RB1   LED8    PIN   39
   RB2   LED9    PIN   38
   RB3   LED10   PIN   37
   RB4   LED11   PIN   36
   RB5   LED12   PIN   35
   RB6   LED13   PIN   34
   RB7   LED14   PIN   33
   */

   set_tris_C(0X00);/*
   RC6   LED15   PIN   25
   RC7   LED16   PIN   26
   */

   set_tris_D(0X00);/*
   RD4   LED17   PIN   27
   RD5   LED18   PIN   28
   RD6   LED19   PIN   29
   RD7   LED20   PIN   30
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
   //#ZERO_RAM 
   limpiarRegistros();

   secuencia2();
   
   reset_cpu();//vuelva a inicio y vuelva y arranque
}
