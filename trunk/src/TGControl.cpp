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
    int TGControl::m_controlNumber=1;

    //-----------------------------------------------------------------------
    //                           T G C o n t r o l
    //-----------------------------------------------------------------------
    TGControl::TGControl(TGControl *parent, TGString name) : m_systemCache(TGSystem::getSingleton().getCache())
        , m_theme(TGTheme())
        , m_frameEnabled(true)
        , m_backgroundEnabled(true)
        , m_renderer(TGSystem::getSingleton().getRenderer())
        , m_system(TGSystem::getSingletonPtr())
        , m_minWidth(0), m_minHeight(0)
        , m_maxWidth(0x7FFFFFFF), m_maxHeight(0x7FFFFFFF)
        , m_focusedChild(0)
        , m_isComposite(false)
        , m_parent(parent)
        , m_redraw(true)
        , m_popupMenu(NULL)
        , x1(0), y1(0), x2(0), y2(0)
        , m_padLeft(0), m_padTop(0), m_padRight(0), m_padBottom(0)
        , xShift(0), yShift(0)
        , m_performLayout(true)
        , m_mouseOverControl(false)
        , m_isVisible(true)
        , m_exclusiveChild(NULL)
        , m_font(TGSystem::getSingleton().getCurrentFont())
        , m_texture(TGSystem::getSingleton().getDefaultTexture())
    {
        if(name.empty())
        {
            Ogre::StringUtil::StrStreamType genName;
            genName << "_noname_" << m_controlNumber++;
            m_name = genName.str();
        }
        else m_name = name;

        if (m_parent)
        {
            m_parent->addChild(this);
            setTheme(m_parent->getTheme());
        }
        else
        {
            setTheme(TGSystem::getSingleton().getTheme());
        }
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
            if (m_parent->m_exclusiveChild == this)
                m_parent->m_exclusiveChild = NULL;
            m_parent->removeChild(this);
        }
    }

    //-----------------------------------------------------------------------
    //                          g e t R e n d e r e r
    //-----------------------------------------------------------------------
    TGRenderer* TGControl::getRenderer()
    {
        return m_renderer;
    }

    //-----------------------------------------------------------------------
    //                             s e t N a m e
    //-----------------------------------------------------------------------
    void TGControl::setName(TGString value)
    {
        m_name = value;
    }

    //-----------------------------------------------------------------------
    //                             f i n d C h i l d
    //-----------------------------------------------------------------------
    TGControl *TGControl::findChild(TGString name)
    {
        if (name.empty())
            return NULL;
        if (!name.compare(m_name))
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

        m_performLayout = true;
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

        m_performLayout = true;
    }

    //-----------------------------------------------------------------------
    //                       r e m o v e A l l C h i l d r e n
    //-----------------------------------------------------------------------
    void TGControl::removeAllChildren()
    {

        while(m_children.size())
        {
            TGControl* child = *m_children.begin();
            delete child;  // this will remove from the parent child list
        }
    }

    //-----------------------------------------------------------------------
    //                              c h i l d A t
    //-----------------------------------------------------------------------
    TGControl *TGControl::childAt(TGReal x, TGReal y)
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
    bool TGControl::pointInControl(TGReal x, TGReal y)
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
    void TGControl::makeExclusive(bool value)
    {
        TGScreen* ascreen = TGSystem::getSingleton().getActiveScreen();

        TGControl* parent = m_parent;
        if (parent)
        {
            if(value)
            {
                ascreen->m_exclusiveChild = this;
            }
            else
            {
                if(ascreen->m_exclusiveChild == this)
                    ascreen->m_exclusiveChild = NULL;
            }
        }
    }

    //-----------------------------------------------------------------------
    //                                p u l s e
    //-----------------------------------------------------------------------
    void TGControl::pulse(TGReal timeElapsed)
    {
        if(!isVisible())
            return;

        if (m_performLayout)
        {
            layout();
            m_performLayout = false;
        }

        //
        // pulse the child controls
        //
        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            (*itr)->pulse(timeElapsed);
        }
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
        if(!oldFocus)
            oldFocus = m_parent->getLastChild();

        m_parent->setFocusedChild(this);

        if(oldFocus)
        {
            if(oldFocus->m_parent)
                oldFocus->m_parent->redraw();
            oldFocus->onFocusExit();
        }
        onFocusEnter(this);
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
    void TGControl::setBounds(TGReal fx1, TGReal fy1, TGReal fx2, TGReal fy2)
    {
        int x1,x2,y1,y2;

        TGReal sw,sh;

        redraw();

        if(!m_parent)
        {
            sw = m_renderer->getWidth();
            sh = m_renderer->getHeight();
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
        if (x2 - x1 + 1 < m_minWidth)
            x2 = x1 + m_minWidth - 1;
        if (y2 - y1 + 1 < m_minHeight)
            y2 = y1 + m_minHeight - 1;
        if (x2 - x1 + 1 > m_maxWidth)
            x2 = x1 + m_maxWidth - 1;
        if (y2 - y1 + 1 > m_maxHeight)
            y2 = y1 + m_maxHeight - 1;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        if (x2 - x1 != oldW || y2 - y1 != oldH)
        {
            m_performLayout = true;
            fireEvent(TGEvent::Resized,TGEventArgs(this));
        }
        if (x1 != oldX1 || y1 != oldY1)
            fireEvent(TGEvent::Moved,TGEventArgs(this));
    }

    //-----------------------------------------------------------------------
    //                          s e t B o u n d s
    //-----------------------------------------------------------------------
    void TGControl::setBounds(int x1, int y1, int x2, int y2)
    {
        redraw();
        int	oldX1 = this->x1;
        int	oldY1 = this->y1;
        int	oldW = this->x2 - this->x1;
        int	oldH = this->y2 - this->y1;
        if (x2 - x1 + 1 < m_minWidth)
            x2 = x1 + m_minWidth - 1;
        if (y2 - y1 + 1 < m_minHeight)
            y2 = y1 + m_minHeight - 1;
        if (x2 - x1 + 1 > m_maxWidth)
            x2 = x1 + m_maxWidth - 1;
        if (y2 - y1 + 1 > m_maxHeight)
            y2 = y1 + m_maxHeight - 1;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        if (x2 - x1 != oldW || y2 - y1 != oldH)
        {
            m_performLayout = true;
            fireEvent(TGEvent::Resized,TGEventArgs(this));
        }
        if (x1 != oldX1 || y1 != oldY1)
            fireEvent(TGEvent::Moved,TGEventArgs(this));
    }

    //-----------------------------------------------------------------------
    //                              s e t P o s
    //-----------------------------------------------------------------------
    void TGControl::setPos(int x1, int y1)
    {
        moveRel(x1,y1);
    }

    //-----------------------------------------------------------------------
    //                              s e t P o s
    //-----------------------------------------------------------------------
    void TGControl::setPos(TGReal x1, TGReal y1)
    {
        moveRel(x1,y1);

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
    void TGControl::getPos(TGReal &x1, TGReal &y1)
    {
    }

    //-----------------------------------------------------------------------
    //                             m o v e R e l
    //-----------------------------------------------------------------------
    void TGControl::moveRel(int x, int y)
    {
        
        int	w = x2 - x1, h = y2 - y1;
        setBounds(x, y, x + w, y + h);
    }

    //-----------------------------------------------------------------------
    //                             m o v e R e l
    //-----------------------------------------------------------------------
    void TGControl::moveRel(TGReal x, TGReal y)
    {
        TGReal sw,sh;

        if(!m_parent)
        {
            sw = m_renderer->getWidth();
            sh = m_renderer->getHeight();
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
        moveRel(nx1,ny1);
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
            moveRel(pw/2 - w/2, y1);
        if (vertical)
            moveRel(x1, ph/2 - h/2);
    }

    //-----------------------------------------------------------------------
    //                           t r a n s l a t e
    //-----------------------------------------------------------------------
    void TGControl::translate(int &x, int &y)
    {
        for (TGControl *parent = m_parent;parent;parent=parent->m_parent)
        {
            x += parent->x1 + parent->m_padLeft;
            y += parent->y1 + parent->m_padTop;
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
    void TGControl::getBounds(TGReal &x1, TGReal &y1, TGReal &x2, TGReal &y2)
    {
        int ix1,iy1,ix2,iy2;
        getBounds(ix1,iy1,ix2,iy2);
        TGReal sw = m_renderer->getWidth();
        TGReal sh = m_renderer->getHeight();

        x1 = (TGReal)ix1 / sw;
        x2 = (TGReal)ix2 / sw;
        y1 = (TGReal)iy1 / sh;
        y2 = (TGReal)iy2 / sh;
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
    void TGControl::setWidth(TGReal width)
    {
        int w,nw;
        if(!m_parent)
        {
            w = m_renderer->getWidth();
        }
        else m_parent->getWidth(w);
        nw = (TGReal)w * width;
        setWidth(nw);
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
    void TGControl::getWidth(TGReal &width)
    {
        TGReal fx1,fx2,fy1,fy2;
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
    void TGControl::setHeight(TGReal height)
    {
        int h,nh;
        if(!m_parent)
        {
            h = m_renderer->getHeight();
        }
        else m_parent->getHeight(h);
        nh = (TGReal)h * height;
        setHeight(nh);
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
    void TGControl::getHeight(TGReal &height)
    {
        TGReal fx1,fx2,fy1,fy2;
        getBounds(fx1,fy1,fx2,fy2);
        height = fy2-fy1;
    }



    //-----------------------------------------------------------------------
    //                           s e t P a d d i n g
    //-----------------------------------------------------------------------
    void TGControl::setPadding(int left, int top, int right, int bottom)
    {
        if (left != -1)
            m_padLeft = left;
        if (top != -1)
            m_padTop = top;
        if (right != -1)
            m_padRight = right;
        if (bottom != -1)
            m_padBottom = bottom;
        redraw();
    }

    //-----------------------------------------------------------------------
    //                         g e t C l i e n t S i z e
    //-----------------------------------------------------------------------
    void TGControl::getClientSize(int &w, int &h)
    {
        w = x2 - x1 - m_padLeft - m_padRight + 1;
        h = y2 - y1 - m_padTop - m_padBottom + 1;
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
        drawRect(x1 + 3, y1 + 3, x2 - 3, y2 - 3,m_theme.getFrameSelectedBrush());
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E n t e r
    //-----------------------------------------------------------------------
    void TGControl::onMouseEnter()
    {
        m_mouseOverControl = true;
    }

    //-----------------------------------------------------------------------
    //                          o n M o u s e E x i t
    //-----------------------------------------------------------------------
    void TGControl::onMouseExit(int x, int y)
    {
        m_mouseOverControl = false;
    }

    //-----------------------------------------------------------------------
    //                         o n M o u s e M o v e d
    //-----------------------------------------------------------------------
    void TGControl::onMouseMoved(int x, int y)
    {
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
    //                            d r a w R e c t
    //-----------------------------------------------------------------------
    void TGControl::drawRect(int x1, int y1, int x2, int y2,TGSBrush brush, int thickness)
    {
        if(!m_isVisible)
            return;

        drawLine(x1-1,y1,x2,y1,brush,thickness);
        drawLine(x2,y1,x2,y2,brush,thickness);
        drawLine(x1,y2,x2,y2,brush,thickness);
        drawLine(x1,y1,x1,y2,brush,thickness);
    }

    //-----------------------------------------------------------------------
    //                            f i l l R e c t
    //-----------------------------------------------------------------------
    void TGControl::fillRect(int x1, int y1, int x2, int y2, TGSBrush brush)
    {
        if(!m_isVisible)
            return;
        TGRect r(x1,y1,x2,y2);
        TGQuadInfo qi = m_renderer->addQuad(r,0,brush);
        m_systemCache.push_back(qi);
        m_quadCache.push_back(qi);
    }


    //-----------------------------------------------------------------------
    //                            d r a w L i n e
    //-----------------------------------------------------------------------
    void TGControl::drawLine(int x1, int y1, int x2, int y2,TGSBrush brush, int thickness)
    {
        if(!m_isVisible)
            return;
        TGRect r(x1,y1,x2,y2);
        TGQuadInfo qi = m_renderer->addLine(r,0,brush,thickness);
        m_systemCache.push_back(qi);
        m_quadCache.push_back(qi);
    }

    //-----------------------------------------------------------------------
    //                             d r a w T r i
    //-----------------------------------------------------------------------
    void TGControl::drawTri(int x1, int y1, int x2, int y2,TGSBrush brush, int pointDir)
    {
        if(!m_isVisible)
            return;

        TGRect r(x1,y1,x2,y2);
        TGQuadInfo qi = m_renderer->addTri(r,0,brush,pointDir);
        m_systemCache.push_back(qi);
        m_quadCache.push_back(qi);
    }

    //-----------------------------------------------------------------------
    //                            d r a w F r a m e
    //-----------------------------------------------------------------------
    void TGControl::drawFrame(int x1, int y1, int x2, int y2, TGFrameStyle s,int thickness)
    {
        if(!m_isVisible)
            return;

        TGSBrush brush;

        brush = m_theme.getBaseOpaque();
        fillRect(x1, y1, x2, y2, brush);
        if (!s)
        {
            return;
        }
        switch (s)
        {
        case FS_FLAT:
            brush = m_theme.getFrameBrush();
            drawRect(x1, y1, x2, y2, brush );
            break;
        case FS_RAISED:
            brush = m_theme.getFrameFocusedBrush();
            drawRect(x1, y1, x2, y2, brush);
            break;
        case FS_LOWERED:            
            brush = m_theme.getFrameSelectedBrush();
            drawRect(x1, y1, x2, y2, brush);
            break;
        default:
            break;
        }
    }

    //-----------------------------------------------------------------------
    //                           d r a w S t r i n g
    //-----------------------------------------------------------------------
    void TGControl::drawString(int x, int y, TGString str, TGSBrush brush, int length)
    {
        if(!m_isVisible)
            return;
        TGFont* font = m_font;
        if(!font)
            return;

        int cHeight=font->getHeight();
        

        TGReal	cx = x;
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

            Ogre::Font::CodePoint cp = ch;
            const Ogre::Font::UVRect uvr = font->m_font->getGlyphTexCoords(cp);
            brush->m_uv.d_left = uvr.left;
            brush->m_uv.d_top = uvr.top;
            brush->m_uv.d_right = uvr.right;
            brush->m_uv.d_bottom = uvr.bottom;
            

            TGQuadInfo qi = m_renderer->addQuad(r,0,brush);
            m_systemCache.push_back(qi);
            m_quadCache.push_back(qi);

            cx += cWidth + 1.0f;
        }
    }



    //-----------------------------------------------------------------------
    //                          s t r i n g W i d t h
    //-----------------------------------------------------------------------
    int TGControl::stringWidth(TGString str, size_t length)
    {
        TGFont* font = m_font;
        if(!font)
            return 0;
        TGReal	cx = 0;
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
        m_renderer->resetClipping();

    }

    //-----------------------------------------------------------------------
    //                         o p e n C l i p A r e a
    //-----------------------------------------------------------------------
    void TGControl::openClipArea(int x1, int y1, int x2, int y2)
    {
        m_renderer->openClipArea(x1,y1,x2,y2);

    }

    //-----------------------------------------------------------------------
    //                          c l o s e C l i p A r e a
    //-----------------------------------------------------------------------
    void TGControl::closeClipArea()
    {
        m_renderer->closeClipArea();
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
    void TGControl::addEventHandler(TGString eventID, TGEventHandler* handler)
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
    void TGControl::removeEventHandler(TGString eventID, TGEventHandler* handler)
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
            for(size_t i=0; i<itr->second.size(); i++)
            {
                TGEventHandler* eh = itr->second[i];
                delete eh;
            }
            itr->second.clear();
            ++itr;
        }

    }

    //-----------------------------------------------------------------------
    //                          l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TGControl::logMessage(TGString message)
    {
        TGSystem::getSingleton().logMessage(message);
    }

    //-----------------------------------------------------------------------
    //                           s e t T h e m e
    //-----------------------------------------------------------------------
    void TGControl::setTheme(TGTheme theme,bool updateChildren) 
    {
        m_theme = theme;
        if(m_popupMenu)
            m_popupMenu->setTheme(theme,true);

        if(!updateChildren)
            return;

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            (*itr)->setTheme(theme,true);
        }
        redraw();
    }

    //-----------------------------------------------------------------------
    //                           r e P a r e n t
    //-----------------------------------------------------------------------
    void TGControl::reParent(TGControl* newParent)
    {
        if(m_parent)
            m_parent->removeChild(this);
        m_parent = newParent;
        if(m_parent)
            m_parent->addChild(this);
    }

    //-----------------------------------------------------------------------
    //                         f i r e E v e n t
    //-----------------------------------------------------------------------
    bool TGControl::fireEvent(TGString eventID,TGEventArgs& args)
    {
        bool rc=false;

        args.m_eventID = eventID;

        if(m_system->eventHook(args))
            return true;

        TGEventMap::iterator itr;
        itr = m_handlers.find(eventID);

        //
        // map entry?
        //
        if(itr == m_handlers.end())
            return false;

        for(size_t i=0;i<itr->second.size();i++)
        {

            TGEventHandler* eh = itr->second[i];

            rc = (*eh)(args);
            if(rc)
                return true;
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

    //-----------------------------------------------------------------------
    //                      i s R e n d e r C a c h e d
    //-----------------------------------------------------------------------
    bool TGControl::isRenderCached()
    {
        if(!m_isVisible)
            return true;

        if(m_redraw)
        {
            m_quadCache.clear();
            m_redraw = false;
            return false;
        }

        for(size_t i=0; i<m_quadCache.size(); i++)
        {
            m_systemCache.push_back(m_quadCache[i]);
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

        openClipArea(x1 + m_padLeft, y1 + m_padTop, x2 - m_padRight,
            y2 - m_padBottom);

        for (TGControlListItr itr = m_children.begin();itr != m_children.end(); ++itr)
        {
            if (*itr == m_exclusiveChild)
                continue;
            (*itr)->render();
            (*itr)->redraw(false);
        }

        if (m_exclusiveChild)
        {
            TGSBrush brush;
            brush.bind(new TGBrush(TGColour(0, 0, 0, 96)));
            TGControl::fillRect(x1, y1, x2, y2, brush);

            m_exclusiveChild->render();
            m_exclusiveChild->redraw(false);
        }

        closeClipArea();
        m_redraw = false;
    }


}