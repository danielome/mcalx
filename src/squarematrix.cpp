<<<<<<< HEAD
=======
<<<<<<< HEAD
/*
 * This file is part of MCalx, a simple GPL matrix calculator
 * (c) 2015  Daniel R. Ome
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 */

=======
>>>>>>> github/master
>>>>>>> sf/master
#include "squarematrix.h"

bool is_square (const Matrix& m) {
   return (m.getRows() == m.getCols());
}

bool is_symmetric (const Matrix& m) {
   int   rows, cols;

   rows = m.getRows();
   cols = m.getCols();

   for (int _row=0; _row<rows; _row ++)
      for (int _col=0; _col<cols; _col ++)
         if ( m(_row, _col) != m(_col, _row) )
            return false;
   return true;
}

bool is_idempotent (const Matrix& m) {
   return ( m == (m * m) );
}

double trace (const Matrix& m) {
   double   res = 0;
   int      cols;

   cols = m.getCols();

   for (int _col=0; _col<cols; _col ++)
      res += m(_col, _col);

   return res;
}

double determinante (const Matrix& m) {
   Matrix   tmp;
   double   det = 1.0;
   //int      sign = 1;
   int      cols;

   cols = m.getCols();

   switch ( cols ) {
      case  1 :
         det = m(0, 0);
         break;

      case  2 :
         det = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
         break;

      case  3 :
         det = m(0,0)*(m(1,1)*m(2,2)-m(1,2)*m(2,1)) - \
               m(0,1)*(m(1,0)*m(2,2)-m(1,2)*m(2,0)) + \
               m(0,2)*(m(1,0)*m(2,1)-m(1,1)*m(2,0));
         break;

      default:
         tmp  = GaussJordan(m);
         /* Calculate determinant of the matrix */
         for (int _col=0; _col<cols; _col++)
            det = det * tmp(_col, _col);
         break;
   }

   //return (det * sign);
   return det;
}

Matrix identityMatrix(const int rc) {
   Matrix	tmp(rc, rc);
   int		col;

   for (col=0; col<rc; col ++) { tmp(col, col) = 1; }

   return tmp;
}

Matrix inverseMatrix (const Matrix& m) {
   double   **array;
   int      rows, cols;
   int      sign;
   bool     nozero;
   Matrix   tmp;

   if ( m.getRows() == m.getCols() ) {    // Accept just square matrix
      rows = cols = m.getRows();

      array= new double * [rows];
      for(int row = 0; row < rows; row ++) {
         array[row] = new double [2*cols];
         for (int col=0; col < cols; col ++) {   // Fill array with zeros ...
            array[row][col]       = m(row, col);
            array[row][cols + col]= 0;
         }
         array[row][rows + row] = 1;
      }

      cols  *= 2;
      sign  = 1;
      nozero= true;
      /************ Inicio del codigo *****************************************/

      for(int row=0; row<rows; row++) {
         if (array[row][row] == 0) {    /* Check the diagonal element */
            nozero = false;
            for (int nrow=row+1; ((nrow < rows) && !nozero); nrow ++) {
               if (array[nrow][row] != 0) {
                  double      *aux;          /* Swap two rows */

                  nozero      = true;
                  aux         = array[row];
                  array[row]  = array[nrow];
                  array[nrow] = aux;

                  sign *= -1;
               }
            }
         }

         if ( nozero == true ) {
            /* Normalize pivot row */
            for (int col=cols-1; col >=0; col --)
               array[row][col] /= array[row][row];
            /* Divide */
            for (int nrow=0; nrow<rows; nrow ++) {
               if ( nrow != row ) {
                  double factor = array[nrow][row];
                  for (int ncol=0; ncol<cols; ncol ++) {
                     array[nrow][ncol] -= factor * array[row][ncol];
                     if ( fabs(array[nrow][ncol]) < 0.000001)
                        array[nrow][ncol] = 0;
                  }
               }
            }
         } else {
            break;
         }
      } // FOR END

      /* -----------------------------------------------------------------------*/

      if ( nozero == true) {
         cols= rows;
         tmp = Matrix(rows, cols);

         for (int row=0; row < rows; row++)
            for (int col=0; col<cols; col++)
               tmp(row, col) = array[row][cols + col];
      }

      for(int row = 0; row < rows; row++){ delete [] array[row]; }
      delete [] array;
   }

   return tmp;
}

int rank(const Matrix& m) {
   Matrix   tmp;
   double   det = 1.0;
   int      cont = 0;
   int      rows, cols;

   tmp  = GaussJordan(m);
   rows = tmp.getRows();
   cols = tmp.getCols();

   for (int _row=rows-1; _row>=0; _row--) {
      for (int _col=0; _col<cols; _col++) {
         if (tmp(_row, _col) != 0) {
            cont ++;
            break;
         }
      }
   }

   return cont;
}

Matrix adjCofactor(const Matrix& m) {
   double   **array;
   int      rows, cols;
   int      sign;
   Matrix   tmp = m;
   Matrix   cof;

   if ( m.getRows() == m.getCols() ) {    // Accept just square matrix
      int   row, col;

      rows = cols = m.getRows();
      cof = Matrix(rows-1, cols-1);

      for (row=0; row<rows; row ++)
         for (col=0; col<cols; col ++) {
            int i, j, r, c;
            i = j = 0;
            for (i=0, r=0; r<rows; r ++) {
               if ( r != row ) {
                  for (j=0, c=0; c<cols; c ++) {
                     if ( c != col ) {
                        cof(i,j) = m(r, c);
                        j ++;
                     }
                  }
                  i ++;
               }
            }
            tmp(row, col) = determinante( cof ) * ( (row+col)%2 ? -1 : 1 );
         }
   }
   return tmp;
}
