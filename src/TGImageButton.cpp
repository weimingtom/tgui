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
    //                         T G I m a g e B u t t o n
    //-----------------------------------------------------------------------
    TGImageButton::TGImageButton(TGControl *parent, TGString name, TGString imageName, 
        TGString resourceGroup) : TGControl(parent, name)
    {
        m_uvIndex = 0;
        m_pushed = m_highlighted = false;

        m_images = new TGImageSet(imageName,4,resourceGroup);
        setBounds(0, 0, m_images->getWidth(),m_images->getHeight() / 4);
    }

    //-----------------------------------------------------------------------
    //                        ~ T G I m a g e B u t t o n
    //-----------------------------------------------------------------------
    TGImageButton::~TGImageButton()
    {
        if(m_images)
            delete m_images;
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGImageButton::render()
    {
        if(isRenderCached())
            return;

        int			x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);

        TGSBrush brush;
        brush.bind(new TGBrush(m_images->getTexture()));
        brush->m_uv = m_images->getUVRect(m_uvIndex);

        fillRect(x1,y1,x2,y2,brush);

    }

    //-----------------------------------------------------------------------
    //                         o n M o u s e D o w n 
    //-----------------------------------------------------------------------
    void TGImageButton::onMouseDown(int x, int y, int b)
    {
        focus();
        if (b == LeftButton)
        {
            setMouseTrackingControl(this);
            m_pushed = true;
            m_uvIndex = 2;
            redraw();
            fireEvent(TGEvent::MouseDown,TGEventArgs(this));
        }
    }

    //-----------------------------------------------------------------------
    //                           o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGImageButton::onMouseUp(int x, int y, int b)
    {
        if (!focused())
            return;
        if (b == LeftButton && m_pushed)
        {
            setMouseTrackingControl(NULL);
            if (m_mouseOverControl)
            {
                m_uvIndex = 1;
                fireEvent(TGEvent::MouseClicked,TGEventArgs(this));
            }
            else m_uvIndex = 0;
            redraw();
        }
        m_pushed = false;
    }

    //-----------------------------------------------------------------------
    //                        o n M o u s e E n t e r
    //-----------------------------------------------------------------------
    void TGImageButton::onMouseEnter()
    {
        TGControl::onMouseEnter();
        if(!m_pushed)
            m_uvIndex = 1;
        else m_uvIndex = 2;
        redraw();
        fireEvent(TGEvent::MouseEnter,TGEventArgs(this));

    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E x i t
    //-----------------------------------------------------------------------
    void TGImageButton::onMouseExit(int x, int y)
    {
        TGControl::onMouseExit(x,y);
        if(!m_pushed)
            m_uvIndex = 0;
        else m_uvIndex = 1;
        redraw();
        fireEvent(TGEvent::MouseExit,TGEventArgs(this));
   }

}