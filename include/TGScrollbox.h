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
#ifndef __TGSCROLLBOX_H__
#define __TGSCROLLBOX_H__

namespace TGUI
{

    struct TGScrollbox : public TGControl
    {
        float   clientWidth;
        float   clientHeight;
        float   hScrollMax;
        float   vScrollMax;
        float   hScroll;
        float   vScroll;
        int	scrolling;      // 0=no, 1=vertical, 2=horizontal
        TGAction  *scrolled;

        TGScrollbox(TGControl *parent, int x1, int y1, int x2, int y2);
        virtual ~TGScrollbox();

        virtual void setScrollingBounds(float hMax, float vMax);

        virtual void render();
        virtual void place(int x1, int y1, int x2, int y2);
        virtual void layout();

        virtual void onScroll(float hd, float vd);

        virtual void onMouseDown(int x, int y, int b);
        virtual void onMouseMoved(int x, int y);
        virtual void onMouseUp(int x, int y, int b);
    };
}
#endif

