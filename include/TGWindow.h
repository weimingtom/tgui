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
#ifndef __TGWINDOW_H__
#define __TGWINDOW_H__
namespace TGUI
{


    class TGWindow : public TGControl
    {
    protected:
        string			m_caption;
        bool            m_isTabbedCaption;
        bool			m_moving;
        bool			m_resizing;
        bool			m_resizeable;
        bool            m_movable;
        bool            m_titlebarEnabled;
        int             m_titlebarHeight;

    public:
        int			    mX, mY;
        TGPopupMenu*    menu;

        TGWindow(string caption="");
        TGWindow(TGScreen *screen,string caption="");
        virtual ~TGWindow();

        virtual void setCaption(string newCaption);
        virtual bool pointInControl(float x, float y);
        virtual bool pointInCaption(float x, float y);
        virtual void setResizeEnabled(bool value) {m_resizeable = value;};
        virtual bool getResizeEnabled() {return m_resizeable;};
        virtual void setMoveEnabled(bool value) {m_movable = value;};
        virtual bool getMoveEnabled() {return m_movable;};
        virtual void setTitlebarEnabled(bool value) {m_titlebarEnabled = value;};
        virtual bool getTitlebarEnabled() {return m_titlebarEnabled;};
        virtual void setTitlebarHeight(int value) {m_titlebarHeight = value;};
        virtual int getTitlebarheight() {return m_titlebarHeight;};

        virtual void render();

        virtual void onMouseDown(int x, int y, int b);
        virtual void onMouseMoved(int x, int y);
        virtual void onMouseUp(int x, int y, int b);
        virtual void onMouseEnter();
        virtual void onMouseExit();

    };
}
#endif
