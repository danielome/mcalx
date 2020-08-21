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
   float          values[MAX_ROWS][MAX_COLS];
   int            row_edit, col_edit;
   bool           enable;
   bool           havefocus;
   Fl_Int_Input   *inpRow;
   Fl_Int_Input   *inpCol;
   int            precision;

protected:
   void     set_value_hide();
   void     start_editing(int , int );
   void     done_editing( bool );
   /* *** */
   void draw_cell(TableContext ,int ,int ,int ,int ,int ,int);
   void event_callback2();				// table's event callback (instance)
   static void event_callback(Fl_Widget*,void *v) { ((Sheet*)v)->event_callback2(); }
   static void input_cb(Fl_Widget* sp,void* v) { ((Sheet*)v)->set_value_hide(); }

public:
   Sheet(int ,int ,int ,int ,const char* );
   ~Sheet();
   int      handle (int e);
   void     clearTable();
   void     enabled( bool );
   float    getValue(int, int);
   void     setValue(int , int , float );
   void     setIRow(Fl_Int_Input* );
   bool     is_setIRow();
   void     setICol(Fl_Int_Input* );
   void     rows2input();
   void     cols2input();
   void     input2rows();
   void     input2cols();
   int      getRows();
   int      getCols();
   void     setRows( int );
   void     setCols( int );
   void     setPrecision( int );
   int      getPrecision();
};

#endif
