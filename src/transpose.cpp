#include "matrix.h"

Matrix transposeMatrix (const Matrix& m) {
   int      rows, cols;
   int      _row, _col;

   rows        = m.getRows();
   cols        = m.getCols();
   Matrix tmp  = Matrix(cols, rows);

   for (_row=0; _row<rows; _row ++)
      for(_col=0; _col<cols; _col ++)
         tmp(_col, _row) = m(_row, _col);

   return tmp;
}

/* NO ELIMINAR ESTA PARTE DEL CODIGO
 * CONTIENE LO NECESARIO PARA TRANSPONER LA MATRIZ
 * CALCULAR LA DETERMINANTE
 * CALCULAR EL RANGO DE LA MATRIZ
 */

//int main() {

   //double **array, **auxarray;
   //int      rows, cols;
   //int      _row, _col;
   //int      sign;
   //double   det;

   //printf("Ingresar la cantidad de filas de la matriz: ");
   //scanf("%i", &rows);
   //printf("Ingresar la cantidad de columnas de la matriz: ");
   //scanf("%i", &cols);

   //if ( (rows < 2) || (cols < 2) )
      //return(1);

   //array = new double * [rows];

   ///* Allocate matrix */
   //for (_row=0; _row<rows; _row++)
      //array[_row] = new double [cols];

   ///* Enter data on matrix */
   //for(_row=0;_row < rows;_row++){
      //for(_col=0;_col < cols;_col++){
         //printf("Los valores de la matriz [%d,%d]= ",_row + 1, _col + 1);
         //scanf("%lf",&array[_row][_col]);
      //}
   //}

   ///* Imprimir los datos */
   //print(array, rows, cols);

   ////if (rows < cols) {      /* Transform in transpose matrix */
      ////int aux;

      ////auxarray = new double * [cols];
      ////for (_col=0; _col<cols; _col++)
         ////auxarray[_col] = new double [rows];

      ////for (_row=0; _row<rows; _row++)        /* Transpose matrix */
         ////for(_col=0; _col<cols; _col++)
            ////auxarray[_col][_row] = array[_row][_col];

      ////for (_row=0; _row<rows; _row++)
         ////delete [] array[_row];
      ////delete [] array;

      ////array = auxarray;

      ////aux = rows;
      ////rows= cols;
      ////cols= aux;
   ////}

   /* OJO !!! Esta parte del codigo transpone la matriz */
   //if (rows < cols) {      /* Transform in transpose matrix */
      //int aux;

      //auxarray = new double * [cols];
      //for (_col=0; _col<cols; _col++)
         //auxarray[_col] = new double [rows];

      //for (_row=0; _row<rows; _row++) {      /* Transpose matrix */
         //for(_col=0; _col<cols; _col++)
            //auxarray[_col][_row] = array[_row][_col];
         //delete [] array[_row];
      //}

      ////for (_row=0; _row<rows; _row++)
         ////delete [] array[_row];
      //delete [] array;

      //array = auxarray;

      //aux = rows;
      //rows= cols;
      //cols= aux;
   //}

   ////upperTriangle( array, rows, cols, sign );
   //lowerTriangle( array, rows, cols, sign );

   ///* Calculate determinant of the matrix */
   //if (rows == cols) {
      //det = 1.0;
      //for (_col=0; _col<cols; _col++) {
         //det = det * array[_col][_col];
      //}
      //det = det * sign;
      //printf("%f\n", det);

      //std::cout << std::setw(15) << "Determinante: " << det << std::endl;
   //}

   ///* Imprimir los datos */
   //print(array, rows, cols);

   //int cont=0;
   //for (_row=rows-1; _row>=0; _row--) {
      //for (_col=0; _col<cols; _col++) {
         //if (array[_row][_col] != 0) {
            //cont ++;
            //break;
         //}
      //}
   //}
   //printf("Rango de la matriz: %i\n", cont);

   ///* Borrar el arreglo */
   //for (_row=0; _row<rows; _row++)
      //delete [] array[_row];
   //delete [] array;


   //return 0;
//}
