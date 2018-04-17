#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)
//#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O
#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
   #use fast_io(c)
#endif
void main (void){
   setup_oscillator(OSC_16MHZ);
   //Puertos de salida
   set_tris_a(0xc0);
   set_tris_b(0xf0);
   set_tris_e(0x08);
   //Puertos de entrada
   set_tris_c(0x3f);
   set_tris_d(0xff);
   //Declaracion de variables
   int  numeroPuertoC; 
   int  numeroPuertoD; 
   long cont=0;
   int  selec = 0;
   long resultado = 0; 
   //Inicio con todos los leds apagados.
   output_a(0b00000000);
   output_b(0b00000000);
   output_e(0b00000);
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
         numeroPuertoC = (long)input_c();
         numeroPuertoD = (long)input_d();
         switch(selec)
            {
               case 1://Suma 
                  resultado = numeroPuertoC +  numeroPuertoD;
                  output_a(resultado);
                  output_b(resultado>>6);
                  output_c(resultado>>10);
                  selec = 0;
               break;
               case 2://Resta
                  resultado = numeroPuertoC - numeroPuertoD;
                  output_a(resultado);
                  output_b(resultado>>6);
                  output_e(resultado>>10);
                  selec = 0;
               break;
               case 3://Multi
                  resultado = numeroPuertoC * numeroPuertoD;
                  output_a(resultado);
                  output_b(resultado>>6);
                  output_e(resultado>>10);
                  selec = 0 ;
               break;
               case 4://Division
                  if(numeroPuertoC < numeroPuertoD)
                     {//Error 1
                        output_a(0b11111111);
                        output_b(0b00001111);
                        output_e(0b0111);
                        delay_ms(500);
                        output_a(0b00000000);
                        output_b(0b00000000);
                        output_e(0b00000);
                        delay_ms(500);   
                     }
                    else
                      {
                         resultado = numeroPuertoC / numeroPuertoD;
                         output_a(resultado);
                         output_b(resultado>>6);
                         output_e(resultado>>10);       
                      }
                  selec = 0; 
               break;
            }
      }
}
