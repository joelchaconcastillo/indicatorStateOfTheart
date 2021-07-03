README: 'FEHyCon3D V.1.0'

 * Compute all hypervolume contributions of a non-dominated set in 3-D in time O(n log n). 
 * Implementation: Michael T. M. Emmerich, Universidade do Algarve, Faro Portugal
 * Algorithm: C. M. M. Fonseca & Michael T.M. Emmerich, UAlg. Faro Portugal
 *  
 * 
 * Released under GNU General Public License (GPL) version 2
 * (C) by Michael Emmerich, mtemmerich@ualg.pt
 * Date: 10.10.2010 
 *
 * Michael T.M. Emmerich and Carlos M. Fonseca
 *  Computing hypervolume contributions in low
 *  dimensions: asymptotically optimal algorithm
 *  and complexity results
 * submitted for: EMO 2011, LNCS (under review)
 *
 * COMPILE:
 * g++ -O3 *.cpp
 *
 * USAGE: 
 * a.exe test.dat ref1:double ref2:double ref3:double
 * file.dat format:
            #
            x1 y1 z1
            x2 y2 z2
            :
            .
            xn yn zn
            #
 * sorted by z-coordinate in descending order. 
 *
 * Limitations/remarks to this version:
 *    -  minimization is considered. Coordinates must not exceed 
 *       reference point
 *    -  coordinates should not exceed 100000000000.0
 *    -  duplicate coordinates are not ext. tested
 *    -  20000 points is maximum
 * 
 * For example SphericalConvex see test.dat 
 * The algorithm considers minimization.
 *
 * Includes:
 * ANSI C Library for maintainance of AVL Balanced Trees
 *  G. M. Adelson-Velskij & E. M. Landis
 *  Doklady Akad. Nauk SSSR 146 (1962), 263-266
 *  (C) 2000 Daniel Nagy, Budapest University of Technology and Economics
 * Released under GNU General Public License (GPL) version 2
 *
 