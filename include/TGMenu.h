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

    class TGMenuControl;
    class TGMenu;

    //-----------------------------------------------------------------------
    //                          T G M e n u I t e m
    //-----------------------------------------------------------------------
    class TGMenuItem : public TGControl
    {
    public:
        TGString    		    caption;
        TGMenuControl*          menuControl;
        TGMenu*                 subMenu;

        TGMenuItem(TGControl *owner, TGString caption);
        virtual ~TGMenuItem();

        virtual TGMenuItem *addItem(TGString caption);
        virtual void clear();
        virtual void setTheme(TGTheme theme,bool updateChildren=false);

        virtual void render();
        virtual TGString getControlType() {return "TGMenuItem";};

        virtual void onMouseEnter();
        virtual void onMouseExit(int x, int y);

        virtual void onMouseDown(int x, int y, int b){};
        virtual void onMouseUp(int x, int y, int b);
    };

    //-----------------------------------------------------------------------
    //                             T G M e n u 
    //-----------------------------------------------------------------------
    class TGMenu : public TGControl
    {
    public:
        TGMenuControl*          rootMenuControl;
        TGMenuControl*          m_menuControl;

        TGMenu(TGControl* parent);
        virtual ~TGMenu();

        virtual void setTheme(TGTheme theme,bool updateChildren=false);

        virtual TGMenuItem *addItem(TGString caption);
        virtual void clear();
        virtual void run(int x=-10000, int y=-10000)=0;
        virtual void cancel();
        virtual TGString getControlType() {return "TGMenu";};
    };

    //-----------------------------------------------------------------------
    //                        T G M e n u C o n t r o l
    //-----------------------------------------------------------------------
    class TGMenuControl : public TGControl
    {
    public:
        TGMenu*                 m_menu;
        int			            iconPad;

        TGMenuControl(TGControl *owner=NULL);
        virtual ~TGMenuControl();

        virtual void calcSize();

        virtual void layout();
        virtual void render();
        virtual TGString getControlType() {return "TGMenuControl";};

        virtual void getSubOffsets(TGMenuItem* item, int& dx, int& dy);

        virtual void onFocusExit();
    };

    //-----------------------------------------------------------------------
    //                       T G M e n u b a r C o n t r o l
    //-----------------------------------------------------------------------
    class TGMenubarControl : public TGMenuControl
    {
    public:
        TGMenu*                 m_menu;
        int			            iconPad;

        TGMenubarControl(TGControl *owner=NULL);
        virtual ~TGMenubarControl();

        virtual void calcSize();

        virtual void layout();
        virtual void render();
        virtual TGString getControlType() {return "TGMenubarControl";};
        virtual void getSubOffsets(TGMenuItem* item, int& dx, int& dy);

        virtual void onFocusExit();
    };

}
#endif
