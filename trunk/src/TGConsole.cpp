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
    //                          T G C o n s o l e
    //-----------------------------------------------------------------------
    TGConsole::TGConsole(TGString caption) : TGWindow(NULL,"",caption)
    {
        m_list = new TGListBox(this,"commandHistory");
        m_list->setPos(5,5);
        m_list->resize(485,205);

        m_input = new TGEditBox(this,"commandLine");
        m_input->setPos(5,220);
        m_input->resize(485,25);

        m_input->addEventHandler(TGEvent::AcceptText,new TGEventHandler(&TGConsole::acceptText,this));
        m_input->addEventHandler(TGEvent::EscapeText,new TGEventHandler(&TGConsole::escapeText,this));

        resize(500, 275);
        center();
        m_input->focus();
    }

    //-----------------------------------------------------------------------
    //                         ~ T G C o n s o l e
    //-----------------------------------------------------------------------
    TGConsole::~TGConsole()
    {
    }

    //-----------------------------------------------------------------------
    //                         e s c a p e T e x t
    //-----------------------------------------------------------------------
    bool TGConsole::escapeText(const TGEventArgs& args)
    {
        toggle();
        return true;
    }

    //-----------------------------------------------------------------------
    //                         a c c e p t T e x t
    //-----------------------------------------------------------------------
    bool TGConsole::acceptText(const TGEventArgs& args)
    {
        TGString command;
        command = m_input->getText();

        if(command.empty())
            return true;

        TGConsoleEventArgs ea(this);
        ea.m_command = command;
        
        addItem(m_input->getText());

        fireEvent(TGEvent::ConsoleCommand,ea);

        m_input->setText("");

        m_list->setVScrollPos(m_list->getVScrollMax());

        return true;
    }

    //-----------------------------------------------------------------------
    //                           s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGConsole::setBounds(int x1, int y1, int x2, int y2)
    {
        int ox1,oy1,ox2,oy2;
        getBounds(ox1,oy1,ox2,oy2);

        TGControl::setBounds(x1,y1,x2,y2);

        if( ((ox2-ox1) == (x2-x1)) &&
            ((oy2-oy1) == (y2-y1)) )
            return;      
    }

    //-----------------------------------------------------------------------
    //                            a d d I t e m
    //-----------------------------------------------------------------------
    void TGConsole::addItem(TGString item) 
    {
        m_list->addItem(item);
    }

    //-----------------------------------------------------------------------
    //                            t o g g l e
    //-----------------------------------------------------------------------
    void TGConsole::toggle()
    {
        if(isVisible())
        {
            makeExclusive(false);
            hide();
            setKeyboardFocusControl(NULL);
        }
        else
        {
            TGScreen* activeScreen = TGSystem::getSingleton().getActiveScreen();
            if(activeScreen)
            {
                if(activeScreen != m_parent)
                    reParent(activeScreen);
                activeScreen->setFocusedChild(this);
                makeExclusive();
                setKeyboardFocusControl(m_input);

                m_input->focus();
                show();
            }
        }
        fireEvent(TGEvent::ConsoleToggled,TGEventArgs(this));

    }
}