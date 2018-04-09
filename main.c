#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
//#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O
#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
   #use fast_io(c)
#endif

void main (void){
   setup_oscillator(OSC_16MHZ);
   //Puertos de salida
   set_tris_a(0);
   set_tris_b(0b11110000);
   set_tris_e(0b0000);
   //Puertos de entrada
   set_tris_c(1);
   set_tris_d(1);
   //Declaracion de variables
   int num1; int num2; int cont=0;
   int selec = 0;
   long resultado = 0; 
#ifdef __DEBUG_SERIAL__//Deberiamos de proteger nuestras depuraciones de esta forma o usar una macro ya protegida.
   printf("Hola Mundo\n");//Puedes usar putc o printf. Revisa la documentaci�n de CCS para ver que mas puedes hacer.
#endif

}
