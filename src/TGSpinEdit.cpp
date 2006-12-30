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
    //                          T G C o m b o b o x
    //-----------------------------------------------------------------------
    TGSpinEdit::TGSpinEdit(TGControl *parent, TGString name)
        : TGControl(parent, name)
        , m_upPressed(false)
        , m_downPressed(false)
        , m_height(0)
        , m_pulseTime(0.f)
    {
        m_inputbox = new TGEditBox(this);
        m_inputbox->m_isComposite = true;     
        m_value = 0.f;
        m_minValue = 0.f;
        m_maxValue = 100.f;
        m_increment = 1.f;
    }

    //-----------------------------------------------------------------------
    //                          T G C o m b o b o x
    //-----------------------------------------------------------------------
    TGSpinEdit::~TGSpinEdit()
    {
    }

    //-----------------------------------------------------------------------
    //                           s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGSpinEdit::setBounds(int x1, int y1, int x2, int y2)
    {
        m_height = y2-y1;

        TGControl::setBounds(x1,y1,x2,y2 + m_height*5);

        m_inputbox->setBounds(0,0,x2-x1-m_height,m_height);
    }

    //-----------------------------------------------------------------------
    //                       p o i n t I n C o n t r o l
    //-----------------------------------------------------------------------
    bool TGSpinEdit::pointInControl(TGReal x, TGReal y)
    {
        int	x1, y1, x2, y2;

        getBounds(x1, y1, x2, y2);
        y2 = y1 + m_height;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    //                            c h i l d A t
    //-----------------------------------------------------------------------
    TGControl* TGSpinEdit::childAt(TGReal x, TGReal y)
    {
        return this;
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGSpinEdit::onMouseDown(int x, int y, int b)
    {
        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);

        if (m_inputbox->pointInControl(x,y))
        {
            m_inputbox->onMouseDown(x, y, b);
            return;
        }

        if (y < y1+(m_height / 2))
            m_upPressed = true;
        else m_downPressed = true;
        updateValue();
        m_pulseTime = 0.f;

        setMouseTrackingControl(this);
        redraw();
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e U p 
    //-----------------------------------------------------------------------
    void TGSpinEdit::onMouseUp(int x, int y, int b)
    {

        if(m_upPressed || m_downPressed)
        {
            setMouseTrackingControl(NULL);
            m_upPressed = false;
            m_downPressed = false;
            redraw();
            return;
        }

        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);

        if (m_inputbox->pointInControl(x,y))
        {
            m_inputbox->onMouseUp(x, y, b);
            return;
        }

        x1 = x2-m_height;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y1+m_height))
        {
        }
    }
    //-----------------------------------------------------------------------
    //                          o n M o u s e M o v e d
    //-----------------------------------------------------------------------
    void TGSpinEdit::onMouseMoved(int x, int y)
    {
        if(m_upPressed || m_downPressed)
        {
            return;
        }

        if(m_inputbox->pointInControl(x,y))
        {
            m_inputbox->setMouseOverControl(true);
            m_inputbox->onMouseMoved(x,y);
            return;
        }
        m_inputbox->setMouseOverControl(true);

        TGControl::onMouseMoved(x,y);
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E n t e r
    //-----------------------------------------------------------------------
    void TGSpinEdit::onMouseEnter()
    {
        if(m_upPressed || m_downPressed)
        {
            return;
        }
        TGControl::onMouseEnter();
        m_inputbox->onMouseEnter();
    }

    //-----------------------------------------------------------------------
    //                            o n M o u s e E x i t
    //-----------------------------------------------------------------------
    void TGSpinEdit::onMouseExit(int x, int y)
    {
        if(m_upPressed || m_downPressed)
        {
            return;
        }
        if(pointInControl(x,y))
            return;
        
        m_inputbox->setMouseOverControl(false);
        setMouseOverControl(false);
        m_inputbox->onMouseExit(x, y);
        TGControl::onMouseExit(x, y);

    }

    //-----------------------------------------------------------------------
    //                            o n F o c u s E x i t
    //-----------------------------------------------------------------------
    void TGSpinEdit::onFocusExit()
    {

        if(m_mouseOverControl)
            return;

        m_inputbox->onFocusExit();
        m_inputbox->setMouseOverControl(false);

        redraw(true);
    }

    //-----------------------------------------------------------------------
    //                              f o c u s e d
    //-----------------------------------------------------------------------
    bool TGSpinEdit::focused()
    {
        if (!m_parent)
            return true;
        TGControl* c = m_parent->getFocusedChild();
        if(c == this)
            return true;
        else return false;
    }

    //-----------------------------------------------------------------------
    //                           s e t T h e m e
    //-----------------------------------------------------------------------
    void TGSpinEdit::setTheme(TGTheme theme,bool updateChildren)
    {
        TGControl::setTheme(theme,updateChildren);
    }

    //-----------------------------------------------------------------------
    //                              p u l s e
    //-----------------------------------------------------------------------
    void TGSpinEdit::pulse(TGReal timeElapsed)
    {
        if((!m_upPressed) && (!m_downPressed))
            return;

        m_pulseTime += timeElapsed;

        if(m_pulseTime >= 0.25f)
        {
            updateValue();
            redraw();
            m_pulseTime = 0.f;
        }
    }

    //-----------------------------------------------------------------------
    //                         u p d a t e V a l u e
    //-----------------------------------------------------------------------
    void TGSpinEdit::updateValue()
    {
        if((!m_upPressed) && (!m_downPressed))
            return;

        if(m_upPressed)
        {
            m_value += m_increment;
            if(m_value > m_maxValue)
                m_value = m_maxValue;
        }

        if(m_downPressed)
        {
            m_value -= m_increment;
            if(m_value < m_minValue)
                m_value = m_minValue;
        }

        char buf[100];
        sprintf(buf,"%.2f",m_value);
        m_inputbox->setText(buf);
    }

    //-----------------------------------------------------------------------
    //                       s e t C u r r e n t V a l u e
    //-----------------------------------------------------------------------
    void TGSpinEdit::setCurrentValue(TGReal value)
    {
        if( (value < m_minValue) || (value > m_maxValue) )
            return;
        m_value = value;
        char buf[100];
        sprintf(buf,"%.2f",m_value);
        m_inputbox->setText(buf);
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGSpinEdit::render()
    {
        if(isRenderCached())
            return;

        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);
        TGSBrush brush;
        if (m_mouseOverControl  || hasKeyboardFocus(this) || 
            hasKeyboardFocus(m_inputbox))
            brush = m_theme.getFrameFocusedBrush();
        else
            brush = m_theme.getFrameBrush();

        drawRect(x2-m_height, y1, x2, y1+m_height,brush);

        if(!m_upPressed)
            drawTri(x2-m_height+2,y1+1, x2-3, y1+(m_height/2)-1,brush,1);
        else drawTri(x2-m_height+2,y1+1, x2-3, y1+(m_height/2)-1,m_theme.getFrameBrush(),1);

        if(!m_downPressed)
            drawTri(x2-m_height+2,y1+(m_height/2)+1, x2-3, y1+m_height-2,brush,0);
        else drawTri(x2-m_height+2,y1+(m_height/2)+1, x2-3, y1+m_height-2,m_theme.getFrameBrush(),0);

        TGControl::render();

    }

}