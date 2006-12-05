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
    TGCombobox::TGCombobox(TGControl *parent, int x1, int y1, int x2, int y2)
        : TGInputbox(parent,x1,y1,x2,y2)
    {
        m_height=0;
    }

    //-----------------------------------------------------------------------
    //                          T G C o m b o b o x
    //-----------------------------------------------------------------------
    TGCombobox::~TGCombobox()
    {
    }

    //-----------------------------------------------------------------------
    //                           s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGCombobox::setBounds(int x1, int y1, int x2, int y2)
    {
        m_height = y2-y1;
        
        TGInputbox::setBounds(x1, y1, x2-m_height, y2);

    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGCombobox::render()
    {
        if(isRenderCached())
            return;

        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);
        TGInputbox::render();
        if (mouseOverControl  || hasKeyboardFocus(this))
            color(m_theme.getFrameFocusedColour());
        else
            color(m_theme.getFrameColour());

        drawRect(x2, y1, x2 + m_height, y2);


    }

}