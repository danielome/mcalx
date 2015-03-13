#ifndef _SHEET_H
#define _SHEET_H

/*#include <iostream>*/
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>

const int MAX_COLS = 32;
const int MAX_ROWS = 32;
const int FONT_SIZE = 12;

char* itoa(int );

class Sheet : public Fl_Table {
   Fl_Float_Input *input;
   double         values[MAX_ROWS][MAX_COLS];
   int            row_edit, col_edit;
   bool           enable;
   bool           havefocus;
   Fl_Int_Input   *inpRow;
   Fl_Int_Input   *inpCol;

protected:
   void draw_cell(TableContext ,int ,int ,int ,int ,int ,int);
   void event_callback2();				// table's event callback (instance)
   static void event_callback(Fl_Widget*,void *v) { ((Sheet*)v)->event_callback2(); }
   static void input_cb(Fl_Widget* sp,void* v) { ((Sheet*)v)->set_value_hide(); }

public:
   Sheet(int ,int ,int ,int ,const char* );
   ~Sheet();
   int      handle (int e);
   void     clearTable();
   void     enabled( bool  );
   void     set_value_hide();
   void     start_editing(int , int );
   void     done_editing();
   double   getValue(int, int);
   void     setValue(int , int , double );
   void     setIRow(Fl_Int_Input* );
   bool     is_setIRow();
   void     setICol(Fl_Int_Input* );
   void     rows2input();
   void     cols2input();
   void     input2rows();
   void     input2cols();
};




#endif
