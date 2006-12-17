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
    //                       T G L i s t b o x I t e m
    //-----------------------------------------------------------------------
    TGListboxItem::TGListboxItem(TGControl *parent)
        : TGControl(parent)
    {
        box = (TGListbox*)parent;
        text = "";
        minimumWidth = 16;
        itemHeight = stringHeight() + 5;
        data = NULL;
    }

    //-----------------------------------------------------------------------
    //                      ~ T G L i s t b o x I t e m
    //-----------------------------------------------------------------------
    TGListboxItem::~TGListboxItem()
    {
    }

    //-----------------------------------------------------------------------
    //                            s e t T e x t
    //-----------------------------------------------------------------------
    void TGListboxItem::setText(TGString newText)
    {
        text = newText;
        minimumWidth = stringWidth(newText) + 16;
    }

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TGListboxItem::render()
    {
        if(isRenderCached())
            return;

        int			x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);

        TGSBrush brush;

        if (box->m_selectedItem == this)
        {
            brush = m_theme.getCaptionBrush();
            fillRect(x1, y1, x2, y2, brush);
            brush = m_theme.getTextFocusedBrush();
        }
        else
        {
            if (mouseOverControl)
                brush = m_theme.getTextFocusedBrush();
            else
                brush = m_theme.getTextBrush();
        }
        drawString(x1 + 8,
            (y2-y1 + 1)/2 + y1 - stringHeight()/2,
            text, brush);
    }

    //-----------------------------------------------------------------------
    //                               f o c u s 
    //-----------------------------------------------------------------------
    void TGListboxItem::focus()
    {
        if (box->m_selectedItem != this)
        {
            box->m_selectedItem = this;
            fireEvent(TGEvent::Selected,TGEventArgs(this));
            box->fireEvent(TGEvent::Modified,TGEventArgs(box));
        }
        box->focus();
    }


    //-----------------------------------------------------------------------
    //                          T G L i s t b o x 
    //-----------------------------------------------------------------------
    TGListbox::TGListbox(TGControl *parent, int x1, int y1, int x2, int y2)
        : TGScrollbox(parent, x1, y1, x2, y2)
    {
        m_selectedItem = NULL;
    }

    //-----------------------------------------------------------------------
    //                         ~ T G L i s t b o x 
    //-----------------------------------------------------------------------
    TGListbox::~TGListbox()
    {
    }

    //-----------------------------------------------------------------------
    //                             a d d I t e m
    //-----------------------------------------------------------------------
    void TGListbox::addItem(TGString text)
    {
        (new TGListboxItem(this))->setText(text);
        layout();
    }

    //-----------------------------------------------------------------------
    //                             a d d I t e m
    //-----------------------------------------------------------------------
    void TGListbox::addItem(TGListboxItem *item)
    {
        addChild(item);
    }

    //-----------------------------------------------------------------------
    //                             f i n d I t e m
    //-----------------------------------------------------------------------
    TGListboxItem *TGListbox::findItem(TGString text)
    {

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            if(!((TGListboxItem*)(*itr))->getText().compare(text))
                return (TGListboxItem*)*itr;
        }

        return NULL;
    }

    //-----------------------------------------------------------------------
    //                             g e t I t e m
    //-----------------------------------------------------------------------
    TGListboxItem *TGListbox::getItem(unsigned int index)
    {
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            if (index == ((TGListboxItem*)(*itr))->getIndex())
                return (TGListboxItem*)*itr;
        }

        return NULL;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e I t e m
    //-----------------------------------------------------------------------
    void TGListbox::removeItem(TGListboxItem *item)
    {
        if (!item)
            return;
        
        if(item == m_selectedItem)
            m_selectedItem = 0;
        removeChild(item);
        delete item;
    }

    //-----------------------------------------------------------------------
    //                            s e l e c t I t e m
    //-----------------------------------------------------------------------
    void TGListbox::selectItem(unsigned int index)
    {
        selectItem(getItem(index));
    }

    //-----------------------------------------------------------------------
    //                            s e l e c t I t e m
    //-----------------------------------------------------------------------
    void TGListbox::selectItem(TGListboxItem *item)
    {
        if (!item || item == m_selectedItem)
            return;
        m_selectedItem = item;
        m_selectedItem->fireEvent(TGEvent::Selected,TGEventArgs(m_selectedItem));
        fireEvent(TGEvent::Modified,TGEventArgs(this));
    }

    //-----------------------------------------------------------------------
    //                              l a y o u t
    //-----------------------------------------------------------------------
    void TGListbox::layout()
    {
        int     	w, h, y = 0, i = 0;

        getClientSize(w, h);
        w--;

        
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            TGListboxItem* lbi = (TGListboxItem*)(*itr);
            if( lbi->minimumWidth > (unsigned int)w)
                w = lbi->minimumWidth;
        }
        

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            TGListboxItem* lbi = (TGListboxItem*)(*itr);
            lbi->index = i++;
            lbi->setBounds(0, y, w, y + lbi->itemHeight - 1);
            y += lbi->itemHeight;
        }

        if (!m_selectedItem)
            m_selectedItem = (TGListboxItem*)getFirstChild();

        TGScrollbox::layout();
    }
}