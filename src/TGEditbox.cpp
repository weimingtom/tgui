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
    //                          T G E d i t b o x
    //-----------------------------------------------------------------------
    TGEditbox::TGEditbox(TGControl *parent, int x1, int y1, int x2, int y2)
        : TGControl(parent)
        , m_readOnly(false)
        , m_cursorVisible(false)
        , m_pulseTime(0.f)
        , m_lastKey(-1)
        , m_repeatDelay(0.25)
        , m_repeatRate(0.1f)
        , m_repeatElapsed(0.f)
        , m_cursor(0)
        , m_cursorX(0)
    {
        m_text.setControl(this);
        m_text.set("");
        setBounds(x1, y1, x2, y2);
        tScroll = 0;
    }

    //-----------------------------------------------------------------------
    //                        ~ T G E d i t b o x
    //-----------------------------------------------------------------------
    TGEditbox::~TGEditbox()
    {
    }

    //-----------------------------------------------------------------------
    //                            s e t T e x t
    //-----------------------------------------------------------------------
    void TGEditbox::setText(TGString newText)
    {
        int     w, h;
        getClientSize(w, h);
        m_text.set(newText);
        m_cursor = newText.length();
        m_cursorX = stringWidth(newText);
        tScroll = 0;
        if (m_cursorX - tScroll > w - 10)
            tScroll = m_cursorX - w + (w/2);
        redraw();
    }

    //-----------------------------------------------------------------------
    //                           g e t T e x t
    //-----------------------------------------------------------------------
    TGString TGEditbox::getText()
    {
        return m_text.get();
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGEditbox::render()
    {
        if(isRenderCached())
            return;

        int			x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);

        TGSBrush brush;
        brush = m_theme.getBase();
        fillRect(x1, y1 + 1, x2 - 1, y2, brush);

        openClip();

        if(hasKeyboardFocus(this) || m_mouseOverControl  ||
            (isComposite && m_parent->getMouseOverControl()))
            brush = m_theme.getTextFocusedBrush();
        else brush = m_theme.getTextBrush();

        drawString(x1 + 5 - tScroll, y1 + (y2 - y1)/2 -
            stringHeight()/2, m_text.get(), brush);

        closeClip();

        
        if (m_cursorVisible && !m_readOnly)
        {
            TGSBrush brush;
            brush.bind(new TGBrush(TGColour(1,1,1)));
            drawLine(x1 + 5 + m_cursorX - tScroll, y1 + 4,
                x1 + 5 + m_cursorX - tScroll, y2 - 4, brush);
        }
        

        if (m_mouseOverControl  || hasKeyboardFocus(this))
            brush = m_theme.getFrameFocusedBrush();
        else
            brush = m_theme.getFrameBrush();

        drawRect(x1, y1, x2, y2, brush);
    }

    //-----------------------------------------------------------------------
    //                         o n K e y D o w n
    //-----------------------------------------------------------------------
    void TGEditbox::onKeyDown(int key, unsigned char ascii)
    {
        int     w, h;

        if(m_readOnly)
            return;

        if(m_lastKey < 0)
            m_repeatElapsed = -m_repeatDelay;
        else m_repeatElapsed = 0.f;
        m_lastKey = key;
        m_lastChar = ascii;
        TGString text = m_text.get();
        getClientSize(w, h);
        switch (ascii)
        {
        case 8:
            if (!text.empty())
            {
                text = text.substr(0,text.length()-1);
                m_cursorX = stringWidth(text,--m_cursor);
                if (m_cursorX - tScroll < 0)
                {
                    tScroll = m_cursorX - (w/2);
                    if (tScroll < 0)
                        tScroll = 0;
                }
            }
            break;

        case 13:    // Enter/Return
            fireEvent(TGEvent::AcceptText,TGEventArgs(this));
            return;
            break;

        default:
            if (ascii < 32 || ascii > 127)
            { 
                m_lastKey = -1;
                break;
            }

            text += ascii;
            m_cursorX = stringWidth(text, ++m_cursor);
            if (m_cursorX - tScroll > w - 10)
                tScroll = m_cursorX - w + (w/2);
            break;
        }
        m_text.set(text);
        redraw();
    }

    //-----------------------------------------------------------------------
    //                           o n K e y U p
    //-----------------------------------------------------------------------
    void TGEditbox::onKeyUp(int key, unsigned char ascii)
    {
        m_lastKey = -1;
    }

    //-----------------------------------------------------------------------
    //                            p u l s e
    //-----------------------------------------------------------------------
    void TGEditbox::pulse(TGReal timeElapsed)
    {
        if(!focused() || m_readOnly)
            return;

        m_pulseTime += timeElapsed;

        if(m_pulseTime >= 0.25f)
        {
            m_cursorVisible = m_cursorVisible ? false : true;
            m_pulseTime = 0.f;
            redraw();
        }

        if(m_lastKey > 0)
        {
            m_repeatElapsed += timeElapsed;
            if(m_repeatElapsed >= m_repeatRate)
            {
                onKeyDown(m_lastKey,m_lastChar);
            }
        }

    }

    //-----------------------------------------------------------------------
    //                       o n F o c u s E n t e r
    //-----------------------------------------------------------------------
    void TGEditbox::onFocusEnter(TGControl* oldFocus)
    {
        TGControl::onFocusEnter(oldFocus);
        m_cursorVisible = true;
        m_pulseTime = 0.f;
        redraw();
    }

    //-----------------------------------------------------------------------
    //                        o n F o c u s E x i t
    //-----------------------------------------------------------------------
    void TGEditbox::onFocusExit()
    {
        m_cursorVisible = false;
        redraw();
    }


}