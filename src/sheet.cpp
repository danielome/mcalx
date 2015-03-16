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


#include <iostream>
#include "sheet.h"

using namespace std;

/* ----------------- */
void msg(const char *mess) {
   cout << mess << endl;
}

/* ----------------- */
char* itoa(int val){
   static char buf[12] = {0};
   int i = 10;
   for(; val && i ; --i, val /= 10)
      buf[i] = "0123456789abcdef"[val % 10];
   return &buf[i+1];
}

/* ----------------- */
Sheet::Sheet(int X,int Y,int W,int H,const char* L=0) :
   Fl_Table(X,Y,W,H-40,L) {
      callback(&event_callback, (void*)this);
      when(FL_WHEN_NOT_CHANGED | when());
      enable = true;
      havefocus = false;

      // Create input widget that we'll use whenever user clicks on a cell
      input = new Fl_Float_Input(W/2,H/2,0,0);
      input->hide();
      input->callback(input_cb, (void*) this);
      input->when(FL_WHEN_ENTER_KEY_ALWAYS);
      input->maximum_size(15);
      input->color(FL_YELLOW);
      input->textsize(FONT_SIZE);
      input->textfont(FL_HELVETICA | FL_BOLD);

      for (int c = 0; c < MAX_COLS; c++)
         for (int r = 0; r < MAX_ROWS; r++)
            values[r][c] = 0;		   // initialize cells
      end();

      row_edit = col_edit = 0;
      set_selection(0, 0, 0, 0);
      row_header( 0 );
      col_header( 0 );
      row_height_all( 25 );
      col_width_all( 65 );

      inpRow=NULL;
      inpCol=NULL;

      rows( 3 );
      cols( 3 );
}

/* ----------------- */
Sheet::~Sheet() { msg("juaz");}

/* ----------------- */
void Sheet::enabled( bool b ) { enable = b; }

/* ----------------- */
double Sheet::getValue(int r, int c) { return values[r][c]; }
/* ----------------- */
void   Sheet::setValue(int r, int c, double v) { values[r][c] = v; }

/* ----------------- */
void Sheet::set_value_hide() {
      values[row_edit][col_edit] = atof(input->value());
      input->hide();
      window()->cursor(FL_CURSOR_DEFAULT);
      take_focus();
}

/* ----------------- */
void Sheet::start_editing(int R, int C) {

   if ( enable ) {
      char  s[30];
      int   X,Y,W,H;

      row_edit = R;				// Now editing this row/col
      col_edit = C;

      set_selection(R,C,R,C);
      find_cell(CONTEXT_CELL, R,C, X,Y,W,H);
      //cout << "R: " << R << endl;
      //cout << "C: " << C << endl;
      //cout << "X: " << X << endl;
      //cout << "Y: " << Y << endl;
      //cout << "W: " << W << endl;
      //cout << "H: " << H << endl;
      //cout << "find: " << k << endl;
      //cout << "----------------: " << endl;
      input->resize(X,Y,W,H);
      sprintf(s, "%0.3f", values[R][C]);
      input->value(s);
      input->position(0, strlen(s));
      input->show();
      input->take_focus();
   }
}

/* ----------------- */
void Sheet::done_editing() { if (input->visible()) set_value_hide(); }

/* ----------------- */
void Sheet::draw_cell(TableContext context, int R,int C, int X,int Y,int W,int H) {
   switch ( context ) {
      case CONTEXT_STARTPAGE:
         break;

      case CONTEXT_CELL:
         if ( R == row_edit &&
              C == col_edit &&
              input->visible() ) { return; }
         // Background
         //if (is_selected(R,C) && enable && havefocus)
         //cout << "context R: " << R << endl;
         //cout << "context C: " << C << endl << endl << endl;
         if (is_selected(R,C) )
            fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, FL_YELLOW);
         //fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, is_selected(R,C) ? FL_YELLOW : FL_WHITE);
         else
            fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, FL_WHITE);
         // Text
         fl_push_clip(X+3, Y+3, W-6, H-6);
         {
            static char s[30];
            fl_color(FL_BLACK);
            fl_font(FL_HELVETICA, 10);		// ..in regular font
            sprintf(s, "%0.4f", (double) values[R][C]); // DANIEL OME
            fl_draw(s, X+3,Y+3,W-6,H-6, FL_ALIGN_RIGHT);
         }
         fl_pop_clip();
         return;
         break;


      case CONTEXT_RC_RESIZE:
         if ( input->visible() ) {
            find_cell(CONTEXT_TABLE, row_edit, col_edit, X, Y, W, H);
            input->resize(X,Y,W,H);
            init_sizes();
         }
         return;
         break;

      default:
          return;
          break;
   };
}

/* ----------------- */
int Sheet::handle( int event ) {
   switch ( event ) {
      case FL_PUSH:


         //int R;
         //int C;
         //ResizeFlag resizeflag;
         //TableContext cont;
         //cont = cursor2rowcol(R, C, resizeflag);


         //if ( Fl::event_button() == FL_RIGHT_MOUSE ) {
            //Fl_Menu_Item rclick_menu[] = {
                  //{ "Swap matrices A <-> B",   0, swapMatrix, (void*)this, 0, FL_NORMAL_LABEL, 0, 13 },
                  //{ "Identity Matrix",  0, setIdentityMatrix, (void*)this, 0, FL_NORMAL_LABEL, 0, 13 },
                  //{ 0 }
            //};
            //const Fl_Menu_Item *popmenu = rclick_menu->popup(Fl::event_x(), Fl::event_y(), 0, 0, 0);
            //if ( popmenu ) popmenu->do_callback(0, popmenu->user_data());
            //return(1);          // (tells caller we handled this event)
         //}

         if ( Fl::event_button() == 1 ) {
            int wcell = cols() * col_width(0);
            int hcell = rows() * row_height(0);
            int evx = Fl::event_x() - x();
            int evy = Fl::event_y() - y();
            //cout << "x(): " << x() << endl;
            //cout << "y(): " << y() << endl;
            //cout << "w(): " << w() << endl;
            //cout << "h(): " << h() << endl;
            //cout << "-----------------\n";
            //cout << "tox: " << tox << endl;
            //cout << "toy: " << toy << endl;
            //cout << "tow: " << tow << endl;
            //cout << "toh: " << toh << endl;
            //cout << "----------------\n";
            //cout << "tix: " << tix + x()<< endl;
            //cout << "tiy: " << tiy + y()<< endl;
            //cout << "tiw: " << tiw + x()<< endl;
            //cout << "tih: " << tih + y()<< endl;
            //cout << "----------------\n";
            //cout << "ex() " << Fl::event_x() << endl;
            //cout << "ey() " << Fl::event_y() << endl;
            //cout << "----------------\n";
            //cout << "wcell: " << wcell << endl;
            //cout << "hcell: " << hcell << endl;
            //cout << "evx  : " << evx << endl;
            //cout << "evy  : " << evy << endl;
            //cout << ((wcell<=evx) && (evx<tiw)) << endl;
            //cout << ((hcell<=evy) && (evy<tih)) << endl;
            if ( ((wcell<=evx) && (evx<tiw)) ||
                  ((hcell<=evy) && (evy<tih)) ) {
               done_editing();
               return 0; }
         }
         return Fl_Table::handle(event);
         break;

      default:
         return Fl_Table::handle(event);
   };
}

/* ----------------- */
void Sheet::clearTable() {
   for (int row=0; row<MAX_ROWS; row++)
      for (int col=0; col<MAX_COLS; col++)
         values[row][col] = 0;
   redraw();
}

/* ----------------- */
void Sheet::event_callback2() {
   int R = callback_row();
   int C = callback_col();
   TableContext context = callback_context();

   switch ( context ) {
      case CONTEXT_CELL:
         switch (Fl::event()) {
            case FL_PUSH:
               done_editing();
               start_editing(R,C);
               return;
               break;

            case FL_KEYBOARD:				// key press in table?
               if ( Fl::event_key() == FL_Escape ) { exit(0); }
               if ( Fl::event_key() == FL_Tab ) {
                  if ( move_cursor(0, 1) == 0 ) {
                     move_cursor(0, -1000000);
                     if ( move_cursor(1, 0) == 0 )
                        move_cursor(-1000000, 0);
                  }
               }
               done_editing();				// finish any previous editing

               //if ( Fl::event_key() == FL_Home ) {
               //std::cout << "KEY HOME\n";
               //}

               //if (Fl::event_state() && FL_CTRL) {
                  //int key = Fl::event_key();
                  //std::cout << "KEY CTRL: " << key << "\n";
               //}


               switch ( Fl::e_text[0] ) {
                  case '0': case '1': case '2': case '3':	// any of these should start editing new cell
                  case '4': case '5': case '6': case '7':
                  case '8': case '9': case '+': case '-':
                  case '.':
                     start_editing(R,C);			// start new edit
                     input->handle(Fl::event());		// pass typed char to input
                     break;
                  case '\r': case '\n':			// let enter key edit the cell
                     start_editing(R,C);			// start new edit
                     break;
               }
               return;
               break;
         }
         return;
         break;

      case CONTEXT_TABLE:					// A table event occurred on dead zone in table
      case CONTEXT_ROW_HEADER:				// A table event occurred on row/column header
      case CONTEXT_COL_HEADER:
          done_editing();					// done editing, hide
          return;
          break;

      default:
         return;
   }
}
/* ----------------- */
bool Sheet::is_setIRow() { return ((inpRow!=NULL) ? 1 : 0); }
/* ----------------- */
void Sheet::setIRow(Fl_Int_Input* irow) { inpRow = irow; }
/* ----------------- */
void Sheet::setICol(Fl_Int_Input* icol) { inpCol = icol; }
/* ----------------- */
void Sheet::rows2input() { inpRow->value( itoa( rows() ) ); }
/* ----------------- */
void Sheet::cols2input() { inpCol->value( itoa( cols() ) ); }
/* ----------------- */
void Sheet::input2rows() {
   int r = atoi( inpRow->value() );
   if ( (r >= 1) && (r <= MAX_ROWS) )
      rows( r );
   else
      inpRow->value( itoa( rows() ) );

   return;
}
/* ----------------- */
void Sheet::input2cols() {
   int c = atoi( inpCol->value() );
   if ( (c >= 1) && (c <= MAX_COLS) )
      cols( c );
   else
      inpCol->value( itoa( cols() ) );

   return;
}
