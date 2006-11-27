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
    //                           T G B u t t o n
    //-----------------------------------------------------------------------
    TGButton::TGButton(TGControl *parent, int x1, int y1, int x2, int y2, 
        string caption, TGImage* image) : TGControl(parent)
    {
        setBounds(x1, y1, x2, y2);
        m_caption = caption;
        m_pushed = m_highlighted = false;
        m_image = image;
        m_autoDeleteImage = true;
    }

    //-----------------------------------------------------------------------
    //                          ~ T G B u t t o n
    //-----------------------------------------------------------------------
    TGButton::~TGButton()
    {
        if (m_autoDeleteImage && m_image)
            delete m_image;
    }

    //-----------------------------------------------------------------------
    //                          s e t C a p t i o n
    //-----------------------------------------------------------------------
    void TGButton::setCaption(string newCaption)
    {
        m_caption = newCaption;
    }

    //-----------------------------------------------------------------------
    //                          s e t I m a g e
    //-----------------------------------------------------------------------
    void TGButton::setImage(TGImage* newImage, bool autoDelete)
    {
        if (m_autoDeleteImage && m_image)
            delete m_image;
        m_image = newImage;
        m_autoDeleteImage = autoDelete;
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGButton::render()
    {
        int			x1, y1, x2, y2;
        FrameStyle	fs = FS_FLAT;
        getBounds(x1, y1, x2, y2);

        if (mouseOverControl)
            fs = m_pushed?FS_LOWERED:FS_RAISED;
        else
            fs = FS_FLAT;

        drawFrame(x1, y1, x2, y2, fs);
        if (m_highlighted)
        {
            color(150, 164, 165);
            fillRect(x1, y1 + 1, x2 - 1, y2);
        }

        if (m_highlighted)
        {
            color(0, 0, 0);
        }
        else
            if (focused())
            {
                drawOwnFocus();
                color(220, 234, 235);
            }
            else
                color(190, 204, 205);
        x1 = (x2 - x1 + 1)/2 + x1;
        if (m_image)
        {
            x1 -= (stringWidth(m_caption) + m_image->getWidth() + 5)/2;
            x2 = m_image->getWidth() + 5;
        }
        else
        {
            x1 -= stringWidth(m_caption)/2;
            x2 = 0;
        }
        drawString(x1 + x2, (y2-y1 + 1)/2 + y1 - 
            stringHeight()/2, m_caption);
        if (m_image)
            m_image->draw(x1, (y2 - y1 + 1)/2 + y1 - m_image->getHeight()/2);
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
            if (mouseOverControl)
                fireEvent(TGEvent::MouseClicked,TGEventArgs(this));
        }
        m_pushed = false;
    }
}