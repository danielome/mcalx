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
