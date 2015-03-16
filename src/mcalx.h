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
#ifndef _MCALX_H
#define _MCALX_H

#include <FL/fl_ask.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Multiline_Output.H>
#include <stdlib.h>
#include <stdint.h>

#include "pix/icon.xpm"
#include "logdisplay.h"
#include "sheet.h"
#include "copy.h"
#include "operations.h"
#include "mcalx.h"

struct fButtons {
   int          x;
   int          y;
   int          W;
   int          H;
   const char*  n;
   const char*  ttip;
};

struct mButtons {
   int          x;
   int          y;
   int          W;
   int          H;
   Fl_Menu_Item *mitem;
   const char*  n;
};

const char * msgLicense =
"Mcalx is free software; you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation; either version 2 of the License, or\n\
(at your option) any later version.\n\n\
Mcalx is distributes in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\n\
You should have received a copy of the GNU General Public License\n\
along with Mcalx; if not, write to the Free Software Foundation,Inc.,\n\
59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n";

static void cb_copyMatrix(Fl_Widget* , void* );
static void cb_quit      (Fl_Widget* , void* );
static void cb_aboutMsg  (Fl_Widget* , void* );

Fl_Menu_Item menu_Menu[] = {
   {"&Quit",  0,  cb_quit, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"&About", 0,  cb_aboutMsg, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {0,0,0,0,0,0,0,0,0},
};

Fl_Menu_Item menu_A[] = {
   {"Buffer 1", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 2", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 3", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Clipboard", 0,  cb_copyMatrix, (void*)ACB, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {0,0,0,0,0,0,0,0,0}
};

Fl_Menu_Item menu_B[] = {
   {"Buffer 1", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 2", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 3", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Clipboard", 0,  cb_copyMatrix, (void*)BCB, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {0,0,0,0,0,0,0,0,0}
};

Fl_Menu_Item menu_Copy[] = {
   {"Matrix A",  0, cb_copyMatrix, (void*)CA , 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Matrix B",  0, cb_copyMatrix, (void*)CB , 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Clipboard", 0, cb_copyMatrix, (void*)CCB, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {0,0,0,0,0,0,0,0,0}
};

Fl_Menu_Item menu_Paste[] = {
   {"Matrix A", 0,  0, 0, FL_SUBMENU, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 1", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 2", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 3", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {0,0,0,0,0,0,0,0,0},
   {"Matrix B", 0,  0, 0, FL_SUBMENU, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 1", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 2", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {"Buffer 3", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 12, 0},
   {0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0}
};

#endif
