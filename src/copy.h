#ifndef _COPY_H
#define _COPY_H

#include "sheet.h"
#include "matrix.h"
#include "logdisplay.h"

enum { AB, BA, CA, CB, ACB, BCB, CCB };

void Sheet2Sheet (Sheet* , Sheet* ) ;

void swapMatrix (Sheet* , Sheet* ) ;

void copyC2CB (Sheet* );

/*void copyMatrix (Sheet* , Sheet* , typeCopy) ;*/

/*void numOp(Sheet* , double , Sheet* );*/

/*void powOp(Sheet* , double , Sheet* );*/

/*void transposeMatrix(Sheet* , Sheet* );*/

/*void invMatrix(Sheet* , Sheet* );*/

/*void adjunteMatrix(Sheet* , Sheet* );*/

/*void identityMatrix(Sheet* );*/

/*void GaussJordanMatrix(Sheet* , Sheet* );*/

/*void detMatrix(Sheet* , Display_Text* , char );*/

/*void rankMatrix(Sheet* , Display_Text* , char );*/

#endif
