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
#include "matrix.h"

int lowerTriangle(double **array, int rows, int cols, int &sign) {

   /* Begin Gauss's elimination ... */
   int      _row, _col;
   int      diag;
   bool     nozero = true;
   double   **low;

   low = new double * [rows];

   /* Allocate lower triangle matrix */
   for (_row=0; _row<rows; _row++) {
      low[_row] = new double [cols];
      for (_col=0; _col<cols; _col++)
         low[_row][_col] = 0;
   }


   sign = 1;
   for (_row = 0; (_row < rows) && nozero; _row++) {
      if (array[_row][_row] == 0) {    /* Check the diagonal element */
         nozero = false;
         for (diag=_row+1; ((diag < rows) && !nozero); diag ++) {
            if (array[diag][_row] != 0) {
               nozero = true;

               double      *aux;          /* Swap two rows */
               aux         = array[_row];
               array[_row] = array[diag];
               array[diag] = aux;

               sign *= -1;
            }
         }
      }

      if ( nozero ) {
         low[_row][_row] = 1;
         for( int rowpiv=_row+1; rowpiv < rows; rowpiv ++) {
            double factor = array[rowpiv][_row] / array[_row][_row];
            for(_col=_row; _col < cols; _col++) {
               array[rowpiv][_col] -= array[_row][_col] * factor;
               if ( fabs(array[rowpiv][_col]) <= 0.000001) { array[rowpiv][_col] = 0; }
            }
            //low[_row][_row] = 1;
            low[rowpiv][_row] = factor;
         }
      } else {
         break;
      }
   }


   ////low[_row][_row] = 1;
   //std::cout << "Lower Triangle Matrix <<=======\n";
   //print(low, rows, cols);
   //std::cout << "=====>  <<=======\n";

   /* Borrar el arreglo */
   for (_row=0; _row<rows; _row++)
      delete [] low[_row];
   delete [] low;


   return 0;
}

Matrix GaussJordan(const Matrix& orig) {

   /* Begin Gauss's elimination ... */
   int      _row, _col;
   int      diag;
   int      rows, cols;
   bool     nozero = true;
   double   pivote;
   Matrix   tmp = orig;
   int      sign = 1;

   sign = 1;
   rows = tmp.getRows();
   cols = tmp.getCols();

   for (_row = 0; (_row < rows) && nozero; _row++) {
      if ( tmp(_row, _row) == 0 ) {    /* Check the diagonal element */
         nozero = false;
         for (diag=_row+1; ((diag < rows) && !nozero); diag ++) {
            if ( tmp(diag, _row) != 0 ) {
               nozero = true;
               tmp.swapRows(diag, _row);
               sign *= -1;
            }
         }
      }

      if ( nozero ) {
         pivote = tmp(_row, _row);
         for( int rowpiv=_row+1; rowpiv < rows; rowpiv ++) {
            double rowinit = tmp(rowpiv, _row);
            for(_col=_row; _col < cols; _col++) {
               tmp(rowpiv, _col) -= rowinit * tmp(_row, _col) / pivote;
               if ( fabs(tmp(rowpiv, _col)) <= 0.0001) { tmp(rowpiv, _col) = 0; }
            }
         }
      } else {
         break;
      }
   }

   return tmp * sign;
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> sf/master

/* NO ELIMINAR ESTA PARTE DEL CODIGO
 * CONTIENE LO NECESARIO PARA TRANSPONER LA MATRIZ
 * CALCULAR LA DETERMINANTE
 * CALCULAR EL RANGO DE LA MATRIZ
 */

//int main() {

   //double **array, **auxarray;
   //int      rows, cols;
   //int      _row, _col;
   //int      sign;
   //double   det;

   //printf("Ingresar la cantidad de filas de la matriz: ");
   //scanf("%i", &rows);
   //printf("Ingresar la cantidad de columnas de la matriz: ");
   //scanf("%i", &cols);

   //if ( (rows < 2) || (cols < 2) )
      //return(1);

   //array = new double * [rows];

   ///* Allocate matrix */
   //for (_row=0; _row<rows; _row++)
      //array[_row] = new double [cols];

   ///* Enter data on matrix */
   //for(_row=0;_row < rows;_row++){
      //for(_col=0;_col < cols;_col++){
         //printf("Los valores de la matriz [%d,%d]= ",_row + 1, _col + 1);
         //scanf("%lf",&array[_row][_col]);
      //}
   //}

   ///* Imprimir los datos */
   //print(array, rows, cols);

   ////if (rows < cols) {      /* Transform in transpose matrix */
      ////int aux;

      ////auxarray = new double * [cols];
      ////for (_col=0; _col<cols; _col++)
         ////auxarray[_col] = new double [rows];

      ////for (_row=0; _row<rows; _row++)        /* Transpose matrix */
         ////for(_col=0; _col<cols; _col++)
            ////auxarray[_col][_row] = array[_row][_col];

      ////for (_row=0; _row<rows; _row++)
         ////delete [] array[_row];
      ////delete [] array;

      ////array = auxarray;

      ////aux = rows;
      ////rows= cols;
      ////cols= aux;
   ////}

   /* OJO !!! Esta parte del codigo transpone la matriz */
   //if (rows < cols) {      /* Transform in transpose matrix */
      //int aux;

      //auxarray = new double * [cols];
      //for (_col=0; _col<cols; _col++)
         //auxarray[_col] = new double [rows];

      //for (_row=0; _row<rows; _row++) {      /* Transpose matrix */
         //for(_col=0; _col<cols; _col++)
            //auxarray[_col][_row] = array[_row][_col];
         //delete [] array[_row];
      //}

      ////for (_row=0; _row<rows; _row++)
         ////delete [] array[_row];
      //delete [] array;

      //array = auxarray;

      //aux = rows;
      //rows= cols;
      //cols= aux;
   //}

   ////upperTriangle( array, rows, cols, sign );
   //lowerTriangle( array, rows, cols, sign );

   ///* Calculate determinant of the matrix */
   //if (rows == cols) {
      //det = 1.0;
      //for (_col=0; _col<cols; _col++) {
         //det = det * array[_col][_col];
      //}
      //det = det * sign;
      //printf("%f\n", det);

      //std::cout << std::setw(15) << "Determinante: " << det << std::endl;
   //}

   ///* Imprimir los datos */
   //print(array, rows, cols);

   //int cont=0;
   //for (_row=rows-1; _row>=0; _row--) {
      //for (_col=0; _col<cols; _col++) {
         //if (array[_row][_col] != 0) {
            //cont ++;
            //break;
         //}
      //}
   //}
   //printf("Rango de la matriz: %i\n", cont);

   ///* Borrar el arreglo */
   //for (_row=0; _row<rows; _row++)
      //delete [] array[_row];
   //delete [] array;


   //return 0;
//}
<<<<<<< HEAD
=======
>>>>>>> github/master
>>>>>>> sf/master
