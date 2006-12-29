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
    //                            T G L a b e l
    //-----------------------------------------------------------------------
    TGLabel::TGLabel(TGControl *parent, TGString name, TGString text)
        : TGControl(parent, name)
    {
        m_alignment = alLeft;
        m_text = text;
        m_textWidth = stringWidth(m_text);
        resize(m_textWidth, stringHeight());
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
    void TGLabel::setText(TGString newText)
    {
        m_text = newText;
        m_textWidth = stringWidth(m_text);
        resize(m_textWidth, stringHeight());
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGLabel::render()
    {
        if(isRenderCached())
            return;

        int	x1, y1, x2, y2, ax;
        getBounds(x1, y1, x2, y2);

        int width = x2-x1;
        switch(m_alignment)
        {
        case alLeft:
            ax = 0;
            break;
        case alCenter:
            ax = (width / 2) - (m_textWidth / 2);
            break;
        case alRight:
            ax = width - m_textWidth - 1;
            break;
        };

        TGSBrush brush = m_theme.getTextBrush();
        drawString(x1+ax, y1, m_text, brush);
    }

}