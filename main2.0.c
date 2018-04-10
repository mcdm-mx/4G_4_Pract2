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
   //Codigo
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
         //Obtencion del numero de entrada
         NumeroPuertoC = (long)input_c();
         NumeroPuertoD = (long)input_d();
      }
}
