/*
 * This file is part of MCalx, a simple GPL matrix calculator
<<<<<<< HEAD
=======
<<<<<<< HEAD
 * (c) )2015  Daniel R. Ome
=======
>>>>>>> sf/master
 * 2015  Daniel R. Ome
 * 
 * Based in Rafael Sachetto's lib-matrix
 *
 * Info about matrix 2D: http://www.eld.leidenuniv.nl/~moene/Home/tips/matrix2d/
<<<<<<< HEAD
=======
>>>>>>> github/master
>>>>>>> sf/master
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

#include "matrix.h"

// ****************************
/* Private functions */
/* Create a fresh array for new matrix */
void Matrix::newMatrix(int rows, int cols) {
   if (marray)
      deleteMatrix();

   mRows = rows;
   mCols = cols;

	marray= new double * [mRows];
	for(int row = 0; row < mRows; row++) {
		marray[row] = new double [mCols];
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
<<<<<<< HEAD
=======
<<<<<<< HEAD
   marray= NULL;
=======
>>>>>>> github/master
>>>>>>> sf/master
#ifdef DEBUG
   std::cout << "Constructor inicial: " << (long) this << std::endl;
#endif
}

/* Construct a matrix with rows and cols */
Matrix::Matrix( int rows , int cols ) {
   if ( (rows >= 1) && (cols >= 1) ) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
      marray = NULL;
=======
>>>>>>> github/master
>>>>>>> sf/master
      newMatrix(rows, cols);
   }

#ifdef DEBUG
      std::cout << "Constructor calificado: " << (long) this << std::endl;
      if ( werror ) std::cout << "Error: " << msgerror << std::endl;
#endif
}

/* Construct a copy of matrix named rm (Right Matrix)*/
Matrix::Matrix( const Matrix& rm ) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
   marray = NULL;
=======
>>>>>>> github/master
>>>>>>> sf/master
   newMatrix(rm.getRows(), rm.getCols());
   copyMatrix( rm );

#ifdef DEBUG
   std::cout << "Constructor copia this: " << (long) this << std::endl;
   std::cout << "Constructor copia m   : " << (long) &rm  << std::endl;
#endif
}

/* Construct a matrix based in an array, rows and cols */
Matrix::Matrix(double **arr, int rows , int cols ) {
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
int      Matrix::getRows()      const { return mRows; }
int      Matrix::getCols()      const { return mCols; }
inline string   Matrix::getMsgError()  const { return msgerror; }
void     Matrix::swapRows(const int a, const int b) {
   double      *aux;

   aux       = marray[a];
   marray[a] = marray[b];
   marray[b] = aux;
}

/* End of Methods */
// ****************************

// ****************************
/* Operators */
// (x, y) = z
double& Matrix::operator () (int row, int col) { return marray[row][col]; }
// z = (x, y)
double  Matrix::operator () (int row, int col) const { return marray[row][col]; }
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
      double   element;

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
Matrix operator * (const Matrix& rm, const double num) {
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
Matrix operator * (const double num, const Matrix& m) {
   return m * num;
}
// A / n
Matrix operator / (const Matrix& m, const double num) {
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
<<<<<<< HEAD
=======
<<<<<<< HEAD
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
=======
>>>>>>> sf/master




//bool Matrix::isNull() {

	//if(marray)
		//return false;
	//else
		//return true;

//}

//Matrix Matrix::getTransposed() const {

	//Matrix temp(mCols, mRows);
	//double aux;

	//for(int i = 0; i < temp.mRows; i++) {
		//for(int j = 0; j < temp.mCols; j++) {
			//aux = marray[j][i];
			//temp.setElem(i,j,aux);			
		//}
	//}

	//return temp;
//}

//Matrix Matrix::getInverseMatrix() {

	//Matrix A(*this);
	//int n = A.getmCols()-1;
	//double aux;
	//Vector *b;
	//Matrix inverse(n+1,0);

	//for(int i = 1; i <= n; i++) {	
		//A(i,0) = A(i,0)/A(0,0);	
	//}

	//for(int i = 1; i <= n; i++) {	
		//for(int j = i; j <= n; j++) {
			//aux = A(i,j);
			//for(int k = 0; k <= i-1; k++) {			
				//aux = aux - A(i,k)*A(k,j);			
			//}
			//A(i,j) = aux;
		//}
		//if(i != n) {
			//for(int j = i+1; j <= n; j++) {
				//aux = A(j,i);
				//for(int k = 0; k <= i-1; k++) {			
					//aux = aux - A(j,k)*A(k,i);			
				//}
				//A(j,i) = aux/A(i,i);
			//}		
		//}	
	//}


	//for(int i = 0; i <= n; i++) {

		//b = new Vector(n+1);
		//b->setI(i,1);

		//for(int i = 1; i <= n; i++) {
			//for(int k = 0; k <= i-1; k++) {	
				//if(i == k)
					//aux = 1;
				//else
					//aux = A(i,k);	
				//b->setI(i,(b->getI(i)-aux*b->getI(k)));
				////b[i] = &b[i]-aux*(b[k]);		
			//}
		//}	

		//*b = retroSubstitution(A,*b);
		//inverse.addColumnRight(*b);

	//}	

	//return inverse;
//}

//double Matrix::getDeterminant() const {


	//Matrix aux(this->getDiagonalMatrix());

	//if(mRows != mCols) {
		//cerr << "Error getDeterminant()!! ";
		//exit(0);
	//}

	//double det = 1;		

	//for(int j = 0; j < mCols; j++) { 
		//det *= aux.getElem(j,j);;						
	//}	
	//return det;	
//}

//Matrix Matrix::reducedMatrix (MatrixMatrix & m, int offset) {


	//Matrix aux(m.mRows-1, m.mCols-1);
	//int iAux = 0, jAux = 0;


	//for(int i = 1; i < m.mRows; i++) {
		//for(int j = 0; j < m.mCols; j++) {

			//if(j != offset) {
				//aux.setElem(iAux,jAux,m.marray[i][j]);	
				//jAux += 1;					
			//}

			//if((jAux == aux.getmCols()) && (iAux < aux.getmRows())){
				//iAux+=1;
				//jAux = 0;								
			//}							
		//}	

	//}

	//return aux;

//}

//Vector Matrix::getPrincipalDiagonal() const {

	//if(mRows != mCols) {
		//cerr << "Error getPrincipalDiagonal()!! " << endl;
		//exit(0);
	//}

	//Vector result(mRows);
	//double aux;

	//for(int i = 0; i < mRows; i++) {

		//aux = marray[i][i];
		//result.setI(i, aux);

	//}

	//return result;

//}

//Vector Matrix::getSecundaryDiagonal() const {

	//if(mRows != mCols) {
		//cerr << "Error getSecundaryDiagonal()!! " << endl;
		//exit(0);
	//}

	//Vector result(mRows);
	//double aux;

	//for(int i = mRows-1; i >= 0; i--) {

		//aux = marray[(mRows-1)-i][i];
		//result.setI((mRows-1)-i, aux);

	//}

	//return result;

//}

//void Matrix::addColumnRight(Vector &b) {

	//if(mRows != b.getSize()) {
		//cerr << "Error addColumn(Vector &b)!! " << endl;
		//exit(0);
	//}

	//Matrix aux(mRows, mCols+1);
	//double val;

	//for (int i = 0; i < mRows; ++i) {
		//for (int j = 0; j < mCols; ++j) {
			//val = this->getElem(i,j);
			//aux.setElem(i,j, val);
		//}	
	//}

	//for (int i = 0; i < mRows; ++i) {
		//val = b.getI(i);
		//aux.setElem(i,mCols, val);
	//}	

	//*this = aux;

//}

//void Matrix::addColumnLeft(Vector &b) {

	//if(mRows != b.getSize()) {
		//cerr << "Error addColumn(Vector &b)!! " << endl;
		//exit(0);
	//}

	//Matrix aux(mRows, mCols+1);
	//double val;

	//for (int i = 0; i < mRows; ++i) {
		//for (int j = 0; j < mCols; ++j) {
			//val = this->getElem(i,j);
			//aux.setElem(i,j+1, val);
		//}	
	//}

	//for (int i = 0; i < mRows; ++i) {
		//val = b.getI(i);
		//aux.setElem(i,0, val);
	//}	

	//*this = aux;

//}


//double Matrix::getNorm() const{

	//double sum = 0;

	//for(int i = 0; i < this->getmRows(); i++) {
		//for(int j = 0; j < this->getmCols(); j++) {
			//sum += pow(this->getElem(i,j),2);
		//}
	//}

	//return sqrt(sum);

//}

//double Matrix::getCond() {

	//return  (this->getNorm())*(this->getInverseMatrix().getNorm());

//}

<<<<<<< HEAD
=======
>>>>>>> github/master
>>>>>>> sf/master
