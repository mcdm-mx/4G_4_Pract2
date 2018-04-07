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
   int num1; int num2; int cont=0;
   int selec = 0;
   long resultado = 0; 
#ifdef __DEBUG_SERIAL__//Deberiamos de proteger nuestras depuraciones de esta forma o usar una macro ya protegida.
   printf("Hola Mundo\n");//Puedes usar putc o printf. Revisa la documentación de CCS para ver que mas puedes hacer.
#endif
   while(1)
      {resultado = 0;
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
                if((long)input_c() == 0 || (long)input_d() == 0 )
                   {//error 4
                      output_a(0b11111111);
                   }
                else
                   if(num1<num2)
                   {//error 1
                       for(cont=0;cont<5;cont++)
                       {
                       output_a(0b11111111);
                       delay_ms(500);
                       output_a(0b00000000);
                       delay_ms(500);
                       }
                   }
                   else
                   {
                      resultado = num1 - num2;
                      if(resultado<1)
                      {//error 2
                          for(cont=4096;cont>0;cont/2);
                          {
                             output_a(cont);
                             delay_ms(200);
                          }
                      }
                      else
                         output_a(resultado);
                   }
             break;
             case 3://Multi
                num1 = (long)input_c();
                num2 = (long)input_d();
                if((long)input_c() == 0 || (long)input_d() == 0 )
                   {//error 4
                      output_a(0b11111111);
                   }
                else
                   {
                      for(int cont = 0;cont<num2;cont++)
                         {
                            resultado = resultado + num1;
                         }
                      if(resultado>8192)
                      {//Error 3
                          for(cont=1;cont<4096;cont*2);
                          {
                             output_a(cont);
                             delay_ms(200);
                          }
                      }
                      else
                        output_a(resultado);
                   }
             break;
             case 4://Division
                num1 = (long)input_c();
                num2 = (long)input_d();
                if((long)input_c() == 0 || (long)input_d() == 0 )
                   {//Error 4
                      output_a(0b11111111);
                   }
                else
                   if(num1<num2)
                   {//Error 1
                       output_a(0b11111111);
                       delay_ms(500);
                       output_a(0b00000000);
                       delay_ms(500);
                   }
                   else
                   {
                      int temp=0;
                      while(num1 != temp)
                      {
                         temp = temp + num2 ;
                         resultado++;
                      }
                      if(resultado<1)
                      {//Error 2
                          for(cont cont=4096;cont>0;cont/2);
                          {
                             output_a(cont);
                             delay_ms(200);
                          }
                      }
                      else
                      output_a(resultado);
                   }
             break;
          }
   }
}
