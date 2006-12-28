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
    //                           T G B u t t o n
    //-----------------------------------------------------------------------
    TGButton::TGButton(TGControl *parent, TGString name, TGString caption) : TGControl(parent,name)
        , m_caption(caption)
        , m_pushed(false)
        , m_highlighted(false)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T G B u t t o n
    //-----------------------------------------------------------------------
    TGButton::~TGButton()
    {
    }

    //-----------------------------------------------------------------------
    //                          s e t C a p t i o n
    //-----------------------------------------------------------------------
    void TGButton::setCaption(TGString newCaption)
    {
        m_caption = newCaption;
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGButton::render()
    {
        if(isRenderCached())
            return;

        int			x1, y1, x2, y2;
        TGFrameStyle	fs = FS_FLAT;
        getBounds(x1, y1, x2, y2);

        if (getMouseOverControl())
            fs = m_pushed?FS_LOWERED:FS_RAISED;
        else
            fs = FS_FLAT;

        drawFrame(x1, y1, x2, y2, fs);

        if (focused())
        {
            drawOwnFocus();
        }

        TGSBrush brush;

        if (m_pushed)
            brush = m_theme.getTextInvertedBrush();
        else
        {
            if(getMouseOverControl())
                brush = m_theme.getTextFocusedBrush();
            else brush = m_theme.getTextBrush();
        }

        x1 = (x2 - x1 + 1)/2 + x1;
        x1 -= stringWidth(m_caption)/2;
        x2 = 0;
        openClip();
        drawString(x1 + x2, (y2-y1 + 1)/2 + y1 - 
            stringHeight()/2, m_caption, brush);
        closeClip();
    }

    //-----------------------------------------------------------------------
    //                         o n M o u s e D o w n 
    //-----------------------------------------------------------------------
    void TGButton::onMouseDown(int x, int y, int b)
    {
        focus();
        if (b == LeftButton)
        {
            setMouseTrackingControl(this);
            m_pushed = true;
            redraw();
        }
    }

    //-----------------------------------------------------------------------
    //                           o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGButton::onMouseUp(int x, int y, int b)
    {
        if (!focused())
            return;
        if (b == LeftButton && m_pushed)
        {
            setMouseTrackingControl(NULL);
            if (getMouseOverControl())
                fireEvent(TGEvent::MouseClicked,TGEventArgs(this));
            redraw();
        }
        m_pushed = false;
    }
}