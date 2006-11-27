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
    void TGListboxItem::setText(string newText)
    {
        text = newText;
        minimumWidth = stringWidth(newText) + 16;
    }

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TGListboxItem::render()
    {
        int			x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);

        if (box->active == this)
        {
            color(190, 204, 205);
            fillRect(x1, y1, x2, y2);
            color(80, 94, 95);
            if (box->focused())
                drawRect(x1 + 2, y1 + 2, x2 - 1, y2 - 2);
        }
        else
        {
            if (mouseOverControl)
                color(210, 224, 225);
            else
                color(190, 204, 205);
        }
        drawString(x1 + 8,
            (y2-y1 + 1)/2 + y1 - stringHeight()/2,
            text);
    }

    //-----------------------------------------------------------------------
    //                               f o c u s 
    //-----------------------------------------------------------------------
    void TGListboxItem::focus()
    {
        if (box->active != this)
        {
            box->active = this;
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
        active = NULL;
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
    void TGListbox::addItem(string text)
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
    TGListboxItem *TGListbox::findItem(string text)
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
        
        if(item == active)
            active = 0;
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
        if (!item || item == active)
            return;
        active = item;
        active->fireEvent(TGEvent::Selected,TGEventArgs(active));
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
            if( lbi->minimumWidth > 2)
                w = lbi->minimumWidth;
        }

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            TGListboxItem* lbi = (TGListboxItem*)(*itr);
            lbi->index = i++;
            lbi->place(0, y, w, y + lbi->itemHeight - 1);
            y += lbi->itemHeight;
        }

        if (!active)
            active = (TGListboxItem*)getFirstChild();

        TGScrollbox::layout();
    }
}