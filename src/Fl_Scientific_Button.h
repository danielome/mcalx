/*
 * Fl_Scientific_Box.h
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
 *    Minor modifications by Daniel R. Ome
 */

#ifndef FL_SCIENTIFIC_BOX_H_
#define FL_SCIENTIFIC_BOX_H_

#include <vector>
#include <string>
using std::string;

#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

// Text soll für wissenschaftliche Schreibweise hoch- oder tiefgestellt werden können.
// @t startet das Tiefstellen, @h startet das Hochstellen @. startet wieder Normalstellung
// Umgestellter Text wird üblicherweise um einen Faktor verkleinert

// This class sets text up/ down for scientific notation.
// @t starts setting text down, @h starts setting text up, @. goes back to normal text.
// Down- an up text will be scaled down.
//
class Fl_Scientific_Button: public Fl_Button
{
   public:
      struct part
      {
         string   Text;
         char     Mark;
         short    mW;
         short    mH;
         int      dF;

         part(string S, char f, short w, short h, int d): Text(S), Mark(f), mW(w), mH(h), dF(d)  {}
      };

      Fl_Scientific_Button(int x, int y, int w, int h, const char* l= 0):
         Fl_Button(x, y, w, h, l),
         td(10),              // 10% of current height for setting up/ down
         tf(80),              // Scaling down the font to 80% of current height
         fSize( labelsize() ),// Size of font
         sb_ColorText( FL_BLACK )

      { if (l) Parse(); }

      virtual ~Fl_Scientific_Button() {}

      inline   void sb_labelcolor( Fl_Color c ) { sb_ColorText = c; }

      inline   const char* value() const  { return Fl_Button::label(); }

      void     value(string V);

      int      td;
      int      tf;
      int      fSize;
      string   m_Text;

      void Parse();

   protected:
      std::vector< part > m_Label;
      Fl_Color sb_ColorText;

      virtual void draw();
};

#endif /* FL_SCIENTIFIC_BOX_H_ */
