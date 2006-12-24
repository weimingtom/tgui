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
    //                         T G P o p u p M e n u
    //-----------------------------------------------------------------------
    TGPopupMenu::TGPopupMenu(TGControl* parent) : TGMenu(parent)
    {
        rootMenuControl = NULL;
        menu = new TGMenuControl(parent);
        menu->m_menu = this;
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
    TGMenuItem *TGPopupMenu::addItem(TGString caption)
    {
        TGMenuItem        *item = new TGMenuItem(menu, caption);
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
        menu->moveRel(x, y);
        menu->focus();
        TGSystem::getSingleton().setActivePopup(this);
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

    //-----------------------------------------------------------------------
    //                         c a n c e l R o o t
    //-----------------------------------------------------------------------
    void TGPopupMenu::cancelRoot()
    {

        if(rootMenuControl && rootMenuControl->m_menu)
            rootMenuControl->m_menu->cancel();
        else if(menu)
            menu->m_menu->cancel();

    }

    //-----------------------------------------------------------------------
    //                          s e t T h e m e
    //-----------------------------------------------------------------------
    void TGPopupMenu::setTheme(TGTheme theme,bool updateChildren)
    {
        TGControl::setTheme(theme,updateChildren);
        menu->setTheme(theme,updateChildren);
    }

}