#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "myrandom.h"

// Pseudo-random normal distribution
// using polar method
// Donald E Knuth.
//    The Art of Computer Programming Volume 2, Seminumerical Algotithms.
//     Addison-Wesley, third edition, 1997. 
double random_uniform_0_1(void)
{
                               return double(rand())/double(RAND_MAX);
}

double random_normal(void)
{
 double U1, U2, V1, V2;
 double S=2;
 while (S >= 1)
 {
          U1= random_uniform_0_1();
          U2= random_uniform_0_1();
          V1=2.0*U1-1.0;
          V2=2.0*U2-1.0;
          S=pow(V1,2)+pow(V2,2);
 }       
 double X1=V1*sqrt((-2.0*log(S))/S);
 return X1;
}

//main ()
//{
//     int i;
//     for(i=1; i < 100;i++)
//     {
//              printf("N(%i)=%.6f;\n",i, random_normal());
//     }
//}
