/*
 * Fl_Scientific_Button.cpp
 *
 *  Created on: 30.06.2011
 *      Author: ed
 *      from fltk.general group
 *      (https://groups.google.com/d/msg/fltkgeneral/lqFJDrW6laM/7xzeuU9YsLkJ)
 *
 *  23/03/15
 *      Modified by Daniel R. Ome for use the Latex style for
 *      superscript/subscript text, like next example:
 *          Fe_{3}(SO_{4}) (PO_{4})^{-3}
 *
 * 19/08/20
 *    Minor modifications and cleaning code by Daniel R. Ome
 */

#include <FL/fl_draw.H>
#include "Fl_Scientific_Button.h"
#include <iostream>


//----------------------------------------------------------------------------
void Fl_Scientific_Button::value(string V)
{
   m_Text= V;
   label(m_Text.c_str());
   Parse();
   redraw();
}
//----------------------------------------------------------------------------
void Fl_Scientific_Button::Parse()
{  // Divide string into parts of different format
   if (label())
   {
      string Text= label();
      string Sub;
      string::size_type nPosU;
      string::size_type nPosD;
      string::size_type fPos = 0;   // First position
      string::size_type ePos = 0;   // End position
      char  c='.';                  // Normally start with unchanged font
      int   mw, mh;                 // Pos in x and y axis
      int   FH = fSize;

      labeltype(FL_NO_LABEL);

      //std::cout << Text << std::endl;
      m_Label.clear();

      do {
         fPos = ( (nPosU=Text.find("_{", ePos)) < (nPosD=Text.find("^{", ePos)) ) ? nPosU : nPosD;
         if ( fPos == ePos ) {
            ePos = 2;
            c = Text[fPos];
            fPos = Text.find("}", 0);
         } else
            c = '.';

         Sub= Text.substr(ePos, fPos - ePos);

         if (!Sub.empty()) {  // If Sub has text
            int   d;
            switch ( c ) {
               case '^':   d = -(FH*td)/50;  break;
               case '_':   d = (FH*td)/100;  break;
               default :   d = 0;            break;
            }

            fl_font(labelfont(), ( (d==0) ? FH : (FH*tf)/100));
            fl_measure(Sub.c_str(), mw, mh);

            //printf("%s \t %c \t %i \t %i \t %i \t %i\n", Sub.c_str(), c, mw, mh, d, 0);

            m_Label.push_back(part(Sub, c, mw, mh, d));
            if ( Text[fPos] == '}' )
               ++ fPos;
            Text.erase(0, fPos);
            ePos = 0;
         }
      } while (Text.size());
   }
}
//----------------------------------------------------------------------------
void Fl_Scientific_Button::draw()
{  // TODO: Distance from border should be kept automatically, not by a space.
   Fl_Button::draw();

   int      Pos= 0;
   int      FH = labelsize(); // font size

   if ( fSize != FH ) {
      fSize = FH;
      Parse();
   }

   fl_font(labelfont(), FH);
   fl_color( sb_ColorText );

   if (align() & FL_ALIGN_RIGHT)
      for (unsigned i= m_Label.size(); i > 0; --i) {
         fl_font(labelfont(), ( (m_Label[i -1].dF==0) ? FH : (FH*tf)/100));
         fl_draw(m_Label[i -1].Text.c_str(), x(), y() + m_Label[i-1].dF, w() -Pos, h(), FL_ALIGN_RIGHT);
         Pos+= m_Label[i -1].mW;
      }
   else if (align() == FL_ALIGN_CENTER || align()== FL_ALIGN_INSIDE) {
      int x0= 0;
      for (unsigned i= 0; i< m_Label.size(); ++i)  // Calc center of string position
         x0 += m_Label[i].mW;

      x0 = (w() - x0) >> 1;
      x0 = ( (x0 > 0) ? ( x() + x0 ) : x() );

      for (unsigned i= 0; i< m_Label.size(); ++i) {
         fl_font(labelfont(), ( (m_Label[i].dF==0) ? FH : (FH*tf)/100));
         fl_draw(m_Label[i].Text.c_str(), x0 + Pos, y() + m_Label[i].dF, w() -Pos, h(), FL_ALIGN_LEFT);
         Pos+= m_Label[i].mW;
      }
   }
   else // if (align() & FL_ALIGN_LEFT)
      for (unsigned i= 0; i< m_Label.size(); ++i) {
         fl_font(labelfont(), ( (m_Label[i].dF==0) ? FH : (FH*tf)/100));
         fl_draw(m_Label[i].Text.c_str(), x() + Pos, y() + m_Label[i].dF, w() -Pos, h(), FL_ALIGN_LEFT);
         Pos+= m_Label[i].mW;
      }
}
