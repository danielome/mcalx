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

#include "calcu/small.h"
#include "mcalx.h"

static Sheet            *mSheetA, *mSheetB, *mSheetC; /* for show in screen */
static Fl_Float_Input   *escalar;
static Display_Text     *display;

static
Fl_Int_Input* rowcolButton (int X, int Y, int W, int H, const char* L) {
   Fl_Int_Input* w = new Fl_Int_Input(X,Y,W,H, L);
   w->labelfont(1);
   w->labelsize(12);
   w->type(FL_INT_INPUT);
   w->textsize(FONT_SIZE);
   w->align(Fl_Align(FL_ALIGN_TOP));
   w->when(FL_WHEN_RELEASE);
   return w;
}

static
Fl_Button* do_fbutton( fButtons d) {
   //Fl_Button* b = new Fl_Button(d.x, d.y, d.W, d.H, d.n);
   Fl_Scientific_Button* b = new Fl_Scientific_Button(d.x, d.y, d.W, d.H, d.n);
   b->tooltip( d.ttip );
   b->box(FL_GTK_UP_BOX);
   b->labelfont( 1 );
   return b;
}

static
Fl_Menu_Button* do_menubutton( mButtons d) {
   Fl_Menu_Button* m = new Fl_Menu_Button(d.x, d.y, d.W, d.H, d.n);
   m->box(FL_GTK_UP_BOX);
   m->deactivate();  /* For now, until implement buffer */
   m->labelfont( 1 );
   m->menu(d.mitem);
   return m;
}

/* Preferences window */
static
void cb_preferences( Fl_Widget* sp, void* v ) {
   datacfg  dt_pref = *(datacfg *) v;
   datacfg  dt_bak = dt_pref;
/*
   cout << "Antes de cambiar\n";
   cout << dt_pref.precisionA << "\n";
   cout << dt_pref.precisionB << "\n";
   cout << dt_pref.precisionC << "\n";
   cout << dt_pref.fdel << "\n";
   cout << dt_pref.tdel << "\n\n";
*/   
   wPref *w = new wPref( 390, 250, "Preferences" );
   w->setPref(dt_pref);
   w->set_modal();
   w->end();
   w->show();
   while (w->visible()) { Fl::wait(); }   /* Avoid return to main execution */

   dt_pref = w->getPref();
   if ( dt_pref == dt_bak ) return;

   *(datacfg *) v = dt_pref;
   mSheetA->setPrecision(dt_pref.precisionA);
   mSheetB->setPrecision(dt_pref.precisionB);
   mSheetC->setPrecision(dt_pref.precisionC);

   return;
}

/* Quit program */
static
void cb_quit(Fl_Widget* sp, void* v) {

   if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape) { return; }

   datacfg  dt_pref = *(datacfg *) v;

   dt_pref.rowMatrixA = mSheetA->getRows();
   dt_pref.colMatrixA = mSheetA->getCols();
   dt_pref.precisionA = mSheetA->getPrecision();
   dt_pref.rowMatrixB = mSheetB->getRows();
   dt_pref.colMatrixB = mSheetB->getCols();
   dt_pref.precisionB = mSheetB->getPrecision();
   dt_pref.precisionC = mSheetC->getPrecision();

   write_configfile( dt_pref );

   exit(0);
}

/* end Quit program */
/* Msg About */
static
void cb_aboutMsg(Fl_Widget* sp, void* v) {
   int x = 440;
   Fl_Double_Window* w = new Fl_Double_Window(x, 255, "About Mcalx");
   {
      Fl_Tabs* tab = new Fl_Tabs(10, 10, x-20, 235);
      {
         Fl_Group* o = new Fl_Group(10, 35, x-20, 210, "Version");
         o->box(FL_GTK_UP_BOX);
         o->labelsize(12);
         {
            Fl_Box* box = new Fl_Box(90, 45, x-110, 30, "Mcalx");
            box->color((Fl_Color)12);
            box->selection_color(FL_DARK1);
            box->labelfont(1);
            box->labelsize(22);
            box->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
         }
         {
            Fl_Box* box = new Fl_Box(90, 75, x-110, 30, "Matrix Calculator for LinuX");
            box->color((Fl_Color)12);
            box->selection_color(FL_DARK1);
            box->labelfont(1);
            box->labelsize(14);
            box->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
         }
         {
            Fl_Box* box = new Fl_Box(90, 105, x-110, 120, "Version: 0.1.5.1\nAugust 2020\n\nBeta version\nThis program is still in development\n\n(c) 2015-2020 Daniel R. Ome");
            box->color((Fl_Color)12);
            box->selection_color(FL_DARK1);
            box->labelsize(12);
            box->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
         }
         {
            Fl_Box* pixbox = new Fl_Box(20, 60, 100, 85);
            static Fl_Pixmap image_icon(icon_xpm);
            pixbox->image(image_icon);
         }
         o->end();
      }
      {
         Fl_Group* o = new Fl_Group(10, 35, x-20, 210, "License");
         o->box(FL_GTK_UP_BOX);
         o->labelsize(12);
         {
            Fl_Multiline_Output* o = new Fl_Multiline_Output(20, 45, x-40, 190);
            o->textsize(11);
            o->value( msgLicense );
         }
         o->end();
      }
      {
         Fl_Group* o = new Fl_Group(10, 35, x-20, 210, "Credits");
         o->box(FL_GTK_UP_BOX);
         o->labelsize(12);
         {
            Fl_Box* box = new Fl_Box(90, 45, x-110, 30, "Mcalx");
            box->color((Fl_Color)12);
            box->selection_color(FL_DARK1);
            box->labelfont(1);
            box->labelsize(22);
            box->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
         }
         {
            Fl_Box* box = new Fl_Box(90, 75, x-110, 30, "Matrix Calculator for LinuX");
            box->color((Fl_Color)12);
            box->selection_color(FL_DARK1);
            box->labelfont(1);
            box->labelsize(14);
            box->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
         }
         {
            Fl_Box* box = new Fl_Box(90, 105, x-110, 120, "Version: 0.1.5.1\nAugust 2020\n\nBeta version\nThis program is still in development\n\n(c) 2015-2020 Daniel R. Ome");
            box->color((Fl_Color)12);
            box->selection_color(FL_DARK1);
            box->labelsize(12);
            box->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
         }
         {
            Fl_Box* pixbox = new Fl_Box(20, 60, 100, 85);
            static Fl_Pixmap image_icon(icon_xpm);
            pixbox->image(image_icon);
         }
         o->end();
      }
      tab->end();
   }
   w->set_modal();
   w->end();
   w->show();
}
/* End Msg About */

/* Callbacks for buttons */
static void cb_changeRow(Fl_Widget* sp, void* v) { ((Sheet* )v)->input2rows(); }

static void cb_changeCol(Fl_Widget* sp, void* v) { ((Sheet* )v)->input2cols(); }

/* Callbacks for buttons */
static void cb_addMatrix(Fl_Widget* sp, void*) { basicOp(mSheetA, mSheetB, mSheetC, ADD); } /* x */

static void cb_subMatrix(Fl_Widget* sp, void*) { basicOp(mSheetA, mSheetB, mSheetC, SUB); } /* x */

static void cb_mulMatrix(Fl_Widget* sp, void*) { basicOp(mSheetA, mSheetB, mSheetC, MUL); } /* x */

static void cb_numMatrix(Fl_Widget* sp, void* m) { numOp((Sheet*)m, atof(escalar->value()), mSheetC); } /* x */

static void cb_powMatrix(Fl_Widget* sp, void* m) { powOp((Sheet*)m, atof(escalar->value()), mSheetC); } /* x */

static void cb_transpose(Fl_Widget* sp, void* m) { transposeMatrix((Sheet*)m, mSheetC); } /* x */

static void cb_adjMatrix(Fl_Widget* sp, void* m) { adjunteMatrix((Sheet*)m, mSheetC); }

static void cb_identity(Fl_Widget* sp, void* m) { identityMatrix((Sheet*)m); } /* x */

static void cb_GaussJordan(Fl_Widget* sp, void* m) { GaussJordanMatrix((Sheet*)m, mSheetC); }

static void cb_invMatrix(Fl_Widget* sp, void* m) { invMatrix((Sheet*)m, mSheetC); } /* x */

static void cb_detMatA(Fl_Widget* sp, void* m) { detMatrix(mSheetA, display, 'A'); } /* x */
static void cb_detMatB(Fl_Widget* sp, void* m) { detMatrix(mSheetB, display, 'B'); } /* x */

static void cb_rankA(Fl_Widget* sp, void* m) { rankMatrix(mSheetA, display, 'A'); }
static void cb_rankB(Fl_Widget* sp, void* m) { rankMatrix(mSheetB, display, 'B'); }

static void cb_clearSheet(Fl_Widget* sp, void* m){ ((Sheet*) m)->clearTable(); } /* x */

static void cb_copyMatrix(Fl_Widget* sp, void* v) {
   //long op = (long) v;
   switch ( (long) v ) {
      case  AB: Sheet2Sheet(mSheetA, mSheetB); break;
      case  BA: Sheet2Sheet(mSheetB, mSheetA); break;
      case  CA: Sheet2Sheet(mSheetC, mSheetA); break;
      case  CB: Sheet2Sheet(mSheetC, mSheetB); break;
      case ACB: copyC2CB(mSheetA); break;
      case BCB: copyC2CB(mSheetB); break;
      case CCB: copyC2CB(mSheetC); break;
      default: break;
   };
   return;
}

static void cb_swapMatrix(Fl_Widget* sp) { swapMatrix(mSheetA, mSheetB); }

static void cb_clearDisplay(Fl_Widget* sp, void* v) { Display_Text* td = (Display_Text*) v; td->clear(); return; }

static
void cb_doCalc(Fl_Widget* sp, void* v) {
   Fl_Input*   inp = (Fl_Input*) sp;
   int         len = inp->size();

   if ( len ) {
      Display_Text* display = (Display_Text*) v;
      char        *ret, *str;
      int         c;

      str = new char [len+1];
      strncpy( str, inp->value(), len+1 );

      display->appendBuf( str );

      c = eval(str, &ret);

      if ( c == 0 ) {
         display->appendBuf( "\n    = " );
         display->appendBuf( ret );
      } else {
         display->appendBuf( "\n  --> Error in expression" );
      }

      display->appendBuf( "\n\n" );
      display->goEnd();

      inp->cut(0, len);

      delete [] str;
   }
   return;
}

/* ---- main function ---- */
int main() {

   int      w_x=880, w_y = 505;
   Fl_Group *fgroup, *goperations, *gsheet, *gcopy, *gdisplay;

   /* Read the config file */
   datacfg  dt = read_configfile();

/* Menu item */
Fl_Menu_Item menu_Menu[] = {
   {"&File", 0, 0, 0, FL_SUBMENU},
      {"&Preferences", FL_ALT+'p', cb_preferences, (void *)&dt, FL_MENU_DIVIDER, FL_NORMAL_LABEL, 0, 0, 0},
      {"&Quit",  FL_ALT+'q',  cb_quit, (void *)&dt, 0, FL_NORMAL_LABEL, 0, 0, 0},
   {0},
   {"&About", 0,  cb_aboutMsg, 0, 0, FL_NORMAL_LABEL, 0, 0, 0},
   {0,0,0,0,0,0,0,0,0},
};
/* End of Menu item*/

   Fl::option(Fl::OPTION_ARROW_FOCUS, 1);

   Fl_Double_Window *win = new Fl_Double_Window(w_x, w_y, "MCalx");
   win->begin();
   {
      Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 640, 30);
      o->down_box(FL_GTK_UP_FRAME);
      o->labeltype(FL_ENGRAVED_LABEL);
      o->menu(menu_Menu);

      fgroup = new Fl_Group(10, 35, w_x-20, 255);
      fgroup->box(FL_GTK_UP_BOX);
      {
         gsheet = new Fl_Group(20, 45, w_x-40, 235);
         gsheet->box(FL_ENGRAVED_FRAME);
         {
            mSheetA = new Sheet( 30, 70, 260, 235, "MatrixA");
            mSheetB = new Sheet(310, 70, 260, 235, "MatrixB");
            mSheetC = new Sheet(590, 70, 260, 235, "Result");
            mSheetC->enabled( false );
            /* Set the sheets */
            mSheetA->setRows( dt.rowMatrixA );
            mSheetA->setCols( dt.colMatrixA );
            mSheetA->setPrecision( dt.precisionA );
            mSheetB->setRows( dt.rowMatrixB );
            mSheetB->setCols( dt.colMatrixB );
            mSheetB->setPrecision( dt.precisionB );
            mSheetC->setPrecision( dt.precisionC );
         }
         gsheet->end();
         fgroup->resizable(gsheet);
      }
      fgroup->end();

      goperations = new Fl_Group(10, 295, 380, 200);
      goperations->box(FL_ENGRAVED_FRAME);
      {
         Fl_Int_Input   *rowA, *colA;
         Fl_Int_Input   *rowB, *colB;

         rowA  = rowcolButton(20 , 320, 45, 20, "Row A");
         colA  = rowcolButton(70 , 320, 45, 20, "Col A");
         rowA->callback(cb_changeRow, (void*) mSheetA);
         colA->callback(cb_changeCol, (void*) mSheetA);
         mSheetA->setIRow( rowA ); mSheetA->setICol( colA );
         mSheetA->rows2input(); mSheetA->cols2input();

         rowB  = rowcolButton(135, 320, 45, 20, "Row B");
         colB  = rowcolButton(185, 320, 45, 20, "Col B");
         rowB->callback(cb_changeRow, (void*) mSheetB);
         colB->callback(cb_changeCol, (void*) mSheetB);
         mSheetB->setIRow( rowB ); mSheetB->setICol( colB );
         mSheetB->rows2input(); mSheetB->cols2input();

         escalar= new Fl_Float_Input(250, 320, 45, 20, "Num");
         escalar->labelfont(1);
         escalar->labelsize(12);
         escalar->align(Fl_Align(FL_ALIGN_TOP));
         escalar->textsize(FONT_SIZE);
         escalar->value( itoa(2) );

         Fl_Button*  buttons[22];

         fButtons style[] = {
            {  20, 350, 65, 25, "Tr A","Transpose A" },        // 0
            {  90, 350, 65, 25, "A^{-1}","Inverse A" },         // 1
            { 160, 350, 65, 25, "adj(A)", "adjunte A" },       // 2
            { 230, 350, 65, 25, "Clear A","Clear Matrix A" },  // 3

            {  20, 380, 65, 25, "|A|", "Determinante A" },     // 4
            {  90, 380, 65, 25, "r(A)", "rank A" },            // 5
            { 160, 380, 65, 25, "Id A", "Identity A" },        // 6
            { 230, 380, 65, 25, "Gauss", "Gaus-Jordan A" },    // 7

            {  20, 420, 65, 25, "Tr B","Transpose B" },        // 8
            {  90, 420, 65, 25, "B^{-1}","Inverse B" },         // 9
            { 160, 420, 65, 25, "adj(B)", "adjunte B" },       // 10
            { 230, 420, 65, 25, "Clear B","Clear Matrix B" },  // 11

            {  20, 450, 65, 25, "|B|", "Determinante B" },     // 12
            {  90, 450, 65, 25, "r(B)", "rank B" },            // 13
            { 160, 450, 65, 25, "Id B", "Identity B" },        // 14
            { 230, 450, 65, 25, "Gauss", "Gaus-Jordan B" },    // 15

            { 315, 310, 65, 25, "A + B",  "A add B" },         // 16
            { 315, 340, 65, 25, "A - B",  "A diff B" },        // 17
            { 315, 370, 65, 25, "A x B",  "A mul B" },         // 18
            { 315, 400, 65, 25, "A * N",  "A mul Number" },    // 19
            { 315, 430, 65, 25, "A ^ N",  "A power Number" },  // 20
            { 315, 460, 65, 25, "B * N",  "B mul Number" },    // 21
         };

         for (int i=0; i<22; i++) { buttons[i] = do_fbutton( style[i] ); }

         buttons[ 0]->callback(cb_transpose, (void*) mSheetA);
         buttons[ 1]->callback(cb_invMatrix, (void*) mSheetA);
         buttons[ 2]->callback(cb_adjMatrix, (void*) mSheetA);
         buttons[ 3]->callback(cb_clearSheet, (void*) mSheetA);
         buttons[ 4]->callback(cb_detMatA, (void*) mSheetA);
         buttons[ 5]->callback(cb_rankA, (void*) mSheetA);
         buttons[ 6]->callback(cb_identity, (void*) mSheetA);
         buttons[ 7]->callback(cb_GaussJordan, (void*) mSheetA);

         buttons[ 8]->callback(cb_transpose, (void*) mSheetB);
         buttons[ 9]->callback(cb_invMatrix, (void*) mSheetB);
         buttons[10]->callback(cb_adjMatrix, (void*) mSheetB);
         buttons[11]->callback(cb_clearSheet, (void*) mSheetB);
         buttons[12]->callback(cb_detMatB, (void*) mSheetB);
         buttons[13]->callback(cb_rankB, (void*) mSheetB);
         buttons[14]->callback(cb_identity, (void*) mSheetB);
         buttons[15]->callback(cb_GaussJordan, (void*) mSheetB);

         buttons[16]->callback(cb_addMatrix);
         buttons[17]->callback(cb_subMatrix);
         buttons[18]->callback(cb_mulMatrix);
         buttons[19]->callback(cb_numMatrix, (void*) mSheetA);
         buttons[20]->callback(cb_powMatrix, (void*) mSheetA);
         buttons[21]->callback(cb_numMatrix, (void*) mSheetB);

         goperations->resizable(0);
      }
      goperations->end();

      /* ------------------------- */
      gcopy = new Fl_Group(400, 295, 155, 200);
      gcopy->box(FL_ENGRAVED_FRAME);
      {
         Fl_Button*  buttons[3];

         fButtons style[] = {
            { 410, 305,  65, 25, "A -> B","Copy A to B" },         // 0
            { 480, 305,  65, 25, "B -> A","Copy B to A" },         // 1
            { 410, 335, 135, 25, "Swap AB", "Swap Matrices A B" }, // 2
         };

         for (int i=0; i<3; i++) { buttons[i] = do_fbutton( style[i] ); }
         buttons[0]->callback(cb_copyMatrix, (void*) AB);
         buttons[1]->callback(cb_copyMatrix, (void*) BA);
         buttons[2]->callback(cb_swapMatrix);

         Fl_Menu_Button*   mbuttons[4];
         mButtons mstyle[] = {
            { 410, 365, 135, 25, menu_A,"A -> Buffer" },    // 0
            { 410, 395, 135, 25, menu_B,"B -> Buffer" },    // 1
            { 410, 425, 135, 25, menu_Copy,"Copy C to" },   // 2
            { 410, 455, 135, 25, menu_Paste,"Paste to" },   // 3
         };

         for (int i=0; i<4; i++) { mbuttons[i] = do_menubutton( mstyle[i] ); }
         mbuttons[2]->activate();
      }
      gcopy->end();

      /* ------------------------- */
      gdisplay = new Fl_Group(565, 295, 305, 200);
      gdisplay->box(FL_ENGRAVED_FRAME);
      {
         Fl_Input*   inpCalc = new Fl_Input(575, 305, 275, 25);
         inpCalc->tooltip("MiniCalculator");


         Fl_Button*  buttons[2];

         fButtons style[] = {
            { 575, 335,  65, 25, "Clear","Clear Display" },             // 0
            { 645, 335,  65, 25, "Copy","Copy Display to Clipboard" },  // 1
         };

         for (int i=0; i<2; i++) { buttons[i] = do_fbutton( style[i] ); }
         display = new Display_Text(575, 365, 285, 120);
         buttons[0]->callback(cb_clearDisplay, (void*) display);

         inpCalc->callback(cb_doCalc, (void*) display);
         inpCalc->when( FL_WHEN_ENTER_KEY );

         gdisplay->resizable( display );
      }
      gdisplay->end();
   }

   win->xclass("MCalx");

   win->resizable(fgroup);
   win->callback( cb_quit, (void *)&dt );
   win->end();
   win->size_range(w_x, w_y);
   Fl::visual(FL_DOUBLE | FL_INDEX); // Recommended by https://www.fltk.org/doc-1.3/classFl__Double__Window.html#details
   win->show();

   return Fl::run();
}
