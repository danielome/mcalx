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
