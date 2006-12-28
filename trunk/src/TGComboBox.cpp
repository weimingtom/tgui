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
    //                          T G C o m b o B o x
    //-----------------------------------------------------------------------
    TGComboBox::TGComboBox(TGControl *parent, TGString name)
        : TGControl(parent, name)
    {
        m_height=0;
        m_listbox = new TGListBox(this);
        m_inputbox = new TGEditBox(this);
        m_listbox->m_isComposite = true;
        m_inputbox->m_isComposite = true;
        m_style = CBS_NORMAL;

        m_listbox->hide();
        m_listbox->redraw();

        m_listbox->addEventHandler(TGEvent::Modified,TGEVENT_HANDLER(TGComboBox::itemSelected));
    }

    //-----------------------------------------------------------------------
    //                          T G C o m b o B o x
    //-----------------------------------------------------------------------
    TGComboBox::~TGComboBox()
    {
    }

    //-----------------------------------------------------------------------
    //                            s e t S t y l e
    //-----------------------------------------------------------------------
    void TGComboBox::setStyle(TGComboBoxStyle value)
    {
        m_style = value;
        if(m_style == CBS_NORMAL)
            m_inputbox->setReadOnly(false);
        else m_inputbox->setReadOnly(true);
    }

    //-----------------------------------------------------------------------
    //                          i t e m S e l e c t e d
    //-----------------------------------------------------------------------
    bool TGComboBox::itemSelected(const TGEventArgs& args)
    {
        TGListBoxItem* lbi = m_listbox->getSelectedItem();
        if(!lbi)
            return true;
        m_inputbox->setText(lbi->getText());
        m_listbox->hide();
        return true;
    }

    //-----------------------------------------------------------------------
    //                           s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGComboBox::setBounds(int x1, int y1, int x2, int y2)
    {
        m_height = y2-y1;

        TGControl::setBounds(x1,y1,x2,y2 + m_height*5);

        m_inputbox->setBounds(0,0,x2-x1-m_height,m_height);
        m_listbox->setBounds(0,m_height,x2-x1,m_height + m_height*5);
    }

    //-----------------------------------------------------------------------
    //                       p o i n t I n C o n t r o l
    //-----------------------------------------------------------------------
    bool TGComboBox::pointInControl(TGReal x, TGReal y)
    {
        int	x1, y1, x2, y2;
        if(m_listbox->isVisible())
            return TGControl::pointInControl(x,y);


        getBounds(x1, y1, x2, y2);
        y2 = y1 + m_height;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    //                            c h i l d A t
    //-----------------------------------------------------------------------
    TGControl* TGComboBox::childAt(TGReal x, TGReal y)
    {
        if(m_listbox->isVisible() && m_listbox->pointInControl(x,y))
            return m_listbox->childAt(x,y);
        return this;
    }

    //-----------------------------------------------------------------------
    //                            a d d I t e m
    //-----------------------------------------------------------------------
    void TGComboBox::addItem(TGString text)
    {
        m_listbox->addItem(text);
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGComboBox::onMouseDown(int x, int y, int b)
    {
        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);

        if (m_inputbox->pointInControl(x,y))
        {
            if(m_listbox->isVisible())
                m_listbox->hide();
            m_inputbox->onMouseDown(x, y, b);
            return;
        }

        x1 = x2-m_height;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y1+m_height))
        {
            if(m_listbox->isVisible())
            {
                m_listbox->hide();
            }
            else 
            {
                m_listbox->show();
                m_listbox->focus();
                setMouseOverControl(true);
            }
            return;
        }
        else m_listbox->onMouseDown(x,y,b);

    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e M o v e d
    //-----------------------------------------------------------------------
    void TGComboBox::onMouseMoved(int x, int y)
    {
        if(m_listbox->isVisible())
        {
            if(m_listbox->pointInControl(x,y))
            {
                m_listbox->setMouseOverControl(true);
                m_inputbox->setMouseOverControl(true);
                m_listbox->onMouseMoved(x,y);
                return;
            }
            if(m_inputbox->pointInControl(x,y))
            {
                m_listbox->setMouseOverControl(true);
                m_inputbox->setMouseOverControl(true);
                m_inputbox->onMouseMoved(x,y);
                return;
            }
        }
        if(m_inputbox->pointInControl(x,y))
        {
            m_listbox->setMouseOverControl(true);
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
    void TGComboBox::onMouseEnter()
    {
        TGControl::onMouseEnter();
        m_inputbox->onMouseEnter();
        m_listbox->onMouseEnter();
    }

    //-----------------------------------------------------------------------
    //                            o n M o u s e E x i t
    //-----------------------------------------------------------------------
    void TGComboBox::onMouseExit(int x, int y)
    {
        if(pointInControl(x,y))
            return;

        m_inputbox->setMouseOverControl(false);
        m_listbox->setMouseOverControl(false);
        m_mouseOverControl = false;
        m_inputbox->onMouseExit(x, y);
        TGControl::onMouseExit(x, y);

    }

    //-----------------------------------------------------------------------
    //                            o n F o c u s E x i t
    //-----------------------------------------------------------------------
    void TGComboBox::onFocusExit()
    {

        if(m_mouseOverControl || m_listbox->getMouseOverControl() )
            return;

        m_inputbox->onFocusExit();
        m_inputbox->setMouseOverControl(false);
        if(m_listbox->isVisible())
            m_listbox->hide();

        redraw(true);
    }

    //-----------------------------------------------------------------------
    //                              f o c u s e d
    //-----------------------------------------------------------------------
    bool TGComboBox::focused()
    {
        if (!m_parent)
            return true;
        TGControl* c = m_parent->getFocusedChild();
        if(c == this || c == m_listbox || c == m_inputbox)
            return true;
        else return false;
    }

    //-----------------------------------------------------------------------
    //                           s e t T h e m e
    //-----------------------------------------------------------------------
    void TGComboBox::setTheme(TGTheme theme,bool updateChildren)
    {
        TGControl::setTheme(theme,updateChildren);
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGComboBox::render()
    {
        if(TGControl::isRenderCached())
            return;

        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);
        TGSBrush brush;
        if (m_mouseOverControl  || hasKeyboardFocus(this) || 
            hasKeyboardFocus(m_inputbox) || m_listbox->isVisible())
            brush = m_theme.getFrameFocusedBrush();
        else
            brush = m_theme.getFrameBrush();

        drawRect(x2-m_height, y1, x2, y1+m_height,brush);
        drawTri(x2-m_height+2,y1+7, x2-3, y1+m_height-7,brush,0);

        TGControl::render();

    }

}