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

#ifndef _MCONFIG_H
#define _MCONFIG_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>

#include <FL/fl_ask.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Multiline_Output.H>


struct datacfg {
   int   rowMatrixA;
   int   colMatrixA;
   int   precisionA;
   int   rowMatrixB;
   int   colMatrixB;
   int   precisionB;
   int   precisionC;
   int   fdel;
   int   tdel;
   
   bool operator == (const datacfg &) const;
} ;


datacfg  read_configfile  ( );
int      write_configfile ( datacfg );

class wPref : public Fl_Double_Window {
    Fl_Box            *o1 ;
    Fl_Spinner        *mA ;
    Fl_Spinner        *mB ;
    Fl_Spinner        *mC ;
    Fl_Box            *o2 ;
    Fl_Choice         *fdel;
    Fl_Choice         *tdel;
    Fl_Return_Button  *rbutton;
    Fl_Button         *cbutton;

    datacfg		dt_wPref;

protected:
    void		setValues2dt();
    static void cb_button(Fl_Widget *w, void *data) {
    	wPref *win = (wPref*)data;
        if ( strcmp(w->label(), "&OK") == 0 ) {
        	win->setValues2dt();
        	win->hide();
        } else if ( strcmp(w->label(), "&Cancel") == 0 ) {
        	win->hide();                                // hide form (no save)
        }
    }

public:
   wPref(int ,int ,const char* );
   ~wPref();
   void		setPref( datacfg );
   datacfg	getPref();

};

#endif
