//-----------------------------------------------------------------------------
// This source file is part of TGUI (Tiny GUI)
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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
#include <tgui.h>

namespace TGUI
{
    //-----------------------------------------------------------------------
    //                             T G S c r e e n
    //-----------------------------------------------------------------------
    TGScreen::TGScreen(TGControl* parent, TGString name)
        : TGControl(parent,name)
    {
        width = getRenderer()->getWidth();
        height = getRenderer()->getHeight();
        x1 = y1 = 0;
        x2 = width;
        y2 = height;
        mouseX = 0;
        mouseY = 0;
    }

    //-----------------------------------------------------------------------
    //                            ~ T G S c r e e n
    //-----------------------------------------------------------------------
    TGScreen::~TGScreen()
    {
        
    }

    //-----------------------------------------------------------------------
    //                             a c t i v a t e
    //-----------------------------------------------------------------------
    TGScreen *TGScreen::activate()
    {
        TGScreen	*prevScreen = getActiveScreen();
        width = getRenderer()->getWidth();
        height = getRenderer()->getHeight();
        TGSystem::getSingleton().setActiveScreen(this);
        redraw();
        return prevScreen;
    }

    //-----------------------------------------------------------------------
    //                            d e a c t i v a t e
    //-----------------------------------------------------------------------
    void TGScreen::deactivate()
    {
        TGSystem::getSingleton().setActiveScreen(NULL);
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E n t e r
    //-----------------------------------------------------------------------
    void TGScreen::onMouseEnter()
    {
        m_mouseOverControl = true;
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E x i t
    //-----------------------------------------------------------------------
    void TGScreen::onMouseExit()
    {
        m_mouseOverControl = false;
    }
}