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
    //                           T G I n p u t
    //-----------------------------------------------------------------------
    TGInputbox::TGInputbox(TGControl *parent, int x1, int y1, int x2, int y2)
        : TGControl(parent)
    {
        text.setControl(this);
        text.set(_strdup(""));
        place(x1, y1, x2, y2);
        tScroll = 0;
        cursor = cursorX = 0;
    }

    //-----------------------------------------------------------------------
    //                          ~ T G I n p u t
    //-----------------------------------------------------------------------
    TGInputbox::~TGInputbox()
    {
    }

    //-----------------------------------------------------------------------
    //                            s e t T e x t
    //-----------------------------------------------------------------------
    void TGInputbox::setText(string newText)
    {
        int     w, h;
        getClientSize(w, h);
        text.set(newText);
        cursor = newText.length();
        cursorX = stringWidth(newText);
        tScroll = 0;
        if (cursorX - tScroll > w - 10)
            tScroll = cursorX - w + (w/2);
    }

    //-----------------------------------------------------------------------
    //                           g e t T e x t
    //-----------------------------------------------------------------------
    string TGInputbox::getText()
    {
        return text.get();
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGInputbox::render()
    {
        int			x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        color(120, 134, 135);
        fillRect(x1, y1 + 1, x2 - 1, y2);

        color(20, 34, 35);
        drawString(x1 + 5 - tScroll, y1 + (y2 - y1)/2 -
            stringHeight()/2, text.get());

        if (hasKeyboardFocus(this))
        {
            drawLine(x1 + 5 + cursorX - tScroll, y1 + 4,
                x1 + 5 + cursorX - tScroll, y2 - 4);
        }

        if (mouseOverControl)
            color(210, 224, 225);
        else
            color(170, 184, 185);
        drawRect(x1, y1, x2, y2);
    }

    //-----------------------------------------------------------------------
    //                         o n K e y D o w n
    //-----------------------------------------------------------------------
    void TGInputbox::onKeyDown(int key, unsigned char ascii)
    {
        int     w, h;
        string text = this->text.get();
        getClientSize(w, h);
        switch (ascii)
        {
        case 8:
            if (!text.empty())
            {
                text = text.substr(1,text.length()-1);
                cursorX = stringWidth(text,--cursor);
                if (cursorX - tScroll < 0)
                {
                    tScroll = cursorX - (w/2);
                    if (tScroll < 0)
                        tScroll = 0;
                }
            }
            break;
        default:
            if (ascii < 32 || ascii > 127)
                break;
            text += ascii;
            cursorX = stringWidth(text, ++cursor);
            if (cursorX - tScroll > w - 10)
                tScroll = cursorX - w + (w/2);
            break;
        }
        this->text.set(text);
    }

    //-----------------------------------------------------------------------
    //                           o n K e y U p
    //-----------------------------------------------------------------------
    void TGInputbox::onKeyUp(int key, unsigned char ascii)
    {
    }
}