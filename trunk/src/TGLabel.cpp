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
    //                            T G L a b e l
    //-----------------------------------------------------------------------
    TGLabel::TGLabel(TGControl *parent, int x, int y, string text)
        : TGControl(parent)
    {
        move(x, y);
        resize(stringWidth(text), stringHeight());
        m_text = text;
    }

    //-----------------------------------------------------------------------
    //                           ~ T G L a b e l
    //-----------------------------------------------------------------------
    TGLabel::~TGLabel()
    {
    }

    //-----------------------------------------------------------------------
    //                            s e t T e x t
    //-----------------------------------------------------------------------
    void TGLabel::setText(string newText)
    {
        m_text = newText;
        resize(stringWidth(m_text), stringHeight());
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGLabel::render()
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);

        color(m_theme.getTextColour());
        drawString(x1, y1, m_text);
    }

}