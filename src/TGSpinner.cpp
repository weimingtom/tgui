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
#include <tgui.h>
namespace TGUI
{

    //-----------------------------------------------------------------------
    //                          T G C o m b o b o x
    //-----------------------------------------------------------------------
    TGSpinner::TGSpinner(TGControl *parent, int x1, int y1, int x2, int y2)
        : TGEditbox(parent,x1,y1,x2,y2)
    {
        m_height=0;
     
    }

    //-----------------------------------------------------------------------
    //                          T G C o m b o b o x
    //-----------------------------------------------------------------------
    TGSpinner::~TGSpinner()
    {
    }

    //-----------------------------------------------------------------------
    //                           s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGSpinner::setBounds(int x1, int y1, int x2, int y2)
    {
        m_height = y2-y1;
        
        TGEditbox::setBounds(x1, y1, x2-m_height, y2);
    }

    //-----------------------------------------------------------------------
    //                       p o i n t I n C o n t r o l
    //-----------------------------------------------------------------------
    bool TGSpinner::pointInControl(float x, float y)
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        x2 += m_height;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
            return true;
        return false;
    }

    //-----------------------------------------------------------------------
    //                            c h i l d A t
    //-----------------------------------------------------------------------
    TGControl* TGSpinner::childAt(float x, float y)
    {
        return this;
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGSpinner::onMouseDown(int x, int y, int b)
    {
        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);
        x1 = x2;
        x2 += m_height;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
        {
            return;
        }

        TGEditbox::onMouseDown(x, y, b);
    }

    //-----------------------------------------------------------------------
    //                      s e t C o l o u r T h e m e
    //-----------------------------------------------------------------------
    void TGSpinner::setColourTheme(TGColourTheme theme,bool updateChildren)
    {
        TGControl::setColourTheme(theme,updateChildren);
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGSpinner::render()
    {
        if(isRenderCached())
            return;

        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);
        TGEditbox::render();
        TGSBrush brush;
        if (mouseOverControl  || hasKeyboardFocus(this))
            brush = m_theme.getFrameFocusedBrush();
        else
            brush = m_theme.getFrameBrush();

        drawRect(x2, y1, x2 + m_height, y2, brush);

        drawTri(x2+2,y1+7, x2+m_height-3, y2-7,brush, 0);

        /*
        if(m_listbox->isVisible())
        {
            int x1,y1,x2,y2;
            m_listbox->getBounds(x1, y1, x2, y2);
            color(m_listbox->getColourTheme().getBase());
            fillRect(x1,y1,x2,y2);

        }
        */
    }

}