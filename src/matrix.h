/*
 * This file is part of MCalx, a simple GPL matrix calculator
 * 2015  Daniel R. Ome
 * 
 * Based in Rafael Sachetto's lib-matrix
 *
 * Info about matrix 2D: http://www.eld.leidenuniv.nl/~moene/Home/tips/matrix2d/
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

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define DEBUG
#undef DEBUG

class Matrix {

   /* Vars */
	double** marray = NULL; // Array
   string   msgerror;      // String msgerror
   bool     werror;        // True with error msg
	int      mRows, mCols;

   /* Functions */
	void     newMatrix(int rows, int cols);
	void     copyMatrix(const Matrix& src);
	void     deleteMatrix();

public:
   // ****************************
	// Constructors.
	/* Construct a empty matrix; */
   Matrix() ;

   /* Construct a matrix with rows and cols */
	Matrix( int rows , int cols );

   /* Construct a copy of matrix named rm (Right Matrix)*/
	Matrix( const Matrix& rm );

   /* Construct a matrix based in an array, rows and cols */
	Matrix(double **arr, int rows , int cols );

	// Destructor.
	/* Destroy the object */
	virtual ~Matrix();

   // End of Constructors
   // ****************************

   // ****************************
   // Methods.
	/* Get the number of rows of the matrix */
	int getRows() const;

	/* Get the number of columns of the matrix */
	int getCols() const;

   /* Get the string with error message */
   string getMsgError() const;

   /* Set the string with error message */
   string setMsgError(char* msg);

   /* Swap two rows */
   void swapRows(const int, const int );

   // End of Methods.
   // ****************************

   // ****************************
   // Operators.
   /* Set an element on matrix. Position (row, col) */
	double& operator ()(int, int );

   /* Get an element on matrix. Position (row, col) */
	double  operator ()(int , int ) const; 

   /* Compare two matrix */
   bool operator == (const Matrix& rm) const ;

   /* Compare two matrix */
   bool operator != (const Matrix& rm) const ;

   /* Assign a matrix */
	Matrix& operator = (const Matrix& rm);

   /* Add two matrices */
	friend Matrix operator + (const Matrix& lm, const Matrix& rm);

   /* Substract two matrices */
	friend Matrix operator - (const Matrix& lm, const Matrix& rm);

   /* Multiplies two matrices */
   friend Matrix operator * (const Matrix& m, const Matrix& n);

   /* Multiplies one matrix with one number */
   friend Matrix operator * (const Matrix& m, const double num);

   /* Multiplies one number with one matrix */
   friend Matrix operator * (const double num, const Matrix& m);

   /* Divide two matrices */
   friend Matrix operator / (const Matrix& m, const Matrix& n);

   /* Divide one matrix with one number */
   friend Matrix operator / (const Matrix& m, const double num);

   /* Print all elements of matrix */
   friend ostream& operator << (ostream& os, const Matrix& rm);

   // End of Operators.
   // ****************************
};


#endif //_MATRIX_H_
