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
    //                        T G M e s s a g e B o x
    //-----------------------------------------------------------------------
    TGMessageBox::TGMessageBox(TGString msg, TGString caption) : TGWindow(TGSystem::getSingleton().getActiveScreen(),caption)
    {
        m_message = msg;
        m_caption = caption;
        TGLabel	*l = new TGLabel(this,"",msg);
        TGButton	*b = new TGButton(this, "OkButton" , "Ok");
        b->setBounds(0, 0, 100, 25);
        resize((l->x2 - l->x1) + 40, 80);
        l->center();
        b->moveRel(0, l->y2 + 15);
        b->center(true, false);
        resize(x2 - x1 + 1, y2 - y1 + 16 + b->y2 - b->y1);
        b->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&TGMessageBox::closeMessageBox,this));
        center();
        hide();
    }

    //-----------------------------------------------------------------------
    //                        ~ T G M e s s a g e B o x
    //-----------------------------------------------------------------------
    TGMessageBox::~TGMessageBox()
    {
    }

    //-----------------------------------------------------------------------
    //                       c l o s e M e s s a g e B o x
    //-----------------------------------------------------------------------
    bool TGMessageBox::closeMessageBox(const TGEventArgs& args)
    {
        TGSystem::getSingleton().destroyControl(this);
        return true;
    }

    //-----------------------------------------------------------------------
    //                              s h o w
    //-----------------------------------------------------------------------
    void TGMessageBox::show()
    {
        makeExclusive();
        TGControl::show();
    }
}