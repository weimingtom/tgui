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
    //                          T G M e n u I t e m
    //-----------------------------------------------------------------------
    TGMenuItem::TGMenuItem(TGControl *owner, string caption, TGImage *image) : TGControl(owner)
    {
        this->caption = caption;
        this->image = image;
        subMenu = NULL;
    }

    //-----------------------------------------------------------------------
    //                         ~ T G M e n u I t e m
    //-----------------------------------------------------------------------
    TGMenuItem::~TGMenuItem()
    {
        if (subMenu)
            delete subMenu;
        if (image)
            delete image;
    }

    //-----------------------------------------------------------------------
    //                             a d d I t e m
    //-----------------------------------------------------------------------
    TGMenuItem *TGMenuItem::addItem(string caption, TGImage *image)
    {
        if (!subMenu)
        {
            subMenu = new TGPopupMenu();
            subMenu->rootMenuControl = menuControl;
        }
        return subMenu->addItem(caption, image);
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
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGMenuItem::render()
    {
        int     x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);

        if (caption[0] == '-' && !caption[1])
        {
            color(220, 234, 235);
            drawLine(x1, y1 + (y2 - y1 + 1)/2, x2 + 1,
                y1 + (y2 - y1 + 1)/2);
            return;
        }

        if (mouseOverControl || (subMenu && subMenu->menu->m_parent))
        {
            color(220, 234, 235);
            fillRect(x1, y1, x2, y2);
            color(20, 34, 35);
        }
        else
            color(220, 234, 235);

        drawString(x1 + ((TGMenuControl*)m_parent)->iconPad + 5, y1 + 1,
            caption);
        if (image)
            image->draw(x1 + 5, (y2 - y1 + 1)/2 - image->getHeight()/2 + y1);
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
                ((TGMenuItem*)child)->subMenu->menu->m_parent)
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
            subMenu->run(x2 - 10, y1 + 5);
        }
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGMenuItem::onMouseUp(int x, int y, int b)
    {
        if (b == LeftButton)
            fireEvent(TGEvent::MouseClicked,TGEventArgs(this));
        if (b < 4)
            menuControl->popupMenu->cancel();
    }


    //-----------------------------------------------------------------------
    //                      T G M e n u C o n t r o l
    //-----------------------------------------------------------------------
    TGMenuControl::TGMenuControl(TGControl *owner)
        : TGControl(owner)
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

            if (w < stringWidth(((TGMenuItem*)child)->caption)+10)
                w = stringWidth(((TGMenuItem*)child)->caption)
                + 10;
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
            if (((TGMenuItem*)child)->image &&
                iconPad < (int)((TGMenuItem*)child)->image->getWidth())
                iconPad = ((TGMenuItem*)child)->image->getWidth() + 5;
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
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGMenuControl::render()
    {

        color(120, 134, 135, 192);
        fillRect(x1, y1, x2, y2);
        color(220, 234, 235);
        drawRect(x1, y1, x2, y2);

        TGControl::render();
    }

    //-----------------------------------------------------------------------
    //                        o n F o c u s E x i t
    //-----------------------------------------------------------------------
    void TGMenuControl::onFocusExit()
    {
        TGControl::onFocusExit();
        if (popupMenu->rootMenuControl)
            popupMenu->rootMenuControl->popupMenu->cancel();
        else
            popupMenu->cancel();
    }


    //-----------------------------------------------------------------------
    //                         T G P o p u p M e n u
    //-----------------------------------------------------------------------
    TGPopupMenu::TGPopupMenu() : TGControl(NULL)
    {
        rootMenuControl = NULL;
        menu = new TGMenuControl(NULL);
        menu->popupMenu = this;
    }

    //-----------------------------------------------------------------------
    //                        ~ T G P o p u p M e n u
    //-----------------------------------------------------------------------
    TGPopupMenu::~TGPopupMenu()
    {
        if (!menu->m_parent)
            delete menu;
    }

    //-----------------------------------------------------------------------
    //                           a d d I t e m
    //-----------------------------------------------------------------------
    TGMenuItem *TGPopupMenu::addItem(string caption,TGImage *image)
    {
        TGMenuItem        *item = new TGMenuItem(menu, caption, image);
        item->menuControl = rootMenuControl?rootMenuControl:menu;
        menu->calcSize();
        menu->layout();
        return item;
    }

    //-----------------------------------------------------------------------
    //                               c l e a r
    //-----------------------------------------------------------------------
    void TGPopupMenu::clear()
    {
        menu->removeAllChildren();
    }

    //-----------------------------------------------------------------------
    //                                 r u n
    //-----------------------------------------------------------------------
    void TGPopupMenu::run(int x, int y)
    {
        if (menu->m_parent)
            cancel();
        if (x == -10000)
            x = TGSystem::getSingleton().getActiveScreen()->getMouseX();
        if (y == -10000)
            y = TGSystem::getSingleton().getActiveScreen()->getMouseY();
        menu->calcSize();
        menu->layout();
        TGSystem::getSingleton().getActiveScreen()->addChild(menu);
        menu->move(x, y);
        menu->focus();
    }

    //-----------------------------------------------------------------------
    //                              c a n c e l
    //-----------------------------------------------------------------------
    void TGPopupMenu::cancel()
    {

        TGControl* child;

        for (TGControlListItr itr = menu->getChildren().begin();itr != menu->getChildren().end(); ++itr)
        {
            child = *itr;
            if (((TGMenuItem*)child)->subMenu &&
                ((TGMenuItem*)child)->subMenu->menu->m_parent)
            {
                ((TGMenuItem*)child)->subMenu->cancel();
                break;
            }
        }

        if (menu->m_parent)
            menu->m_parent->removeChild(menu);
    }
}