<<<<<<< HEAD
=======
<<<<<<< HEAD
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

=======
>>>>>>> github/master
>>>>>>> sf/master
#include <FL/Enumerations.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include "logdisplay.h"
#include <iostream>


/* New object based in Fl_Text_Display */
Display_Text::Display_Text(int X, int Y, int W, int H)
   : Fl_Text_Display(X, Y, W, H) {
      buf = new Fl_Text_Buffer();
      buffer( buf );
      show_cursor( 1 );
#if FL_PATCH_VERSION >= 3
      linenumber_width( 35 );
#endif
}

Display_Text::~Display_Text() { }


int Display_Text::numBufLines() {
   return mNBufferLines;
}

void Display_Text::goEnd() {
   scroll(mNBufferLines, 0);
}

void Display_Text::goHome() {
   scroll(0, 0);
}

void Display_Text::appendBuf(const char* text) {
   buf->append( text );
}

void Display_Text::clear() {
   buf->remove(0, 5000);
}
