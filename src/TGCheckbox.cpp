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
    //                          T G C h e c k b o x
    //-----------------------------------------------------------------------
    TGCheckbox::TGCheckbox(TGControl *parent, int x1, int y1, int x2, int y2,
        string caption)
        : TGControl(parent)
    {
        setBounds(x1, y1, x2, y2);
        m_caption = caption;
        m_hover = m_pushed = false;
        m_checked.setControl(this);
        m_checked.set(false);
    }

    //-----------------------------------------------------------------------
    //                         ~ T G C h e c k b o x
    //-----------------------------------------------------------------------
    TGCheckbox::~TGCheckbox()
    {
    }

    //-----------------------------------------------------------------------
    //                           s e t C a p t i o n
    //-----------------------------------------------------------------------
    void TGCheckbox::setCaption(string newCaption)
    {
        m_caption = newCaption;
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGCheckbox::render()
    {
        int			x1, y1, x2, y2;
        FrameStyle	fs = FS_FLAT;
        getBounds(x1, y1, x2, y2);

        if (m_hover)
            fs = m_pushed?FS_LOWERED:FS_RAISED;
        else
            fs = FS_FLAT;

        //drawFrame(x1, y1 + 4, x1 + 12, y2 - 4, fs);
        drawFrame(x1, y1 + 4, x1 + 12, y2 - 4, fs);

        if (m_checked.get())
        {
            drawLine(x1, y1 + 4, x1 + 12, y2 - 4);
            drawLine(x1 + 12, y1 + 4, x1, y2 - 4);
        }

        if (focused())
        {
            color(m_theme.getFrameColour());
            drawRect(x1 + 14, y1, x2, y2);
            color(m_theme.getTextColour());
        }
        else
            if (m_hover)
                color(m_theme.getTextFocusedColour());
            else
                color(m_theme.getTextColour());

        drawString(x1 + 16,
            (y2-y1 + 1)/2 + y1 - (int)stringHeight()/2,
            m_caption);
    }

    //-----------------------------------------------------------------------
    //                            s e t S t a t e
    //-----------------------------------------------------------------------
    void TGCheckbox::setState(bool checked)
    {
        if (checked != m_checked.get())
        {
            m_checked.set(checked);
            fireEvent(TGEvent::Modified,TGEventArgs(this));
        }
    }

    //-----------------------------------------------------------------------
    //                         o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGCheckbox::onMouseDown(int x, int y, int b)
    {
        focus();
        if (b == LeftButton)
        {
            setMouseTrackingControl(this);
            m_pushed = true;
        }
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGCheckbox::onMouseUp(int x, int y, int b)
    {
        if (!focused())
            return;
        if (b == LeftButton && m_pushed)
        {
            setMouseTrackingControl(NULL);
            if (m_hover)
            {
                m_checked.set(!m_checked.get());
                fireEvent(TGEvent::Modified,TGEventArgs(this));
            }
        }
        m_pushed = false;
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e E n t e r
    //-----------------------------------------------------------------------
    void TGCheckbox::onMouseEnter()
    {
        TGControl::onMouseEnter();
        m_hover = true;
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e E x i t 
    //-----------------------------------------------------------------------
    void TGCheckbox::onMouseExit()
    {
        TGControl::onMouseExit();
        m_hover = false;
    }
}