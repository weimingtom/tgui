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
        m_listbox = new TGListbox(parent,0,0,5,5);

        TGColourTheme ct = m_listbox->getColourTheme();
        TGColour c = ct.getBase();
        c.a = 1.f;
     
        m_listbox->setColourTheme(TGColourTheme(c),true);
        m_listbox->hide();
        m_listbox->redraw();

        m_listbox->addEventHandler(TGEvent::Modified,TGEVENT_HANDLER(TGCombobox::itemSelected));
    }

    //-----------------------------------------------------------------------
    //                          T G C o m b o b o x
    //-----------------------------------------------------------------------
    TGCombobox::~TGCombobox()
    {
    }

    //-----------------------------------------------------------------------
    //                          i t e m S e l e c t e d
    //-----------------------------------------------------------------------
    bool TGCombobox::itemSelected(const TGEventArgs& args)
    {
        TGListboxItem* lbi = m_listbox->getSelectedItem();
        if(!lbi)
            return true;
        setText(lbi->getText());
        m_listbox->hide();
        return true;
    }

    //-----------------------------------------------------------------------
    //                           s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGCombobox::setBounds(int x1, int y1, int x2, int y2)
    {
        m_height = y2-y1;
        
        TGInputbox::setBounds(x1, y1, x2-m_height, y2);
        m_listbox->setBounds(x1, y2, x2, y2 + m_height*5);
    }

    //-----------------------------------------------------------------------
    //                       p o i n t I n C o n t r o l
    //-----------------------------------------------------------------------
    bool TGCombobox::pointInControl(float x, float y)
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
    TGControl* TGCombobox::childAt(float x, float y)
    {
        return this;
    }

    //-----------------------------------------------------------------------
    //                            a d d I t e m
    //-----------------------------------------------------------------------
    void TGCombobox::addItem(string text)
    {
        m_listbox->addItem(text);
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGCombobox::onMouseDown(int x, int y, int b)
    {
        int x1,y1,x2,y2;
        getBounds(x1, y1, x2, y2);

        if ((x >= x1 && y >= y1 && x <= (x2-m_height) && y <= y2))
        {
            if(m_listbox->isVisible())
                m_listbox->hide();
            TGInputbox::onMouseDown(x, y, b);
            return;
        }

        x1 = x2;
        x2 += m_height;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
        {
            if(m_listbox->isVisible())
                m_listbox->hide();
            else 
            {
                m_listbox->show();
                m_listbox->focus();
                m_listbox->mouseOverControl = true;
                mouseOverControl = true;
            }
            return;
        }

    TGInputbox::onMouseDown(x, y, b);
    }

    //-----------------------------------------------------------------------
    //                            o n F o c u s E x i t
    //-----------------------------------------------------------------------
    void TGCombobox::onFocusExit()
    {

        TGInputbox::onFocusExit();
        if(m_listbox->isVisible())
            m_listbox->hide();

    }

    //-----------------------------------------------------------------------
    //                               f o c u s
    //-----------------------------------------------------------------------
    void TGCombobox::focus()
    {
        if (!m_parent)
            return;

        TGInputbox::focus();

        m_parent->focus();

        if (m_parent->getLastChild() == this)
            return;

        TGControl *oldFocus = m_parent->getLastChild()->getFocusedChild();

        m_parent->setFocusedChild(this);

        if(oldFocus)
        {
            if(oldFocus->m_parent)
                oldFocus->m_parent->redraw();
            oldFocus->onFocusExit();
        }
        onFocusEnter(oldFocus);
    }

    //-----------------------------------------------------------------------
    //                              f o c u s e d
    //-----------------------------------------------------------------------
    bool TGCombobox::focused()
    {
        if (!m_parent)
            return true;
        TGControl* c = m_parent->getFocusedChild();
        if(c == this || c == m_listbox)
            return true;
        else return false;
    }



    //-----------------------------------------------------------------------
    //                      s e t C o l o u r T h e m e
    //-----------------------------------------------------------------------
    void TGCombobox::setColourTheme(TGColourTheme theme,bool updateChildren)
    {
        TGControl::setColourTheme(theme,updateChildren);

        TGColour c = theme.getBase();
        c.a = 1.f;
        m_listbox->setColourTheme(TGColourTheme(c),true);
        m_listbox->redraw();
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
        if (mouseOverControl  || hasKeyboardFocus(this) || m_listbox->isVisible())
            color(m_theme.getFrameFocusedColour());
        else
            color(m_theme.getFrameColour());

        drawRect(x2, y1, x2 + m_height, y2);

        drawTri(x2+2,y1+7, x2+m_height-3, y2-7,0);

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