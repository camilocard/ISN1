//	Dispositivo: PIC 16F877A			Compilador:	 CCS vs3.227
//	Entorno IDE: MPLAB IDE v7.20		Simulador:	 Proteus 6.7sp3
//
//	Notas: Barrido de led's simulando la iluminacion del coche fantastico por el
//		   puerto B. Adaptacion del codigo en basic de lordlafebre
//
//				RB0 -> 1º Led
//				RB1 -> 2º Led
//				RB2 -> 3º Led
//				RB3 -> 4º Led
//				RB4 -> 5º Led
//				RB5 -> 6º Led
//				RB6 -> 7º Led
//				RB7 -> 8º Led
//		   En la variable cont se va almacenando los valores 1-2-4-8-16-32-64-128
//		   que en binario corresponden a la secuencia 00000001-00000010-00000100...
//		   son los led's a iluminar, coincidiendo con la secuencia de iluminacion
//		   del coche fantastico(version Ecuatoriana: auto fantastico)
//////////////////////////////////////////////////////////////////////////////////

#include <16f877a.h>				//pic a utilizar
#fuses XT,NOWDT,NOPROTECT,PUT,NOLVP		//ordenes para el programador
#use delay (clock=4000000)			//Fosc=4Mhz
#use standard_io(B)					//puerto B como salida

///PROGRAMA
void main(void)
{
	int i,cont;						//variables definidas
	set_tris_b(0x00);				//portb como salida
	disable_interrupts(GLOBAL);		//todas las interrupciones desactivadas

	do{								//bucle...
		cont=1;						//inicializar...

		for(i=1;i<8;i++){			//led's on derecha
			output_b(cont);			//ilumino led correspondiente
			delay_ms(100);
			cont=cont*2;
			}

		for(i=1;i<8;i++){
			output_b(cont);			//ilumino led correspondiente
			delay_ms(100);
			cont=cont/2;
			}

		}while(TRUE);				//...infinito
}

