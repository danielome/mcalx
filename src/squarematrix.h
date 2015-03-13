#ifndef _SQUAREMATRIX_H
#define _SQUAREMATRIX_H

#include <iostream>
#include "upper_lower.h"
#include "transpose.h"
#include "matrix.h"

bool   is_square     (const Matrix& ) ;
bool   is_symmetric  (const Matrix& ) ;
bool   is_idempotent (const Matrix& ) ;
int    rank          (const Matrix& ) ;
double trace         (const Matrix& ) ;
double determinante  (const Matrix& ) ;
Matrix identityMatrix(const int )	  ;
Matrix inverseMatrix (const Matrix& ) ;
Matrix adjCofactor   (const Matrix& ) ;

#endif // _SQUAREMATRIX_H
