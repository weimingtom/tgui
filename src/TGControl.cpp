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
    //                           T G C o n t r o l
    //-----------------------------------------------------------------------
    TGControl::TGControl(TGControl *parent) : m_systemCache(TGSystem::getSingleton().getCache())
    {
        x1 = y1 = x2 = y2 = padLeft = padTop = padRight = padBottom = xShift =
            yShift = 0;
        minWidth = minHeight = 0;
        maxWidth = maxHeight = 0x7FFFFFFF;
        name = "";
        m_focusedChild = 0;
        m_parent = parent;
        m_redraw = false;
        if (m_parent)
        {
            m_parent->addChild(this);
            setColourTheme(m_parent->getColourTheme());
        }
        else
        {
            setColourTheme(TGSystem::getSingleton().getColourTheme());
        }
        performLayout = true;
        mouseOverControl = false;
        m_popupMenu = NULL;
        exclusiveChild = NULL;
        m_isVisible = true;
    }

    //-----------------------------------------------------------------------
    //                          ~ T G C o n t r o l
    //-----------------------------------------------------------------------
    TGControl::~TGControl()
    {
        invalidateControl(this);
        removeAllChildren();
        removeAllHandlers(this);
        if(m_popupMenu)
            delete m_popupMenu;

        if (m_parent)
        {
            if (m_parent->exclusiveChild == this)
                m_parent->exclusiveChild = NULL;
            m_parent->removeChild(this);
        }

    }

    //-----------------------------------------------------------------------
    //                          g e t R e n d e r e r
    //-----------------------------------------------------------------------
    TGRenderer* TGControl::getRenderer()
    {
        return TGSystem::getSingleton().getRenderer();
    }


    //-----------------------------------------------------------------------
    //                             s e t N a m e
    //-----------------------------------------------------------------------
    void TGControl::setName(string newName)
    {
        name = newName;
    }

    //-----------------------------------------------------------------------
    //                             f i n d C h i l d
    //-----------------------------------------------------------------------
    TGControl *TGControl::findChild(string name)
    {
        if (name.empty())
            return NULL;
        if (!name.compare(this->name))
            return this;

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            TGControl *r = (*itr)->findChild(name);
            if (r)
                return r;
        }

        return NULL;
    }

    //-----------------------------------------------------------------------
    //                             a d d C h i l d 
    //-----------------------------------------------------------------------
    void TGControl::addChild(TGControl *child)
    {
        if (!child)
            return;

        if (child->m_parent)
            child->m_parent->removeChild(child);

        child->m_parent = this;

        m_focusedChild = child;
        m_children.push_back(child);

        performLayout = true;
    }

    //-----------------------------------------------------------------------
    //                          r e m o v e C h i l d
    //-----------------------------------------------------------------------
    void TGControl::removeChild(TGControl *child)
    {
        if (!child || child->m_parent != this)
            return;

        child->m_parent = NULL;

        //child->removeAllChildren();

        m_children.remove(child);

        if(child == m_focusedChild)
        {
            if(m_children.size())
                m_focusedChild = m_children.back();
            else m_focusedChild = NULL;
        }

        performLayout = true;
    }

    //-----------------------------------------------------------------------
    //                       r e m o v e A l l C h i l d r e n
    //-----------------------------------------------------------------------
    void TGControl::removeAllChildren()
    {

        while(m_children.size())
        {
            TGControl* child = *m_children.begin();
            child->removeAllChildren();
            delete child;  // this will remove from the parent child list
        }
    }

    //-----------------------------------------------------------------------
    //                              c h i l d A t
    //-----------------------------------------------------------------------
    TGControl *TGControl::childAt(float x, float y)
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        if(!pointInControl(x,y))
            return this;

        TGControlListRevItr ritr = m_children.rbegin();

        for (ritr = m_children.rbegin();ritr != m_children.rend(); ++ritr)
        {
            if(!(*ritr)->isVisible())
                continue;
            if(!(*ritr)->pointInControl(x,y))
                continue;
            return (*ritr)->childAt(x, y);
        }

        return this;
    }

    //-----------------------------------------------------------------------
    //                      p o i n t I n C o n t r o l
    //-----------------------------------------------------------------------
    bool TGControl::pointInControl(float x, float y)
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        if ((x >= x1 && y >= y1 && x <= x2 && y <= y2))
            return true;
        return false;
    }

    //-----------------------------------------------------------------------
    //                             g e t S c r e e n
    //-----------------------------------------------------------------------
    TGScreen *TGControl::getScreen()
    {
        TGControl*   control = this;
        while (control->m_parent)
            control = control->m_parent;
        return (TGScreen*)control;
    }

    //-----------------------------------------------------------------------
    //                         m a k e E x c l u s i v e
    //-----------------------------------------------------------------------
    void TGControl::makeExclusive()
    {
        if (m_parent)
            m_parent->exclusiveChild = this;
    }

    //-----------------------------------------------------------------------
    //                                p u l s e
    //-----------------------------------------------------------------------
    void TGControl::pulse(float timeElapsed)
    {
        if (performLayout)
        {
            layout();
            performLayout = false;
        }
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            (*itr)->pulse(timeElapsed);
        }
    }

    //-----------------------------------------------------------------------
    //                      i s R e n d e r C a c h e d
    //-----------------------------------------------------------------------
    bool TGControl::isRenderCached()
    {
        if(!m_quadCache.size() || m_redraw)
        {
            m_quadCache.clear();
            return false;
        }

        if(!isVisible())
            return true;

        TGQuadList::iterator itr;

        for(itr=m_quadCache.begin(); itr!=m_quadCache.end(); itr++)
        {
            TGQuadInfo q = *itr;
            m_systemCache.push_back(q);
        }

        TGControl::render();

        return true;
    }

    //-----------------------------------------------------------------------
    //                             r e n d e r
    //-----------------------------------------------------------------------
    void TGControl::render()
    {
        int	x1, y1, x2, y2;
        if(!isVisible())
            return;

        getBounds(x1, y1, x2, y2);

        openClipArea(x1 + padLeft, y1 + padTop, x2 - padRight,
            y2 - padBottom);

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            if (*itr == exclusiveChild)
                continue;
            (*itr)->render();
            (*itr)->redraw(false);
        }

        if (exclusiveChild)
        {
            color(0, 0, 0, 96);
            TGControl::fillRect(x1, y1, x2, y2);

            exclusiveChild->render();
            exclusiveChild->redraw(false);
        }

        closeClipArea();
        m_redraw = false;
    }

    //-----------------------------------------------------------------------
    //                               f o c u s
    //-----------------------------------------------------------------------
    void TGControl::focus()
    {
        if (!m_parent)
            return;

        m_parent->focus();

        //if (m_parent->getLastChild() == this)
        //    return;

        TGControl *oldFocus = m_parent->getLastChild()->getFocusedChild();

        m_parent->setFocusedChild(this);

        if(oldFocus)
        {
            if(oldFocus->m_parent)
                oldFocus->m_parent->redraw();
            oldFocus->onFocusExit();
        }
        onFocusEnter();
    }

    //-----------------------------------------------------------------------
    //                              f o c u s e d
    //-----------------------------------------------------------------------
    bool TGControl::focused()
    {
        if (!m_parent)
            return true;
        return (m_parent->getFocusedChild() == this && m_parent->focused());
    }

    //-----------------------------------------------------------------------
    //                          s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGControl::setBounds(float fx1, float fy1, float fx2, float fy2)
    {
        int x1,x2,y1,y2;

        float sw,sh;

        if(!m_parent)
        {
            sw = getRenderer()->getWidth();
            sh = getRenderer()->getHeight();
        }
        else
        {
            int iw,ih;
            m_parent->getWidth(iw);
            m_parent->getHeight(ih);
            sw = iw;
            sh = ih;
            
        }


        x1 = sw * fx1;
        x2 = sw * fx2;
        y1 = sh * fy1;
        y2 = sh * fy2;

        int	oldX1 = this->x1;
        int	oldY1 = this->y1;
        int	oldW = this->x2 - this->x1;
        int	oldH = this->y2 - this->y1;
        if (x2 - x1 + 1 < minWidth)
            x2 = x1 + minWidth - 1;
        if (y2 - y1 + 1 < minHeight)
            y2 = y1 + minHeight - 1;
        if (x2 - x1 + 1 > maxWidth)
            x2 = x1 + maxWidth - 1;
        if (y2 - y1 + 1 > maxHeight)
            y2 = y1 + maxHeight - 1;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        if (x2 - x1 != oldW || y2 - y1 != oldH)
        {
            performLayout = true;
            fireEvent(TGEvent::Resized,TGEventArgs(this));
        }
        if (x1 != oldX1 || y1 != oldY1)
            fireEvent(TGEvent::Moved,TGEventArgs(this));
        redraw();
    }

    //-----------------------------------------------------------------------
    //                          s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGControl::setBounds(int x1, int y1, int x2, int y2)
    {
        int	oldX1 = this->x1;
        int	oldY1 = this->y1;
        int	oldW = this->x2 - this->x1;
        int	oldH = this->y2 - this->y1;
        if (x2 - x1 + 1 < minWidth)
            x2 = x1 + minWidth - 1;
        if (y2 - y1 + 1 < minHeight)
            y2 = y1 + minHeight - 1;
        if (x2 - x1 + 1 > maxWidth)
            x2 = x1 + maxWidth - 1;
        if (y2 - y1 + 1 > maxHeight)
            y2 = y1 + maxHeight - 1;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        if (x2 - x1 != oldW || y2 - y1 != oldH)
        {
            performLayout = true;
            fireEvent(TGEvent::Resized,TGEventArgs(this));
        }
        if (x1 != oldX1 || y1 != oldY1)
            fireEvent(TGEvent::Moved,TGEventArgs(this));
        redraw();
    }

    //-----------------------------------------------------------------------
    //                              s e t P o s
    //-----------------------------------------------------------------------
    void TGControl::setPos(int x1, int y1)
    {
        move(x1,y1);
    }

    //-----------------------------------------------------------------------
    //                              s e t P o s
    //-----------------------------------------------------------------------
    void TGControl::setPos(float x1, float y1)
    {
        move(x1,y1);

    }

    //-----------------------------------------------------------------------
    //                              g e t P o s
    //-----------------------------------------------------------------------
    void TGControl::getPos(int &x1, int &y1)
    {
        x1 = this->x1;
        y1 = this->y1;
    }

    //-----------------------------------------------------------------------
    //                              g e t P o s
    //-----------------------------------------------------------------------
    void TGControl::getPos(float &x1, float &y1)
    {
    }

    //-----------------------------------------------------------------------
    //                              m o v e
    //-----------------------------------------------------------------------
    void TGControl::move(int x, int y)
    {
        int	dx = x2 - x1, dy = y2 - y1;
        setBounds(x, y, x + dx, y + dy);
    }

    //-----------------------------------------------------------------------
    //                              m o v e
    //-----------------------------------------------------------------------
    void TGControl::move(float x, float y)
    {
        float sw,sh;

        if(!m_parent)
        {
            sw = getRenderer()->getWidth();
            sh = getRenderer()->getHeight();
        }
        else
        {
            int iw,ih;
            m_parent->getWidth(iw);
            m_parent->getHeight(ih);
            sw = iw;
            sh = ih;
            
        }

        int nx1 = sw * x;
        int ny1 = sh * y;
        move(nx1,ny1);
    }

    //-----------------------------------------------------------------------
    //                            r e s i z e
    //-----------------------------------------------------------------------
    void TGControl::resize(int width, int height)
    {
        setBounds(x1, y1, x1 + width - 1, y1 + height - 1);
    }

    //-----------------------------------------------------------------------
    //                            c e n t e r
    //-----------------------------------------------------------------------
    void TGControl::center(bool horizontal, bool vertical)
    {
        int	w, h, pw, ph;
        if (!m_parent)
            return;

        m_parent->getClientSize(pw, ph);
        getClientSize(w, h);

        if (horizontal)
            move(pw/2 - w/2, y1);
        if (vertical)
            move(x1, ph/2 - h/2);
    }

    //-----------------------------------------------------------------------
    //                           t r a n s l a t e
    //-----------------------------------------------------------------------
    void TGControl::translate(int &x, int &y)
    {
        for (TGControl *parent = m_parent;parent;parent=parent->m_parent)
        {
            x += parent->x1 + parent->padLeft;
            y += parent->y1 + parent->padTop;
        }
    }

    //-----------------------------------------------------------------------
    //                           g e t B o u n d s
    //-----------------------------------------------------------------------
    void TGControl::getBounds(int &x1, int &y1, int &x2, int &y2)
    {
        x1 = this->x1 - xShift;
        y1 = this->y1 - yShift;
        x2 = this->x2 - xShift;
        y2 = this->y2 - yShift;
        translate(x1, y1);
        translate(x2, y2);
    }

    //-----------------------------------------------------------------------
    //                           g e t B o u n d s
    //-----------------------------------------------------------------------
    void TGControl::getBounds(float &x1, float &y1, float &x2, float &y2)
    {
        int ix1,iy1,ix2,iy2;
        getBounds(ix1,iy1,ix2,iy2);
        float sw = getRenderer()->getWidth();
        float sh = getRenderer()->getHeight();

        x1 = (float)ix1 * sw;
        x2 = (float)ix2 * sw;
        y1 = (float)iy1 * sh;
        y2 = (float)iy2 * sh;
    }

    //-----------------------------------------------------------------------
    //                             s e t W i d t h
    //-----------------------------------------------------------------------
    void TGControl::setWidth(int width)
    {
        setBounds(x1,y1,x1+width,y2);
    }

    //-----------------------------------------------------------------------
    //                             s e t W i d t h
    //-----------------------------------------------------------------------
    void TGControl::setWidth(float width)
    {
        float fx1,fx2,fy1,fy2;
        getBounds(fx1,fy1,fx2,fy2);
        setBounds(fx1,fy1,fx1+width,fy2);
    }

    //-----------------------------------------------------------------------
    //                             g e t W i d t h
    //-----------------------------------------------------------------------
    void TGControl::getWidth(int &width)
    {
        width = x2-x1;
    }

    //-----------------------------------------------------------------------
    //                             g e t W i d t h
    //-----------------------------------------------------------------------
    void TGControl::getWidth(float &width)
    {
        float fx1,fx2,fy1,fy2;
        getBounds(fx1,fy1,fx2,fy2);
        width = fx2-fx1;
    }

    //-----------------------------------------------------------------------
    //                            s e t H e i g h t
    //-----------------------------------------------------------------------
    void TGControl::setHeight(int height)
    {
        setBounds(x1,y1,x2,y1+height);
    }

    //-----------------------------------------------------------------------
    //                            s e t H e i g h t
    //-----------------------------------------------------------------------
    void TGControl::setHeight(float height)
    {
        float fx1,fx2,fy1,fy2;
        getBounds(fx1,fy1,fx2,fy2);
        setBounds(fx1,fy1,fx2,fy1+height);
    }

    //-----------------------------------------------------------------------
    //                            g e t H e i g h t
    //-----------------------------------------------------------------------
    void TGControl::getHeight(int &height)
    {
        height = y2-y1;
    }

    //-----------------------------------------------------------------------
    //                            g e t H e i g h t
    //-----------------------------------------------------------------------
    void TGControl::getHeight(float &height)
    {
        float fx1,fx2,fy1,fy2;
        getBounds(fx1,fy1,fx2,fy2);
        height = fy2-fy1;
    }



    //-----------------------------------------------------------------------
    //                           s e t P a d d i n g
    //-----------------------------------------------------------------------
    void TGControl::setPadding(int left, int top, int right, int bottom)
    {
        if (left != -1)
            padLeft = left;
        if (top != -1)
            padTop = top;
        if (right != -1)
            padRight = right;
        if (bottom != -1)
            padBottom = bottom;
    }

    //-----------------------------------------------------------------------
    //                         g e t C l i e n t S i z e
    //-----------------------------------------------------------------------
    void TGControl::getClientSize(int &w, int &h)
    {
        w = x2 - x1 - padLeft - padRight + 1;
        h = y2 - y1 - padTop - padBottom + 1;
    }

    //-----------------------------------------------------------------------
    //                          d r a w O w n F r a m e
    //-----------------------------------------------------------------------
    void TGControl::drawOwnFrame()
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        drawFrame(x1, y1, x2, y2);
    }

    //-----------------------------------------------------------------------
    //                          d r a w O w n F o c u s
    //-----------------------------------------------------------------------
    void TGControl::drawOwnFocus()
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        color(m_theme.getFrameSelectedColour());
        drawRect(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E n t e r
    //-----------------------------------------------------------------------
    void TGControl::onMouseEnter()
    {
        mouseOverControl = true;
        redraw();
    }

    //-----------------------------------------------------------------------
    //                         o n M o u s e M o v e d
    //-----------------------------------------------------------------------
    void TGControl::onMouseMoved(int x, int y)
    {
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E x i t
    //-----------------------------------------------------------------------
    void TGControl::onMouseExit()
    {
        mouseOverControl = false;
        redraw();
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e D o w n
    //-----------------------------------------------------------------------
    void TGControl::onMouseDown(int x, int y, int b)
    {
        if (b == LeftButton)
        {
            setKeyboardFocusControl(this);
            focus();
            fireEvent(TGEvent::MouseClicked,TGEventArgs(this));
        }
        if (b == RightButton)
        {
            if (m_popupMenu)
                m_popupMenu->run();
        }
    }

    //-----------------------------------------------------------------------
    //                           o n M o u s e U p
    //-----------------------------------------------------------------------
    void TGControl::onMouseUp(int x, int y, int b)
    {
    }

    //-----------------------------------------------------------------------
    //                            o n K e y D o w n
    //-----------------------------------------------------------------------
    void TGControl::onKeyDown(int key, unsigned char ascii)
    {
    }

    //-----------------------------------------------------------------------
    //                              o n K e y U p
    //-----------------------------------------------------------------------
    void TGControl::onKeyUp(int key, unsigned char ascii)
    {
    }

    //-----------------------------------------------------------------------
    //                s e t M o u s e T r a c k i n g C o n t r o l
    //-----------------------------------------------------------------------
    void TGControl::setMouseTrackingControl(TGControl *control)
    {
        TGSystem::getSingleton().setMouseTrackingControl(control);
    }

    //-----------------------------------------------------------------------
    //              s e t K e y b o a r d F o c u s C o n t r o l
    //-----------------------------------------------------------------------
    void TGControl::setKeyboardFocusControl(TGControl *control)
    {
        TGSystem::getSingleton().setKeyboardFocusControl(control);
    }

    //-----------------------------------------------------------------------
    //                    h a s K e y b o a r d F o c u s
    //-----------------------------------------------------------------------
    bool TGControl::hasKeyboardFocus(TGControl *control)
    {
        return TGSystem::getSingleton().hasKeyboardFocus(control);
    }

    //-----------------------------------------------------------------------
    //                  i n v a l i d a t e C o n t r o l
    //-----------------------------------------------------------------------
    void TGControl::invalidateControl(TGControl *control)
    {
        TGSystem::getSingleton().invalidateControl(control);
    }

    //-----------------------------------------------------------------------
    //                     g e t A c t i v e S c r e e n
    //-----------------------------------------------------------------------
    TGScreen* TGControl::getActiveScreen()
    {
        return TGSystem::getSingleton().getActiveScreen();
    }

    //-----------------------------------------------------------------------
    //                                c o l o r
    //-----------------------------------------------------------------------
    void TGControl::color(int r, int g, int b, int a)
    {
        gColor.r = r/255.f;
        gColor.g = g/255.f;
        gColor.b = b/255.f;
        gColor.a = a/255.f;
    }

    //-----------------------------------------------------------------------
    //                                c o l o r
    //-----------------------------------------------------------------------
    void TGControl::color(TGColour c)
    {
        gColor = c;
    }

    //-----------------------------------------------------------------------
    //                            d r a w R e c t
    //-----------------------------------------------------------------------
    void TGControl::drawRect(int x1, int y1, int x2, int y2,int thickness)
    {
        if(!m_isVisible)
            return;

        drawLine(x1,y1,x2,y1,thickness);
        drawLine(x2,y1,x2,y2,thickness);
        drawLine(x1,y2,x2,y2,thickness);
        drawLine(x1,y1,x1,y2,thickness);
    }

    //-----------------------------------------------------------------------
    //                            f i l l R e c t
    //-----------------------------------------------------------------------
    void TGControl::fillRect(int x1, int y1, int x2, int y2)
    {
        if(!m_isVisible)
            return;
        TGRect r(x1,y1,x2,y2);
        TGColourRect cr(gColor);
        TGQuadInfo qi = TGSystem::getSingleton().getRenderer()->addQuad(r,0,TGSystem::getSingleton().getDefaultTexture(),r,cr);
        m_quadCache.push_back(qi);
    }


    //-----------------------------------------------------------------------
    //                            d r a w L i n e
    //-----------------------------------------------------------------------
    void TGControl::drawLine(int x1, int y1, int x2, int y2,int thickness)
    {
        if(!m_isVisible)
            return;
        TGRect r(x1,y1,x2,y2);
        TGColourRect cr(gColor);

        int xdir= (x2-x1) < 0 ? -1 : 1;
        int ydir= (y2-y1) < 0 ? -1 : 1;

        TGQuadInfo qi = TGSystem::getSingleton().getRenderer()->addLine(r,0,TGSystem::getSingleton().getDefaultTexture(),
            r,cr,thickness);
        m_quadCache.push_back(qi);
    }

    //-----------------------------------------------------------------------
    //                            d r a w F r a m e
    //-----------------------------------------------------------------------
    void TGControl::drawFrame(int x1, int y1, int x2, int y2, FrameStyle s,int thickness)
    {
        if(!m_isVisible)
            return;
        color(m_theme.getBaseOpaque());
        if (!s)
        {
            fillRect(x1, y1, x2, y2);
            return;
        }
        fillRect(x1, y1, x2, y2);
        switch (s)
        {
        case FS_FLAT:
            color(m_theme.getFrameColour());
            drawRect(x1, y1, x2, y2);
            break;
        case FS_RAISED:
            color(m_theme.getFrameFocusedColour());
            drawRect(x1, y1, x2, y2);
            break;
        case FS_LOWERED:
            color(m_theme.getFrameSelectedColour());
            drawRect(x1, y1, x2, y2);
            break;
        default:
            break;
        }
    }

    //-----------------------------------------------------------------------
    //                           d r a w S t r i n g
    //-----------------------------------------------------------------------
    void TGControl::drawString(int x, int y, string str, int length)
    {
        if(!m_isVisible)
            return;
        TGFont* font = TGSystem::getSingleton().getCurrentFont();
        if(!font)
            return;

        int cHeight=font->getHeight();

        float	cx = x;
        if (length == -1)
            length = (int)str.length();

        for (int i=0;i<length;i++)
        {
            char ch=str[i];
            if (ch == ' ')
            {
                cx += 5;
                continue;
            }

            int x2,y2;
            int cWidth = font->m_font->getGlyphAspectRatio(ch) * cHeight;
            x2 = cx + cWidth;
            y2 = y+cHeight;


            TGRect r(cx,y,x2,y2);
            TGColourRect cr(gColor);
            TGRect ruv;

            font->m_font->getGlyphTexCoords(ch,ruv.d_left,ruv.d_top,ruv.d_right,ruv.d_bottom);

            TGQuadInfo qi = TGSystem::getSingleton().getRenderer()->addQuad(r,0,font->m_texture,ruv,cr);
            m_quadCache.push_back(qi);

            cx += cWidth + 1.0f;
        }
    }



    //-----------------------------------------------------------------------
    //                          s t r i n g W i d t h
    //-----------------------------------------------------------------------
    int TGControl::stringWidth(string str, size_t length)
    {
        TGFont* font = TGSystem::getSingleton().getCurrentFont();
        if(!font)
            return 0;
        float	cx = 0;
        if (length == -1)
            length = str.length();

        for (size_t i=0;i<length;i++)
        {
            if (str[i] == ' ')
            {
                cx += 5;
                continue;
            }
            int cWidth = font->m_font->getGlyphAspectRatio(str[i]) * font->getHeight();
            cx += cWidth + 1;
        }
        return (int)cx;
    }

    //-----------------------------------------------------------------------
    //                          s t r i n g H e i g h t
    //-----------------------------------------------------------------------
    int TGControl::stringHeight()
    {
        TGFont* font = TGSystem::getSingleton().getCurrentFont();
        if(!font)
            return 0;
        return font->getHeight();
    }

    //-----------------------------------------------------------------------
    //                            o p e n C l i p
    //-----------------------------------------------------------------------
    void TGControl::openClip()
    {
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        openClipArea(x1, y1, x2, y2);
    }

    //-----------------------------------------------------------------------
    //                           c l o s e C l i p
    //-----------------------------------------------------------------------
    void TGControl::closeClip()
    {
        closeClipArea();
    }

    //-----------------------------------------------------------------------
    //                       r e s e t C l i p p i n g
    //-----------------------------------------------------------------------
    void TGControl::resetClipping()
    {
        getRenderer()->resetClipping();

    }

    //-----------------------------------------------------------------------
    //                         o p e n C l i p A r e a
    //-----------------------------------------------------------------------
    void TGControl::openClipArea(int x1, int y1, int x2, int y2)
    {
        getRenderer()->openClipArea(x1,y1,x2,y2);

    }

    //-----------------------------------------------------------------------
    //                          c l o s e C l i p A r e a
    //-----------------------------------------------------------------------
    void TGControl::closeClipArea()
    {
        getRenderer()->closeClipArea();
    }

    //-----------------------------------------------------------------------
    //                        g e t F i r s t C h i l d
    //-----------------------------------------------------------------------
    TGControl* TGControl::getFirstChild()
    {
        if(m_children.size())
            return m_children.front();
        else return NULL;
    }

    //-----------------------------------------------------------------------
    //                        g e t L a s t C h i l d
    //-----------------------------------------------------------------------
    TGControl* TGControl::getLastChild()
    {
        return m_children.back();
    }

    //-----------------------------------------------------------------------
    //                     s e t F o c u s e d C h i l d
    //-----------------------------------------------------------------------
    void TGControl::setFocusedChild(TGControl* child)
    {
        m_focusedChild = child;

        //
        // put the "focused" child at the back of the list
        //
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            TGControl *c = *itr;
            if (c == child)
            {
                m_children.erase(itr);
                m_children.push_back(c);
                break;

            }
        }
    }

    //-----------------------------------------------------------------------
    //                     a d d E v e n t H a n d l e r
    //-----------------------------------------------------------------------
    void TGControl::addEventHandler(string eventID, TGEventHandler* handler)
    {

        TGEventMap::iterator itr;
        itr = m_handlers.find(eventID);

        //
        // if not found, then create a new handler map entry
        //
        if(itr == m_handlers.end())
        {
            m_handlers[eventID] = TGEventHandlers();
            itr = m_handlers.find(eventID);
        }

        itr->second.push_back(handler);
    }

    //-----------------------------------------------------------------------
    //                  r e m o v e E v e n t H a n d l e r
    //-----------------------------------------------------------------------
    void TGControl::removeEventHandler(string eventID, TGEventHandler* handler)
    {
    }

    //-----------------------------------------------------------------------
    //                    r e m o v e A l l H a n d l e r s
    //-----------------------------------------------------------------------
    void TGControl::removeAllHandlers(void* obj)
    {
    }

    //-----------------------------------------------------------------------
    //                    r e m o v e A l l H a n d l e r s
    //-----------------------------------------------------------------------
    void TGControl::removeAllHandlers(TGControl* control)
    {
        TGEventMap::iterator itr;
        itr = m_handlers.begin();

        while(itr != m_handlers.end())
        {

            TGEventHandlers::iterator eitr = itr->second.begin();

            while(eitr != itr->second.end())
            {
                TGEventHandler* eh = *eitr;
                delete eh;

                ++eitr;
            }
            itr->second.clear();
            ++itr;
        }

    }

    //-----------------------------------------------------------------------
    //                          l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TGControl::logMessage(string message)
    {
        TGSystem::getSingleton().logMessage(message);
    }

    //-----------------------------------------------------------------------
    //                       s e t C o l o u r T h e m e
    //-----------------------------------------------------------------------
    void TGControl::setColourTheme(TGColourTheme theme,bool updateChildren) 
    {
        m_theme = theme;
        if(!updateChildren)
            return;

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            (*itr)->setColourTheme(theme,true);
        }
        redraw();

    }

    //-----------------------------------------------------------------------
    //                         f i r e E v e n t
    //-----------------------------------------------------------------------
    bool TGControl::fireEvent(string eventID,TGEventArgs& args)
    {
        bool rc=false;

        args.m_eventID = eventID;

        TGEventMap::iterator itr;
        itr = m_handlers.find(eventID);

        //
        // map entry?
        //
        if(itr == m_handlers.end())
            return false;

        TGEventHandlers::iterator eitr = itr->second.begin();

        while(eitr != itr->second.end())
        {
            TGEventHandler* eh = *eitr;

            rc = (*eh)(args);
            if(rc)
                return true;

            ++eitr;
        }

        return rc;
    }

    //-----------------------------------------------------------------------
    //                           r e d r a w
    //-----------------------------------------------------------------------
    void TGControl::redraw(bool value) 
    {
        m_redraw = value;
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            (*itr)->redraw(value);
        }

    };

}