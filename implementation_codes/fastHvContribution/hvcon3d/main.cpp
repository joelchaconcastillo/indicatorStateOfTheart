/* 
 * Compute all hypervolume contributions in 3-D in time O(n log n). 
 * Implementation: Michael T. M. Emmerich, Universidade do Algarve, Faro Portugal
 * Algorithm: C. M. M. Fonseca & Michael T.M. Emmerich, UAlg. Faro Portugal
 *
 * USAGE: 
 * a.exe file.dat ref1:double ref2:double ref3:double
 * file.dat format:
            #
            x1 y1 z1
            x2 y2 z2
            :
            .
            xn yn zn
            #
 * sorted by z-coordinate in descending order. For example SphericalConvex see 
 * test.dat.
 * The algorithm considers minimization.
 *
 * Includes:
 * ANSI C Library for maintainance of AVL Balanced Trees
 *  G. M. Adelson-Velskij & E. M. Landis
 *  Doklady Akad. Nauk SSSR 146 (1962), 263-266
 * (C) 2000 Daniel Nagy, Budapest University of Technology and Economics
 * Released under GNU General Public License (GPL) version 2
*/ 

#include "hycon3d.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hycon3d.h"
#include "boxlist.h"
#include "getLRlist.h"
#include "printlist.h"
#include "listPointTree.h"
#include "quicksortPZ.h"
#include "volBox.h"
#include "cmppoint.h"
#include <assert.h>
#include <time.h>
#include "myrandom.h"
#include "iostream.h"
// Reading WFG format Pareto fronts
#include "read.h"

int main(int argc, char *argv[])
{

  int i,j;
  int K=10; 
  point_avl mypoint[MAXPOINTS];
  double results[MAXPOINTS];
  double ref[3];
  
//  if (argc<4) {printf("Usage: a.exe file.dat ref1:double ref2:double ref3:double\n"); exit(0); }
//  srand(423);
//  clock_t start, stop;
//  double t = 0.0;
//  double xnorm[3];
//  FILECONTENTS *f = readFile(argv[1]);
//  int maxm=0, maxn=0;
//  for (int i = 0; i < f->nFronts; i++)
//    {if (f->fronts[i].nPoints > maxm) maxm = f->fronts[i].nPoints;
//     if (f->fronts[i].n       > maxn) maxn = f->fronts[i].n;
//    }    
//    
//  if (maxn >3) {printf("This tool can only process 3-D\n") ; exit(0);}
//  if (maxm >= MAXPOINTS) 
//    {printf("This tool can only process %i points\n", MAXPOINTS); exit(0);}
//  int Kmax = f->nFronts;
//
//  for (K=0; K < Kmax; K++)
//  {
//    int Np =f->fronts[K].nPoints;
//    for(i=0;i<Np;i++)
//    {
//         mypoint[i].x= f->fronts[K].points[i].objectives[0];
//         mypoint[i].y= f->fronts[K].points[i].objectives[1];
//         mypoint[i].z= f->fronts[K].points[i].objectives[2];
//         //printf("%.6f\t%.6f\t%.6f\n", mypoint[i].x,mypoint[i].x,mypoint[i].x);
//         mypoint[i].myindex=i;
//    }
    
//    ref[0]=atof(argv[2]); ref[1]= atof(argv[3]); ref[2]=atof(argv[4]);
//    int check;
//    /* Start timer */
//       assert((start = clock())!=-1);
//       printf("Computing ...\n");
       check =  contributions(results, mypoint, Np, ref);
	cout << check<<endl;
 //      printf("HV Contributions FE3D:\n");
 // 
 //      /* Stop timer */
 //      stop = clock();
 //      t = (double) (stop-start)/CLOCKS_PER_SEC;
 //      printf("Time: %f sec\n",t);
 //      printf("Press key for result\n");
 //      getchar();
 //      
 //      for (j=0;j<Np;j++)
 //      {
 //          printf("C(%i)=%-16.15g\n", j,results[j]);
 //      }
//  }



}
