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
    //                          T G M e n u I t e m
    //-----------------------------------------------------------------------
    TGMenuItem::TGMenuItem(TGControl *owner, TGString caption) : TGControl(owner)
    {
        this->caption = caption;
        subMenu = NULL;
    }

    //-----------------------------------------------------------------------
    //                         ~ T G M e n u I t e m
    //-----------------------------------------------------------------------
    TGMenuItem::~TGMenuItem()
    {
        if (subMenu)
            delete subMenu;
    }

    //-----------------------------------------------------------------------
    //                             a d d I t e m
    //-----------------------------------------------------------------------
    TGMenuItem *TGMenuItem::addItem(TGString caption)
    {
        if (!subMenu)
        {
            subMenu = new TGPopupMenu();
            subMenu->rootMenuControl = menuControl;
        }
        return subMenu->addItem(caption);
    }

    //-----------------------------------------------------------------------
    //                             c l e a r
    //-----------------------------------------------------------------------
    void TGMenuItem::clear()
    {
        if (subMenu)
            subMenu->clear();
    }

    //-----------------------------------------------------------------------
    //                          s e t T h e m e
    //-----------------------------------------------------------------------
    void TGMenuItem::setTheme(TGTheme theme,bool updateChildren)
    {
        TGControl::setTheme(theme,updateChildren);
        if(subMenu)
            subMenu->setTheme(theme,true);
    }
    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGMenuItem::render()
    {
        if(isRenderCached())
            return;

        int     x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);

        TGSBrush brush;

        if (caption[0] == '-' && !caption[1])
        {
            brush = m_theme.getFrameFocusedBrush();
            drawLine(x1, y1 + (y2 - y1 + 1)/2, x2 + 1,
                y1 + (y2 - y1 + 1)/2, brush);
            return;
        }

        if (m_mouseOverControl) // || (subMenu && subMenu->m_menuControl->m_parent))
        {
            brush = m_theme.getCaptionBrush();
            fillRect(x1, y1, x2, y2, brush);
            brush = m_theme.getTextInvertedBrush();
        }
        else
            brush = m_theme.getTextFocusedBrush();

        drawString(x1 + ((TGMenuControl*)m_parent)->iconPad + 5, y1 + 1,
            caption, brush);
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E n t e r
    //-----------------------------------------------------------------------
    void TGMenuItem::onMouseEnter()
    {
        TGControl::onMouseEnter();

        TGControl* child;

        for (TGControlListItr itr = m_parent->getChildren().begin();itr != m_parent->getChildren().end(); ++itr)
        {
            child = *itr;

            if (((TGMenuItem*)child)->subMenu &&
                ((TGMenuItem*)child)->subMenu->m_menuControl->m_parent)
            {
                ((TGMenuItem*)child)->subMenu->cancel();
                break;
            }
        }

        if (subMenu)
        {
            fireEvent(TGEvent::MenuPopup,TGEventArgs(this));

            int     x1, y1, x2, y2;
            getBounds(x1, y1, x2, y2);

            int dx=0,dy=0;
            subMenu->rootMenuControl->getSubOffsets(this,dx,dy);
            subMenu->run(x2+dx, y1+dy);
        }
        redraw();
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E x i t
    //-----------------------------------------------------------------------
    void TGMenuItem::onMouseExit(int x, int y)
    {
        TGControl::onMouseExit(x, y);
        redraw();
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGMenuItem::onMouseUp(int x, int y, int b)
    {
        if (b == LeftButton)
            fireEvent(TGEvent::MouseClicked,TGEventArgs(this));
        if (b < 4)
            if(menuControl && menuControl->m_menu)
                menuControl->m_menu->cancel();
    }

    //-----------------------------------------------------------------------
    //                      T G M e n u C o n t r o l
    //-----------------------------------------------------------------------
    TGMenuControl::TGMenuControl(TGControl *owner, TGString name)
        : TGControl(owner, name)
    {
        TGControl::setPadding(2, 2, 2, 2);
        iconPad = 0;
    }

    //-----------------------------------------------------------------------
    //                     ~ T G M e n u C o n t r o l
    //-----------------------------------------------------------------------
    TGMenuControl::~TGMenuControl()
    {
    }

    //-----------------------------------------------------------------------
    //                           c a l c S i z e
    //-----------------------------------------------------------------------
    void TGMenuControl::calcSize()
    {
        int     	w = 10, h = 3;

        TGControl* child;
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            child = *itr;

            int sw = stringWidth(((TGMenuItem*)child)->caption);
            if (w < sw+10)
                w = sw + 10;
            if (((TGMenuItem*)child)->caption[0] == '-' &&
                !((TGMenuItem*)child)->caption[1])
                h += 4;
            else
                h += stringHeight() + 3;
        }

        resize(w + (iconPad?(iconPad+5):0), h);
    }

    //-----------------------------------------------------------------------
    //                             l a y o u t
    //-----------------------------------------------------------------------
    void TGMenuControl::layout()
    {
        int     	w, h, y = 0;

        iconPad = 0;
        getClientSize(w, h);
        w--;

        TGControl* child;
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            child = *itr;
            int     height;
            if (((TGMenuItem*)child)->caption[0] == '-' &&
                !((TGMenuItem*)child)->caption[1])
                height = 4;
            else
                height = stringHeight() + 3;
            child->setBounds(0, y, w, y + height - 1);
            y += height;
        }

        TGControl::layout();
    }

    //-----------------------------------------------------------------------
    //                        g e t S u b O f f s e t s
    //-----------------------------------------------------------------------
    void TGMenuControl::getSubOffsets(TGMenuItem* item, int& dx, int& dy)
    {
        dx = -10;
        dy = 5;
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGMenuControl::render()
    {
        if(isRenderCached())
            return;

        TGSBrush  brush;
        brush = m_theme.getBase();
        fillRect(x1, y1, x2, y2, brush);
        brush = m_theme.getFrameFocusedBrush();
        drawRect(x1, y1, x2, y2, brush);

        TGControl::render();
    }

    //-----------------------------------------------------------------------
    //                        o n F o c u s E x i t
    //-----------------------------------------------------------------------
    void TGMenuControl::onFocusExit()
    {
        TGControl::onFocusExit();
        if (m_menu->rootMenuControl)
            m_menu->rootMenuControl->m_menu->cancel();
        else
            m_menu->cancel();
    }

    //-----------------------------------------------------------------------
    //                      T G M e n u b a r C o n t r o l
    //-----------------------------------------------------------------------
    TGMenubarControl::TGMenubarControl(TGControl *owner, TGString name)
        : TGMenuControl(owner, name)
    {
        setBounds(1,1,5,5);
        TGControl::setPadding(2, 2, 2, 2);
        iconPad = 0;
    }

    //-----------------------------------------------------------------------
    //                     ~ T G M e n u b a r C o n t r o l
    //-----------------------------------------------------------------------
    TGMenubarControl::~TGMenubarControl()
    {
    }

    //-----------------------------------------------------------------------
    //                           c a l c S i z e
    //-----------------------------------------------------------------------
    void TGMenubarControl::calcSize()
    {
        int     	w = 10, h = 3;

        m_parent->getWidth(w);
        h = stringHeight()+10;

        resize(w,h);
    }

    //-----------------------------------------------------------------------
    //                             l a y o u t
    //-----------------------------------------------------------------------
    void TGMenubarControl::layout()
    {
        int     	w, h, x = 0;

        iconPad = 0;
        getClientSize(w, h);
        h--;

        TGControl* child;
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            child = *itr;
            int     width;
            width = stringWidth(((TGMenuItem*)child)->caption) + 10;

            child->setBounds(x, 1, x+ width, h);
            x += (width + 5);
        }

        TGControl::layout();
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGMenubarControl::render()
    {
        if(isRenderCached())
            return;

        TGSBrush  brush;
        brush = m_theme.getBase();
        fillRect(x1, y1, x2, y2, brush);
        brush = m_theme.getFrameBrush();
        drawLine(x1,y2,x2,y2, brush);

        TGControl::render();
    }

    //-----------------------------------------------------------------------
    //                        o n F o c u s E x i t
    //-----------------------------------------------------------------------
    void TGMenubarControl::onFocusExit()
    {
        TGControl::onFocusExit();
        return;

        if (m_menu->rootMenuControl)
            m_menu->rootMenuControl->m_menu->cancel();
        else
            m_menu->cancel();
    }

    //-----------------------------------------------------------------------
    //                       g e t S u b O f f s e t s
    //-----------------------------------------------------------------------
    void TGMenubarControl::getSubOffsets(TGMenuItem* item, int& dx, int& dy)
    {
        
        dx = item->x1 - item->x2;
        dy = 25;
    }

    //-----------------------------------------------------------------------
    //                             T G M e n u
    //-----------------------------------------------------------------------
    TGMenu::TGMenu(TGControl* parent, TGString name) : TGControl(parent, name)
    {
        rootMenuControl = NULL;
    }

    //-----------------------------------------------------------------------
    //                           ~ T G M e n u
    //-----------------------------------------------------------------------
    TGMenu::~TGMenu()
    {
        if (m_menuControl)
            delete m_menuControl;
    }

    //-----------------------------------------------------------------------
    //                           a d d I t e m
    //-----------------------------------------------------------------------
    TGMenuItem *TGMenu::addItem(TGString caption)
    {
        TGMenuItem        *item = new TGMenuItem(m_menuControl, caption);
        item->menuControl = rootMenuControl?rootMenuControl:m_menuControl;
        m_menuControl->calcSize();
        m_menuControl->layout();
        return item;
    }

    //-----------------------------------------------------------------------
    //                               c l e a r
    //-----------------------------------------------------------------------
    void TGMenu::clear()
    {
        m_menuControl->removeAllChildren();
    }

    //-----------------------------------------------------------------------
    //                              c a n c e l
    //-----------------------------------------------------------------------
    void TGMenu::cancel()
    {

        TGControl* child;

        for (TGControlListItr itr = m_menuControl->getChildren().begin();itr != m_menuControl->getChildren().end(); ++itr)
        {
            child = *itr;
            if (((TGMenuItem*)child)->subMenu &&
                ((TGMenuItem*)child)->subMenu->m_menuControl->m_parent)
            {
                ((TGMenuItem*)child)->subMenu->cancel();
                break;
            }
        }

        if (m_menuControl->m_parent)
            m_menuControl->m_parent->removeChild(m_menuControl);
    }

    //-----------------------------------------------------------------------
    //                          s e t T h e m e
    //-----------------------------------------------------------------------
    void TGMenu::setTheme(TGTheme theme,bool updateChildren)
    {
        TGControl::setTheme(theme,updateChildren);
        m_menuControl->setTheme(theme,updateChildren);
    }
}