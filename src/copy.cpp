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
#include "copy.h"
#include "sheet.h"
//#include "squarematrix.h"
//#include "transpose.h"

using namespace std;
using std::ostringstream;

/* Internal functions */
/* ------------------------ */
//Matrix  Sheet2Matrix(Sheet *S) {
   //int      mrows = S->rows();
   //int      mcols = S->cols();
   //Matrix   tmp = Matrix(mrows, mcols);

   //for (int row=0; row<mrows; row++)
      //for (int col=0; col<mcols; col++)
         //tmp(row, col) = S->getValue(row, col);

   //return tmp;
//}

/* ------------------------ */
//void Matrix2Sheet(Matrix src, Sheet* C) {
   //int   rows = src.getRows();
   //int   cols = src.getCols();

   //for(int row = 0; row < rows; row++) {
      //for (int col=0; col<cols; col++)
         //C->setValue(row, col, src(row, col));
   //}

   //C->rows( src.getRows() );
   //C->cols( src.getCols() );
//}
/* Internal functions */

void Sheet2Sheet (Sheet* src, Sheet* des) {
   int     rowA, colA;

   rowA = src->rows(); colA = src->cols();

   for (int r=0; r<rowA; r ++)
      for (int c=0; c<colA; c ++)
         des->setValue(r, c, src->getValue(r, c));

   des->rows( src->rows() );
   des->cols( src->cols() );

   if ( des->is_setIRow() ) {  /* is matrix C? */
      des->rows2input();
      des->cols2input();
   }

   return;
}

void swapMatrix(Sheet* A, Sheet* B) {
   float    **tmp;
   int      rowtmp, coltmp;

   rowtmp = A->rows();
   coltmp = A->cols();
	tmp = new float  * [rowtmp];
	for(int row = 0; row < rowtmp; row++) {
		tmp[row] = new float  [coltmp];
		for (int col=0; col<coltmp; col++)
			tmp[row][col] = A->getValue(row, col);
	}

   Sheet2Sheet(B, A);

   for (int row=0; row<rowtmp; row ++)
      for (int col=0; col<coltmp; col ++)
         B->setValue(row, col, tmp[row][col]);
   B->rows( rowtmp );
   B->cols( coltmp );
   if ( B->is_setIRow() ) {  /* is matrix C? */
      B->rows2input();
      B->cols2input();
   }

   for(int row = 0; row < rowtmp; row++){ delete [] tmp[row]; }
   delete [] tmp;

   return;
}

void copyC2CB (Sheet* A) {
   int      row = A->rows();
   int      col = A->cols();
   string   str;

   ostringstream ss;

   for (int r=0; r<row; r ++) {
      for (int c=0; c<col; c ++) {
         ss << A->getValue(r, c) << "\t";
         str = str + ss.str();
         ss.str("");
      }
      str = str + "\n";
   }

   const char * c = str.c_str();
   Fl::copy(c, strlen(c), 1);
   return;
}
