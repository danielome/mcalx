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

#ifndef _SQUAREMATRIX_H
#define _SQUAREMATRIX_H

#include <iostream>
#include "upper_lower.h"
#include "transpose.h"
#include "matrix.h"

bool   is_square     (const Matrix& ) ;
bool   is_symmetric  (const Matrix& ) ;
bool   is_idempotent (const Matrix& ) ;
int    rank_         (const Matrix& ) ;
float  trace         (const Matrix& ) ;
float  determinante  (const Matrix& ) ;
Matrix identityMatrix(const int )	  ;
Matrix inverseMatrix (const Matrix& ) ;
Matrix adjCofactor   (const Matrix& ) ;

#endif // _SQUAREMATRIX_H
