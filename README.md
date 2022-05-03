# LLORAM
LLORAM, A forward and backward private oblivious RAM

Zhiqiang Wu, Zhubin Cai, Xiaoyong Tang, Yuming Xu, and Tan Deng, "A forward and backward private oblivious RAM for storage outsourcing on edge-cloud computing," Journal of Parallel and Distributed Computing (JPDC), volume: 166, 1-14, 2022.

//reference
@article{WU20221,
title = {A forward and backward private oblivious RAM for storage outsourcing on edge-cloud computing},
journal = {Journal of Parallel and Distributed Computing},
volume = {166},
pages = {1-14},
year = {2022},
issn = {0743-7315},
doi = {https://doi.org/10.1016/j.jpdc.2022.04.008},
url = {https://www.sciencedirect.com/science/article/pii/S0743731522000855},
author = {Zhiqiang Wu and Zhubin Cai and Xiaoyong Tang and Yuming Xu and Tan Deng}
}

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
