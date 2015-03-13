#ifndef _LOGDISPLAY_H
#define _LOGDISPLAY_H

#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>

class Display_Text : public Fl_Text_Display {
   Fl_Text_Buffer*   buf;

   public:
      Display_Text(int , int , int , int );
      ~Display_Text();
      int numBufLines();
      void goEnd();
      void goHome();
      void appendBuf(const char*);
      void clear();
};

#endif

