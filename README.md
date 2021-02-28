# LLORAM
LLORAM, A forward and backward private oblivious RAM

//C++ demo

            #include "LLORAM.h"


            struct Test
            {
               char buf[256];   
            }

            int main()
            {
               LLORAM<Test> oram(20);
               Test test={"hello world!"};   
               oram.write(100,test);     
               Test test2=oram.read(100)
               printf("%s \r\n",test2.buf);
            }
