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
    //                           T G M e n u B a r
    //-----------------------------------------------------------------------
    TGMenuBar::TGMenuBar(TGControl* parent, TGString name) : TGMenu(parent, name)
    {
        rootMenuControl = NULL;
        m_menuControl = new TGMenubarControl(m_parent);
        m_menuControl->m_menu = this;
        m_menuControl->calcSize();
        m_menuControl->layout();
    }

    //-----------------------------------------------------------------------
    //                          ~ T G M e n u B a r
    //-----------------------------------------------------------------------
    TGMenuBar::~TGMenuBar()
    {
    }

    //-----------------------------------------------------------------------
    //                           a d d I t e m
    //-----------------------------------------------------------------------
    TGMenuItem *TGMenuBar::addItem(TGString caption)
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
    void TGMenuBar::clear()
    {
        m_menuControl->removeAllChildren();
    }

    //-----------------------------------------------------------------------
    //                                 r u n
    //-----------------------------------------------------------------------
    void TGMenuBar::run(int x, int y)
    {
        if (m_menuControl->m_parent)
            cancel();
        if (x == -10000)
            x = TGSystem::getSingleton().getActiveScreen()->getMouseX();
        if (y == -10000)
            y = TGSystem::getSingleton().getActiveScreen()->getMouseY();
        m_menuControl->calcSize();
        m_menuControl->layout();
        TGSystem::getSingleton().getActiveScreen()->addChild(m_menuControl);
        m_menuControl->moveRel(x, y);
        m_menuControl->focus();
    }

    //-----------------------------------------------------------------------
    //                              c a n c e l
    //-----------------------------------------------------------------------
    void TGMenuBar::cancel()
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

        //if (m_menuControl->m_parent)
        //    m_menuControl->m_parent->removeChild(m_menuControl);
    }

    //-----------------------------------------------------------------------
    //                          s e t T h e m e
    //-----------------------------------------------------------------------
    void TGMenuBar::setTheme(TGTheme theme,bool updateChildren)
    {
        TGControl::setTheme(theme,updateChildren);
        m_menuControl->setTheme(theme,updateChildren);
    }

}