#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> /* for isspace() */
#include <bits/stdc++.h>
#include "Hypervolume.h"
using namespace std;
int main()
{
 srand(0);
 double *data, *reference;
 reference = (double *) malloc(3*sizeof(double));
 reference[0]=reference[1]=reference[2]=10;
 data = (double *) malloc(30*sizeof(double));
 for(int i = 0; i < 10; i++)
 {
   for(int j = 0; j < 3; j++)
	data[3*i+j]=rand()/(double)RAND_MAX;
 }
 unsigned int row=10, col=3;
 cout << "HV"<<endl;
 cout << hypervolume(data, reference, col, row)<<"  hv"<<endl;
 return 0;
}

