//-----------------------------------------------------------------------------
// This source file is part of TGUI (Tiny GUI)
//
// Copyright (c) 2006 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal 
// in the Software without restriction, including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
// of the Software, and to permit persons to whom the Software is furnished to 
// do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
// THE SOFTWARE.
//-----------------------------------------------------------------------------
#ifndef __TGMENU_H__
#define __TGMENU_H__

namespace TGUI
{

    struct TGMenuItem : public TGControl
    {
        string    		        caption;
        TGImage*                image;
        struct TGMenuControl*   menuControl;
        struct TGPopupMenu*     subMenu;

        TGMenuItem(TGControl *owner, string caption, TGImage *image=NULL);
        virtual ~TGMenuItem();

        virtual TGMenuItem *addItem(string caption, TGImage *image=NULL);
        virtual void clear();

        virtual void render();
        virtual void onMouseEnter();
        virtual void onMouseDown(int x, int y, int b){};
        virtual void onMouseUp(int x, int y, int b);
    };

    struct TGMenuControl : public TGControl
    {
        struct TGPopupMenu*     popupMenu;
        int			            iconPad;

        TGMenuControl(TGControl *owner);
        virtual ~TGMenuControl();

        virtual void calcSize();

        virtual void layout();
        virtual void render();

        virtual void onFocusExit();
    };

    struct TGPopupMenu
    {
        TGMenuControl*          rootMenuControl;
        TGMenuControl*          menu;

        TGPopupMenu();
        virtual ~TGPopupMenu();

        virtual TGMenuItem *addItem(string caption, TGImage *image=NULL);
        virtual void clear();
        virtual void run(int x=-10000, int y=-10000);
        virtual void cancel();
    };
}
#endif
