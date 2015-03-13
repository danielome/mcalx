#ifndef _OP_H
#define _OP_H

#include "sheet.h"
#include "matrix.h"
#include "logdisplay.h"

enum typeOp { ADD, SUB, MUL };

void basicOp (Sheet* , Sheet* , Sheet* , typeOp) ;

void numOp(Sheet* , double , Sheet* );

void powOp(Sheet* , double , Sheet* );

void transposeMatrix(Sheet* , Sheet* );

void invMatrix(Sheet* , Sheet* );

void adjunteMatrix(Sheet* , Sheet* );

void identityMatrix(Sheet* );

void GaussJordanMatrix(Sheet* , Sheet* );

void detMatrix(Sheet* , Display_Text* , char );

void rankMatrix(Sheet* , Display_Text* , char );

#endif
