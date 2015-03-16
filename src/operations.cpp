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

#include <FL/fl_ask.H>

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

#include "matrix.h"
#include "operations.h"
#include "sheet.h"
#include "squarematrix.h"
#include "transpose.h"

using namespace std;

/* Internal functions */
/* ------------------------ */
Matrix  Sheet2Matrix(Sheet *S) {
   int      mrows = S->rows();
   int      mcols = S->cols();
   Matrix   tmp = Matrix(mrows, mcols);

   for (int row=0; row<mrows; row++)
      for (int col=0; col<mcols; col++)
         tmp(row, col) = S->getValue(row, col);

   return tmp;
}

/* ------------------------ */
void Matrix2Sheet(Matrix src, Sheet* C) {
   int   rows = src.getRows();
   int   cols = src.getCols();

   for(int row = 0; row < rows; row++) {
      for (int col=0; col<cols; col++)
         C->setValue(row, col, src(row, col));
   }

   C->rows( src.getRows() );
   C->cols( src.getCols() );
}
/* Internal functions */

void basicOp (Sheet* sA, Sheet* sB, Sheet* sC, typeOp oper) {
   int     rowA, colA;
   int     rowB, colB;

   rowA = sA->rows(); colA = sA->cols();
   rowB = sB->rows(); colB = sB->cols();

   /* Only for multiplication */
   if ( oper == MUL ) {
      if ( colA == rowB ) {
         Matrix2Sheet( (Sheet2Matrix( sA ) * Sheet2Matrix( sB )), sC );
         return;
      } else {
         fl_alert("Las matrices no son aptas para el producto");
         return;
      }
   }

   if ( (rowA != rowB) || (colA != colB) ) {
      fl_alert("Las matrices tienen distinto tamaño");
      return;
   }

   /* Only for addition and subtraction */
   switch ( oper ) {
      case ADD:
         Matrix2Sheet( (Sheet2Matrix( sA ) + Sheet2Matrix( sB )), sC );
         break;

      case SUB:
         Matrix2Sheet( (Sheet2Matrix( sA ) - Sheet2Matrix( sB )), sC );
         break;

      default:
         break;
   };

}

void numOp(Sheet *sA, double n, Sheet* sC){

   Matrix2Sheet( (Sheet2Matrix( sA ) * n), sC );
   return;
}

void powOp(Sheet *sA, double n, Sheet* sC){
   if (n ==1) {
      //Sheet2Sheet(sA, sC);
      identityMatrix( sC );
   }
   else {
      Matrix   b = Sheet2Matrix( sA );
      Matrix   c = b;

      for (int i=1; i<n; i++) b = b * c;
      Matrix2Sheet( b, sC );
   }
   return;
}

void detMatrix(Sheet* sA, Display_Text* display, char C) {
   double   det;
   char     cad[128];

   Matrix matrix = Sheet2Matrix( sA );

   if ( ! is_square( matrix ) ) {
      fl_alert("La matriz no es cuadrada");
      return;
   }

   det = determinante( matrix );

   sprintf(cad, "|%c| : %0.6f\n\n", C, det);
   display->appendBuf( cad );
   display->goEnd();

}

void rankMatrix(Sheet* sA, Display_Text* display, char C) {
   int      number;
   char     cad[128];

   Matrix matrix = Sheet2Matrix( sA );

   number = rank( matrix );

   sprintf(cad, "rank (%c) : %i\n\n", C, number);
   display->appendBuf( cad );
   display->goEnd();

}

void transposeMatrix(Sheet* sA, Sheet* sC) { Matrix2Sheet( transposeMatrix( Sheet2Matrix( sA ) ), sC ); }

void GaussJordanMatrix(Sheet* sA, Sheet* sC) { Matrix2Sheet( GaussJordan( Sheet2Matrix( sA ) ), sC ); }

void identityMatrix(Sheet* sA) {

   if ( sA->rows() != sA->cols() ) {
      fl_alert("La matriz no es cuadrada");
      return;
   }

   int r = sA->rows();
   sA->clearTable();
   for (int i=0; i<r; i ++) sA->setValue(i, i, 1);

   return;
}

void adjunteMatrix(Sheet* sA, Sheet* sC) {
   double   det;

   Matrix matrix = Sheet2Matrix( sA );

   if ( ! is_square( matrix ) ) {
      fl_alert("La matriz no es cuadrada");
      return;
   }

   if ( fabs(det=determinante( matrix )) == 0 ) {
      Matrix2Sheet( adjCofactor( matrix ), sC );
   } else {
      Matrix2Sheet( det * transposeMatrix( inverseMatrix( matrix ) ), sC );
   }

   return;
}

void invMatrix(Sheet* sA, Sheet* sC) {
   double   det;

   Matrix matrix = Sheet2Matrix( sA );

   if ( ! is_square( matrix ) ) {
      fl_alert("La matriz no es cuadrada");
      return;
   }


   if ( fabs(determinante( matrix )) == 0 ) {
      fl_alert("La matriz no tiene inversa");
      return;
   }

   Matrix2Sheet( inverseMatrix( matrix ), sC );
   return;
}
