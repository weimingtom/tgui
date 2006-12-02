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
    //                            T G W i n d o w
    //-----------------------------------------------------------------------
    TGWindow::TGWindow(string caption) : TGControl(getActiveScreen())
    {
        moving = resizing = resizeable = false;
        minWidth = 50;
        minHeight = 50;
        setBounds(10, 10, 200, 160);
        this->caption = caption;
        padLeft = padRight = padBottom = 2;
        padTop = 6 + stringHeight();
        m_titleBarHeight = stringHeight() + 2;
        menu = NULL;
        icon = NULL;
        isTabbedCaption = false;
    }

    //-----------------------------------------------------------------------
    //                            T G W i n d o w
    //-----------------------------------------------------------------------
    TGWindow::TGWindow(TGScreen *screen, string caption) : TGControl(screen)
    {
        moving = resizing = resizeable = false;
        minWidth = 1;
        minHeight = 1;
        setBounds(10, 10, 200, 160);
        this->caption = caption;
        padLeft = padRight = padBottom = 2;
        padTop = 6 + stringHeight();
        m_titleBarHeight = stringHeight() + 2;
        menu = NULL;
        icon = NULL;
    }

    //-----------------------------------------------------------------------
    //                           ~ T G W i n d o w
    //-----------------------------------------------------------------------
    TGWindow::~TGWindow()
    {
        if (icon)
            delete icon;
        if (menu)
            delete menu;
    }

    //-----------------------------------------------------------------------
    //                           s e t C a p t i o n
    //-----------------------------------------------------------------------
    void TGWindow::setCaption(string newCaption)
    {
        caption = newCaption;
    }

    //-----------------------------------------------------------------------
    //                      p o i n t I n C o n t r o l
    //-----------------------------------------------------------------------
    bool TGWindow::pointInControl(float x, float y)
    {
        if(!isTabbedCaption)
            return TGControl::pointInControl(x,y);

        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        y1 = y1 + m_titleBarHeight;
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
            return true;

        return pointInCaption(x,y);
    }

    //-----------------------------------------------------------------------
    //                      p o i n t I n C a p t i o n
    //-----------------------------------------------------------------------
    bool TGWindow::pointInCaption(float x,float y)
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        y2 = y1 + m_titleBarHeight;
        if(isTabbedCaption)
            x2 = x1+stringWidth(caption)+(stringWidth("M")*2);
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    //                              r e n d e r
    //-----------------------------------------------------------------------
    void TGWindow::render()
    {
        int	x1, y1, x2, y2;
        int	clen, titleY2;
        TGRect cRect;
        getBounds(x1, y1, x2, y2);

        titleY2 = y1 + m_titleBarHeight;

        clen = (int)stringWidth(caption);
        if(isTabbedCaption)
            cRect = TGRect(x1, y1, x1+clen+(stringWidth("M")*2),titleY2);
        else cRect = TGRect(x1, y1, x2, titleY2);

        if(!caption.empty())
        {

            color(m_theme.getCaptionColour());
            fillRect(cRect.d_left, cRect.d_top, cRect.d_right, cRect.d_bottom);

            color(m_theme.getBase());
            fillRect(x1, titleY2, x2, y2);
        }
        else
        {
            color(m_theme.getBase());
            fillRect(this->x1, this->y1, this->x2, this->y2);
        }

        TGColour frameColour;
        if (focused())
        {
            frameColour = m_theme.getFrameFocusedColour();
            color(frameColour);
            drawRect(cRect.d_left, cRect.d_top, cRect.d_right, cRect.d_bottom);
            drawRect(x1, titleY2, x2, y2);
            color(m_theme.getTextFocusedColour());
        }
        else
        {
            frameColour = m_theme.getFrameColour();
            color(frameColour);
            drawRect(cRect.d_left, cRect.d_top, cRect.d_right, cRect.d_bottom);
            drawRect(x1, titleY2, x2, y2);
            color(m_theme.getTextColour());
        }

        if(!caption.empty())
        {
            openClip();
            if(!isTabbedCaption)
                drawString((x2-x1)/2 + x1 - clen/2, y1 + 2, caption);
            else drawString(x1+stringWidth("M"),y1 + 2, caption);
            closeClip();
        }

        TGControl::render();

        if (resizeable)
        {
            color(frameColour);
            drawLine(x2 - 15, y2-1, x2-1, y2 - 15);
            drawLine(x2 - 10, y2-1, x2-1, y2 - 10);
            drawLine(x2 - 5, y2-1, x2-1, y2 - 5);
        }

        if (icon)
        {
            icon->draw(x1 + 1, y1 + (titleY2-y1)/2 - icon->getHeight()/2);
        }
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGWindow::onMouseDown(int x, int y, int b)
    {
        int	x1, y1, x2, y2, titleY2;
        getBounds(x1, y1, x2, y2);

        if(isTabbedCaption)
            x2 = x1+stringWidth(caption)+(stringWidth("M")*2);

        titleY2 = stringHeight() + y1 + 2;

        if (b == LeftButton)
            focus();
        if (resizeable && x >= x2-10 && y >= y2-10)
        {
            resizing = true;
            mX = x;
            mY = y;
            setMouseTrackingControl(this);
        }
        else
        {
            if (icon && menu && (x > x1 && x < x1 + (int)icon->getWidth() && y >
                y1 + (titleY2-y1)/2 - (int)icon->getHeight()/2 &&
                y < y1 + (titleY2-y1)/2 - (int)icon->getHeight()/2 +
                (int)icon->getHeight()))
            {
                menu->run(x1 + 4, y1 + (titleY2-y1)/2 + icon->getHeight() -
                    icon->getHeight()/2);
                return;
            }
            else if ( (x > x1) && (x < x2) && (y > y1) && (y < titleY2) )
            {
                moving = true;
                mX = x-x1;
                mY = y-y1;
                setMouseTrackingControl(this);
            }
        }
        //setMouseTrackingControl(this);
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e M o v e d
    //-----------------------------------------------------------------------
    void TGWindow::onMouseMoved(int x, int y)
    {
        if (moving)
            move(x-mX, y-mY);
        if (resizing)
        {
            resize((x2-x1+1)+x-mX, (y2-y1+1)+y-mY);
            mX = x;
            mY = y;
        }
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGWindow::onMouseUp(int x, int y, int b)
    {
        if (!(moving || resizing))
            return;
        moving = resizing = false;
        setMouseTrackingControl(NULL);
    }
}