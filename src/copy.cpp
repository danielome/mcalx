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
   double   **tmp;
   int      rowtmp, coltmp;

   rowtmp = A->rows();
   coltmp = A->cols();
	tmp = new double * [rowtmp];
	for(int row = 0; row < rowtmp; row++) {
		tmp[row] = new double [coltmp];
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


//void pasteC2CB (Fl_Widget* A) {
   //int   row = A->rows();
   //int   col = A->cols();

   //for (int r=0; r<row; r ++) {
      //for (int c=0; c<col; c ++)
         //cout << A->getValue(r, c) << ";";
      //cout << "\n" ;
   //}

   //char  *s = "12;13;14;16";
   //Fl::copy(s, strlen(s), 1);
   //return;
//}

//void numOp(Sheet *src, double n, Sheet* sC){

   //Matrix2Sheet( (Sheet2Matrix( src ) * n), sC );
   //return;
//}

//void powOp(Sheet *src, double n, Sheet* sC){
   //if (n ==1) {
      ////Sheet2Sheet(src, sC);
      //identityMatrix( sC );
   //}
   //else {
      //Matrix   b = Sheet2Matrix( src );
      //Matrix   c = b;

      //for (int i=1; i<n; i++) b = b * c;
      //Matrix2Sheet( b, sC );
   //}
   //return;
//}

//void detMatrix(Sheet* src, Display_Text* display, char C) {
   //double   det;
   //char     cad[128];

   //Matrix matrix = Sheet2Matrix( src );

   //if ( ! is_square( matrix ) ) {
      //fl_alert("La matriz no es cuadrada");
      //return;
   //}

   //det = determinante( matrix );

   //sprintf(cad, "Determinante de Matriz %c : %0.6f\n\n", C, det);
   //display->appendBuf( cad );
   //display->goEnd();

//}

//void rankMatrix(Sheet* src, Display_Text* display, char C) {
   //double   det;
   //char     cad[128];

   //Matrix matrix = Sheet2Matrix( src );

   //if ( ! is_square( matrix ) ) {
      //fl_alert("La matriz no es cuadrada");
      //return;
   //}

   //det = determinante( matrix );

   //sprintf(cad, "Rank de Matriz %c : %0.6f\n\n", C, det);
   //display->appendBuf( cad );
   //display->goEnd();

//}

//void transposeMatrix(Sheet* src, Sheet* sC) {

   //Matrix2Sheet( transposeMatrix( Sheet2Matrix( src ) ), sC );
   //return;
//}
 
//void identityMatrix(Sheet* src) {

   //if ( src->rows() != src->cols() ) {
      //fl_alert("La matriz no es cuadrada");
      //return;
   //}

   //int r = src->rows();
   //src->clearTable();
   //for (int i=0; i<r; i ++) src->setValue(i, i, 1);

   //return;
//}

//void GaussJordanMatrix(Sheet* src, Sheet* sC) { return;}
//void adjunteMatrix(Sheet* src, Sheet* sC) { return;}

//void invMatrix(Sheet* src, Sheet* sC) {
   //double   det;

   //Matrix matrix = Sheet2Matrix( src );

   //if ( ! is_square( matrix ) ) {
      //fl_alert("La matriz no es cuadrada");
      //return;
   //}


   //if ( fabs(determinante( matrix )) == 0 ) {
      //fl_alert("La matriz no tiene inversa");
      //return;
   //}

   //Matrix2Sheet( inverseMatrix( matrix ), sC );
   //return;
//}
