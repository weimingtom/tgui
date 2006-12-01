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
    //                             T G S l i d e r
    //-----------------------------------------------------------------------
    TGSlider::TGSlider(TGControl *parent, int x1, int y1, int x2, int y2)
        : TGControl(parent)
    {
        sliding = false;
        setBounds(x1, y1, x2, y2);
        max = 5;
        value.setControl(this);
        value.set(0);
    }

    //-----------------------------------------------------------------------
    //                            ~ T G S l i d e r
    //-----------------------------------------------------------------------
    TGSlider::~TGSlider()
    {
    }

    //-----------------------------------------------------------------------
    //                               r e n d e r
    //-----------------------------------------------------------------------
    void TGSlider::render()
    {
        int			x1, y1, x2, y2, width, height, sx;
        getBounds(x1, y1, x2, y2);
        width = x2 - x1 + 1;
        height = y2 - y1 + 1;

        sx = (int)(x1 + (width-9)*value.get()/max + 4);

        color(m_theme.getFrameFocusedColour());
        drawLine(x1 + 4, y1 + height/2, x2 - 4, y1 + height/2);

        if(mouseOverControl)
            fillRect(sx - 4, y1, sx + 4, y2);
        else drawFrame(sx - 4, y1, sx + 4, y2, FS_RAISED);
    }

    //-----------------------------------------------------------------------
    //                             s e t V a l u e
    //-----------------------------------------------------------------------
    void TGSlider::setValue(float newValue)
    {
        value.set(newValue);
        fireEvent(TGEvent::Modified,TGEventArgs(this));
    }

    //-----------------------------------------------------------------------
    //                             s e t M a x
    //-----------------------------------------------------------------------
    void TGSlider::setMax(float newMax)
    {
        max = newMax;
        if (value.get() > max)
            setValue(max);
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGSlider::onMouseDown(int x, int y, int b)
    {
        if (b != LeftButton)
            return;
        focus();
        sliding = true;
        setMouseTrackingControl(this);
        onMouseMoved(x, y);
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e M o v e d
    //-----------------------------------------------------------------------
    void TGSlider::onMouseMoved(int x, int y)
    {
        int	x1, y1, x2, y2, width, height;
        float   oldValue = value.get();

        if (!sliding)
            return;

        getBounds(x1, y1, x2, y2);
        width = x2 - x1 + 1;
        height = y2 - y1 + 1;

        if (x < x1+3)
            x = x1+3;
        else
            if (x > x2-4)
                x = x2-4;

        value.set(max*(float)(x-3-x1)/(float)(width-8));
        if (value.get() < 0.0f)
            value.set(0.0f);
        else
            if (value.get() > max)
                value.set(max);

        if (value.get() != oldValue)
            fireEvent(TGEvent::Modified,TGEventArgs(this));
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGSlider::onMouseUp(int x, int y, int b)
    {
        if (b != LeftButton || !sliding)
            return;
        sliding = false;
        setMouseTrackingControl(NULL);
    }
}