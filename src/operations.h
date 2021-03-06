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

#ifndef _OP_H
#define _OP_H

#include "sheet.h"
#include "matrix.h"
#include "logdisplay.h"

enum typeOp { ADD, SUB, MUL };

void basicOp (Sheet* , Sheet* , Sheet* , typeOp) ;

void numOp(Sheet* , float , Sheet* );

void powOp(Sheet* , float , Sheet* );

void transposeMatrix(Sheet* , Sheet* );

void invMatrix(Sheet* , Sheet* );

void adjunteMatrix(Sheet* , Sheet* );

void identityMatrix(Sheet* );

void GaussJordanMatrix(Sheet* , Sheet* );

void detMatrix(Sheet* , Display_Text* , char );

void rankMatrix(Sheet* , Display_Text* , char );

#endif
