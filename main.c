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
   set_tris_e(0);
   //Puertos de entrada
   set_tris_c(1);
   set_tris_d(1);
   //Declaracion de variables
   int num1;
   int num2;
   int selec = 0;
   long resultado = 0; 
#ifdef __DEBUG_SERIAL__//Deberiamos de proteger nuestras depuraciones de esta forma o usar una macro ya protegida.
   printf("Hola Mundo\n");//Puedes usar putc o printf. Revisa la documentación de CCS para ver que mas puedes hacer.
#endif
   while(1)
   {       
       if(input(pin_b4) == 1)
          selec = 1;
       if(input(pin_b5) == 1)
          selec = 2;
       if(input(pin_b6) == 1)
          selec = 3;
       if(input(pin_b7) == 1)
          selec = 4;
       switch(selec)
          {
             case 1://Suma 
                num1 = (long)input_c();
                num2 = (long)input_d();
                resultado = num1 +  num2;
                output_a(resultado);
             break;
             case 2://Resta
                num1 = (long)input_c();
                num2 = (long)input_d();
             break;
             case 3://Multi
                num1 = (long)input_c();
                num2 = (long)input_d();
             break;
             case 4://Division
                num1 = (long)input_c();
                num2 = (long)input_d();
             break;
          }
   }
}
