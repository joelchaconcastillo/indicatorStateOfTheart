#include "hycon3d.h"
#include <iostream>

int contributions(double* results, point_avl* mypoint, int k, double* ref)
{
    int i,j;
    avl_tree points;  
    double V[MAXPOINTS];  
    
    int K=k+1;
    
    // To avoid write/read outside the array bounds 
    if (K+2 >= MAXPOINTS) 
    {
      printf("The points will exceed the maximal array size. Please edit MAXPOINTS in hycon3d.h! \n"); exit(0);
    }
    
    // Normalize w.r.t. reference point
    for (i=0; i < k; i++)
    {
        mypoint[i].x=ref[0]-mypoint[i].x;
        mypoint[i].y=ref[1]-mypoint[i].y;
        mypoint[i].z=ref[2]-mypoint[i].z;
    }    

    // Boundary points for the 2-D slices
    mypoint[K-1].x=MAXDOUBLE-1.0; mypoint[K-1].y=MAXDOUBLE-1.0; mypoint[K-1].z=0;
    mypoint[K-1].myindex=K-1;
    
    mypoint[K].x = MAXDOUBLE; mypoint[K].y = 0; mypoint[K].z = MAXDOUBLE;
    mypoint[K].myindex=K;
    
    mypoint[K+1].x = 0; mypoint[K+1].y = MAXDOUBLE; mypoint[K+1].z = MAXDOUBLE;
    mypoint[K+1].myindex=K+1;
    
    //printf("\n"); printlist(mypoint,K);
    
    // Sort point array in z-coordinate
    quicksortPZ(mypoint,0,K-1);
    for (i=0; i < K; i++) {mypoint[i].myindex=i;}

    double_linked R[MAXPOINTS]; // double linked list of boxes for each point
    
    // Initialize volumes
    for (i=0;i< K; i++) {V[i]=0;}
    
    // Initialize AVL Tree
    points.compar=cmppoint;
	points.root=0;
    
    // Add first three points to AVL tree
    avl_insert(&points,(avl*)&mypoint[0]);
    avl_insert(&points,(avl*)&mypoint[K+1]);
    avl_insert(&points,(avl*)&mypoint[K]);
        
    // Initialize the first rectangle
    box r;
    r.lx=0;            r.ly=0;            r.lz=-1;
    r.ux=mypoint[0].x; r.uy=mypoint[0].y; r.uz=mypoint[0].z;   
    // Add it to the first linked list
    R[0].push_back(r);

    // Process all other points
    for (i=1; i < K; i++)
    {
        //   Find right neighbor q, left neighbor t, dominated points inner(i)
     	int idom[MAXPOINTS]; int ileft=-1; int iright=-1; int counter=0;
        double x_up=mypoint[i].x; double y_up=mypoint[i].y;
    	double right_best=MAXDOUBLE; double left_best=MAXDOUBLE;
        counter = getLRlist(idom, &ileft, &iright, (point_avl*)points.root, 
                            counter, y_up, x_up, &left_best, &right_best);
      
        // Check if the current point (index i) is not dominated
        if (y_up > mypoint[iright].y)
        {
          // Update boxes and volume of right neighbour
          box b; 
          double xleft;
        
          while (!(R[iright].empty()))
          {
            // Lop off one box
            b=(R[iright]).pop_front();
  
            if (b.ux <= mypoint[i].x)
            {
              b.lz=mypoint[i].z;
              V[iright]=V[iright]+volBox(b);
            }
            // The following box would be sliced by the xy plane through p(i)
            // It is lopped off; a new box is initiated for the right neighbor.
            else if (b.lx < mypoint[i].x && b.ux > mypoint[i].x)
            {
               b.lz=mypoint[i].z;
               V[iright]=V[iright]+volBox(b);  
               b.lx=mypoint[i].x;
               b.uz=mypoint[i].z;
               b.lz=-1.0;
               R[iright].push_front(b);
              break;    
            }
            else {R[iright].push_front(b); 
                  break;}
          }
          // Process all dominated points from left to right
          xleft=mypoint[ileft].x;
          for (j=0; j < counter;j++)
          {
            int jdom=idom[counter-j-1];
            point_avl dom=mypoint[jdom];
            //Lop off all boxes of dominated points and add volumes to the 
            //  point dom, that dominated these boxes and leaves now.
            while(!(R[jdom].empty()))
            {
              b=R[jdom].pop_front();
              b.lz=mypoint[i].z;
              V[jdom]=V[jdom]+volBox(b);
            } 
          
            // Add a box for each point that leaves to the list of mypoint[i]
            b.lx=xleft;  b.ly=dom.y;        b.lz=-1.0;
            b.ux=dom.x;  b.uy=mypoint[i].y; b.uz=mypoint[i].z;
            R[i].push_back(b);
          
            // ... xleft might be needed for the next box
            xleft = b.ux;
          
            // Delete dominated point from the AVL tree 
            avl_remove(&points,(avl*)&(mypoint[jdom]));
          }
        

          // Add a box at in the rightmost region of the dominated cone of p(i)
          // It stretches out to the left to the point where the first
          // point from the left comes that is dominated by p(i), which 
          // then will create its own box to the list of p(i)
          b.lx=xleft;        b.ly = mypoint[iright].y; b.lz=-1.0;
          b.ux=mypoint[i].x; b.uy = mypoint[i].y;      b.uz=mypoint[i].z;
          R[i].push_back(b);    
          
          //Lop off from left neighbour starting from the right
          xleft=mypoint[ileft].x;
          while (!(R[ileft].empty()))
          {
            b=(R[ileft]).pop_back();
            if(b.ly < mypoint[i].y)
            { 
              b.lz=mypoint[i].z;
              V[ileft]= V[ileft] + volBox(b);
              xleft=b.lx;  
            } 
            else
            {
                 (R[ileft]).push_back(b); 
                break;
            } 
         }
                 
         // Add a merged box to left neighbor 
         if (xleft < mypoint[ileft].x) 
         {
           b.lx=xleft;            b.ly=mypoint[i].y;      b.lz=-1.0; 
           b.ux=mypoint[ileft].x; b.uy=mypoint[ileft].y;  b.uz=mypoint[i].z;
           R[ileft].push_front(b);
         }
         
         // Add current point to AVL tree
         avl_insert(&points,(avl*)&mypoint[i]);
       }
    }    
    //PRINTCHECK("THE HYPERVOLUME CONTRIBUTIONS ARE:");
    for (i=0; i < k; i++) {results[i]=V[i];}
    return EXIT_SUCCESS;
}
