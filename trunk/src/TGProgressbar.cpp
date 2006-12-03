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
    //                        T G P r o g r e s s B a r 
    //-----------------------------------------------------------------------
    TGProgressBar::TGProgressBar(TGControl *parent, int x1, int y1, int x2, int y2)
        : TGControl(parent)
    {
        max.setControl(this);
        value.setControl(this);
        max.set(100);
        value.set(0);
        setBounds(x1, y1, x2, y2);
    }

    //-----------------------------------------------------------------------
    //                       ~ T G P r o g r e s s B a r 
    //-----------------------------------------------------------------------
    TGProgressBar::~TGProgressBar()
    {
    }

    //-----------------------------------------------------------------------
    //                             s e t M a x
    //-----------------------------------------------------------------------
    void TGProgressBar::setMax(float newMax)
    {
        if (newMax < 0.0f)
            newMax = 0.0f;
        max.set(newMax);
        if (value.get() > newMax)
            value.set(newMax);
    }

    //-----------------------------------------------------------------------
    //                           s e t V a l u e
    //-----------------------------------------------------------------------
    void TGProgressBar::setValue(float newValue)
    {
        if (newValue < 0)
            newValue = 0;
        if (newValue > max.get())
            newValue = max.get();
        value.set(newValue);
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGProgressBar::render()
    {
        int	x1, y1, x2, y2, w;
        float	value = this->value.get();
        getBounds(x1, y1, x2, y2);

        color(m_theme.getFrameFocusedColour());
        drawRect(x1, y1, x2, y2);

        if (value < 0.0f)
            value = 0.0f;
        if (value > max.get())
            value = max.get();

        if (max.get() == 0.0f || value == 0.0f)
            return;

        w = (int)((float)(x2-x1-2)*value/max.get());

        fillRect(x1 + 1, y1 + 1, x1 + w, y2 - 2);
    }
}