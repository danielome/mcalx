/*
 * This file is part of MCalx, a simple GPL matrix calculator
 * (c) )2015  Daniel R. Ome
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

/*
 * -------------------------------------------
 * Matrix is a class for matricial operations
 * -------------------------------------------
 */

#include "matrix.h"

// ****************************
/* Private functions */
/* Create a fresh array for new matrix */
void Matrix::newMatrix(int rows, int cols) {
   if (marray)
      deleteMatrix();

   mRows = rows;
   mCols = cols;

	marray= new float * [mRows];
	for(int row = 0; row < mRows; row++) {
		marray[row] = new float [mCols];
		for (int _col=0; _col<mCols; _col++)
			marray[row][_col] = 0;
	}

   msgerror = "-1";
	werror   = false;
}

/* Copy a matrix in another */
void Matrix::copyMatrix(const Matrix& src) {

   mRows = src.getRows();
   mCols = src.getCols();

	for(int row= 0; row< mRows; row++)
		for(int col= 0; col < mCols; col++)
			marray[row][col] = src.marray[row][col];

   msgerror = src.msgerror;
   werror   = src.werror;
}

/* Delete memory allocated in a matrix */
void Matrix::deleteMatrix() {
	if ( marray != NULL ) {
      for(int row = 0; row < mRows; row++){ delete [] marray[row]; }
      delete [] marray;
      marray = NULL;
#ifdef DEBUG
   std::cout << "Deleting : " << (long) this << std::endl;
#endif
   }
}
//
// /* End of private functions */
// ****************************


// ****************************
/* Constructors. */
/* Construct a empty matrix; */
Matrix::Matrix() {
   mRows = 0;
   mCols = 0;
   werror= false;
   marray= NULL;
#ifdef DEBUG
   std::cout << "Constructor inicial: " << (long) this << std::endl;
#endif
}

/* Construct a matrix with rows and cols */
Matrix::Matrix( int rows , int cols ) {
   if ( (rows >= 1) && (cols >= 1) ) {
      marray = NULL;
      newMatrix(rows, cols);
   }

#ifdef DEBUG
      std::cout << "Constructor calificado: " << (long) this << std::endl;
      if ( werror ) std::cout << "Error: " << msgerror << std::endl;
#endif
}

/* Construct a copy of matrix named rm (Right Matrix)*/
Matrix::Matrix( const Matrix& rm ) {
   marray = NULL;
   newMatrix(rm.getRows(), rm.getCols());
   copyMatrix( rm );

#ifdef DEBUG
   std::cout << "Constructor copia this: " << (long) this << std::endl;
   std::cout << "Constructor copia m   : " << (long) &rm  << std::endl;
#endif
}

/* Construct a matrix based in an array, rows and cols */
Matrix::Matrix(float **arr, int rows , int cols ) {
   if ( (arr != NULL) &&
         (rows >= 1) && (cols >= 1) ) {
      newMatrix(rows, cols);
      for (int i = 0; i < rows; ++i)
         for (int j = 0; j < cols; ++j)
            marray[i][j] = arr[i][j];
   }
#ifdef DEBUG
   std::cout << "Constructor con arreglo: " << (long) this << std::endl;
#endif
}

// Destructor.
Matrix::~Matrix() {
#ifdef DEBUG
   std::cout << "Destructor : " << (long) this << std::endl;
#endif
   deleteMatrix();
}

/* End of Constructors. */
// ****************************


// ****************************
/* Methods */
int            Matrix::getRows()      const { return mRows; }
int            Matrix::getCols()      const { return mCols; }
inline string  Matrix::getMsgError()  const { return msgerror; }
void           Matrix::swapRows(const int a, const int b) {
   float         *aux;

   aux       = marray[a];
   marray[a] = marray[b];
   marray[b] = aux;
}

/* End of Methods */
// ****************************

// ****************************
/* Operators */
// (x, y) = z
float& Matrix::operator () (int row, int col) { return marray[row][col]; }
// z = (x, y)
float  Matrix::operator () (int row, int col) const { return marray[row][col]; }
// A = B
Matrix& Matrix::operator = (const Matrix& rm) {
   if(this == &rm)
      return *this;

#ifdef DEBUG
   std::cout << "_______=> Operador = this : " << (long) this << std::endl;
   std::cout << "_______=> Operador = m    : " << (long) &rm  << std::endl;
#endif

   if ( this->marray == NULL ) {
#ifdef DEBUG
      std::cout << "Operador = : this está vacio. Llenar\n";
#endif
      newMatrix(rm.getRows(), rm.getCols());
   } else {
#ifdef DEBUG
      std::cout << "Operador = : this está lleno. Resize\n";
#endif
      deleteMatrix();
      newMatrix(rm.getRows(), rm.getCols());
   }

   copyMatrix( rm );

   return *this;
}
// A == B
bool Matrix::operator == (const Matrix& rm) const {
   if ( (this->mRows == rm.getRows() ) && (this->mCols == rm.getCols()) ) {
      for (int i=0; i < mRows; i++)
         for (int j=0; j < mCols; j++)
            if ( marray[i][j] != rm.marray[i][j] )
               return false;
      return true;
   }
   return false;
}
// A != B
bool Matrix::operator != (const Matrix& rm) const {
   if (*this == rm)
      return false;
   else
      return true;
}
// A + B
Matrix operator + (const Matrix& lm, const Matrix& rm) {
   int      mRows = rm.getRows();
   int      mCols = rm.getCols();
   Matrix   tmp(mRows, mCols);

#ifdef DEBUG
   std::cout << "_______=> Operador + tmp  : " << (long) &tmp << std::endl;
   std::cout << "_______=> Operador + rm    : " << (long) &rm << std::endl;
#endif

   for (int row=0; row<mRows; row++)
      for (int col=0; col<mCols; col++)
         tmp(row, col) = lm(row, col) + rm(row, col);

   return tmp;
}
// A - B
Matrix operator - (const Matrix& lm, const Matrix& rm) {
   int      mRows = rm.getRows();
   int      mCols = rm.getCols();
   Matrix   tmp(mRows, mCols);

#ifdef DEBUG
   std::cout << "_______=> Operador - tmp  : " << (long) &tmp << std::endl;
   std::cout << "_______=> Operador - rm    : " << (long) &rm << std::endl;
#endif

   for (int row=0; row<mRows; row++)
      for (int col=0; col<mCols; col++)
         tmp(row, col) = lm(row, col) - rm(row, col);

   return tmp;
}
// A * B
Matrix operator * (const Matrix& lm, const Matrix& rm) {
   Matrix   tmp;

   if ( lm.getCols() == rm.getRows() ) {
      int      lRows = lm.getRows();
      int      lCols = lm.getCols();
      int      rCols = rm.getCols();
      float   element;

      tmp = Matrix(lRows, rCols);
#ifdef DEBUG
      std::cout << "_______=> Operador * tmp  : " << (long) &tmp << std::endl;
      std::cout << "_______=> Operador * lm   : " << (long) &rm << std::endl;
      std::cout << "_______=> Operador * rm   : " << (long) &rm << std::endl;
#endif

      for (int _rowL=0; _rowL < lRows; _rowL++)
         for (int _colR=0; _colR<rCols; _colR++) {
            element = 0;
            for (int _rowcol=0; _rowcol<lCols; _rowcol++)
               element += lm(_rowL, _rowcol) * rm(_rowcol, _colR);
            tmp(_rowL, _colR) = element;
         }
   }

   return tmp;
}

// A * n
Matrix operator * (const Matrix& rm, const float num) {
   int      mRows = rm.getRows();
   int      mCols = rm.getCols();
   Matrix   tmp(mRows, mCols);

#ifdef DEBUG
   std::cout << "_______=> Operador * tmp  : " << (long) &tmp << std::endl;
   std::cout << "_______=> Operador * rm   : " << (long) &rm << std::endl;
#endif

   for (int row=0; row<mRows; row++)
      for (int col=0; col<mCols; col++)
         tmp(row, col) = rm(row, col) * num;

   return tmp;
}
// n * A
Matrix operator * (const float num, const Matrix& m) {
   return m * num;
}
// A / n
Matrix operator / (const Matrix& m, const float num) {
   int      mRows = m.getRows();
   int      mCols = m.getCols();
   Matrix   tmp(mRows, mCols);

#ifdef DEBUG
   std::cout << "_______=> Operador / tmp  : " << (long) &tmp << std::endl;
   std::cout << "_______=> Operador / m    : " << (long) &m << std::endl;
#endif

   for (int row=0; row<mRows; row++)
      for (int col=0; col<mCols; col++)
         tmp(row, col) = m(row, col) / num;

   return tmp;
}
// << A
ostream& operator << (ostream& os, const Matrix& rm) {
   int R = rm.getRows();
   int C = rm.getCols();

   os << "------------------------" << "\n";
   if (R == 0) {
      os << "Matrix Empty" << "\n";
   } else {
#ifdef DEBUG
   os << "Matrix: Rows = " << R << " Cols = " << C << "\n";
#endif
      for (int row=0; row < R; row++) {
         for (int col=0; col < C; col++)
            os << rm(row, col) << "\t";
         os << "\n";
      }
   }
   os << "------------------------" << "\n";

   return os;
}

// End of Operators.
// ****************************
/*
int main() {
   Matrix   a;
   Matrix   b;
   Matrix   c;

   c = Matrix(3, 4);
   Matrix d = c;
   Matrix e = Matrix( d );

   d = Matrix(5, 7);
   d = Matrix( c );

   return 0;
}
*/
