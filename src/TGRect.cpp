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
    //                            T G R e c t
    //-----------------------------------------------------------------------
    TGRect::TGRect(float left, float top, float right, float bottom)
    {
        d_top = top;
        d_bottom = bottom;
        d_left = left;
        d_right = right;
    }

    //-----------------------------------------------------------------------
    //                            T G R e c t
    //-----------------------------------------------------------------------
    TGRect::TGRect(TGPoint pos, TGSize sz)
    {
        d_top = pos.y;
        d_bottom = pos.y + sz.y;
        d_left = pos.x;
        d_right = pos.x + sz.x;
    }


    //-----------------------------------------------------------------------
    //                      g e t I n t e r s e c t i o n
    //-----------------------------------------------------------------------
    TGRect TGRect::getIntersection(const TGRect& rect) const
    {
        // check for total exclusion
        if ((d_right > rect.d_left) &&
            (d_left < rect.d_right) &&
            (d_bottom > rect.d_top) &&
            (d_top < rect.d_bottom))
        {
            TGRect temp;

            // fill in temp with the intersection
            temp.d_left = (d_left > rect.d_left) ? d_left : rect.d_left;
            temp.d_right = (d_right < rect.d_right) ? d_right : rect.d_right;
            temp.d_top = (d_top > rect.d_top) ? d_top : rect.d_top;
            temp.d_bottom = (d_bottom < rect.d_bottom) ? d_bottom : rect.d_bottom;

            return temp;
        }
        else
        {
            return TGRect(0.0f, 0.0f, 0.0f, 0.0f);
        }

    }

    //-----------------------------------------------------------------------
    //                            o f f s e t
    //-----------------------------------------------------------------------
    TGRect& TGRect::offset(const TGPoint& pt)
    {
        d_left		+= pt.x;
        d_right		+= pt.x;
        d_top		+= pt.y;
        d_bottom	+= pt.y;
        return *this;
    }


    //-----------------------------------------------------------------------
    //                       i s P o i n t I n R e c t
    //-----------------------------------------------------------------------
    bool TGRect::isPointInRect(const TGPoint& pt) const
    {
        if ((d_left > pt.x) ||
            (d_right <= pt.x) ||
            (d_top > pt.y) ||
            (d_bottom <= pt.y))
        {
            return false;
        }

        return true;
    }

    //-----------------------------------------------------------------------
    //                          s e t P o s i t i o n
    //-----------------------------------------------------------------------
    void TGRect::setPosition(const TGPoint& pt)
    {
        TGSize sz(getSize());

        d_left = pt.x;
        d_top  = pt.y;
        setSize(sz);
    }


    //-----------------------------------------------------------------------
    //                     c o n s t r a i n S i z e M a x
    //-----------------------------------------------------------------------
    TGRect& TGRect::constrainSizeMax(const TGSize& sz)
    {
        if (getWidth() > sz.x)
        {
            setWidth(sz.x);
        }

        if (getHeight() > sz.y)
        {
            setHeight(sz.y);
        }

        return *this;
    }


    //-----------------------------------------------------------------------
    //                     c o n s t r a i n S i z e M i n
    //-----------------------------------------------------------------------
    TGRect& TGRect::constrainSizeMin(const TGSize& sz)
    {
        if (getWidth() < sz.x)
        {
            setWidth(sz.x);
        }

        if (getHeight() < sz.y)
        {
            setHeight(sz.y);
        }

        return *this;
    }


    //-----------------------------------------------------------------------
    //                       c o n s t r a i n S i z e
    //-----------------------------------------------------------------------
    TGRect& TGRect::constrainSize(const TGSize& max_sz, const TGSize& min_sz)
    {
        TGSize curr_sz(getSize());

        if (curr_sz.x > max_sz.x)
        {
            setWidth(max_sz.x);
        }
        else if (curr_sz.x < min_sz.x)
        {
            setWidth(min_sz.x);
        }

        if (curr_sz.y > max_sz.y)
        {
            setHeight(max_sz.y);
        }
        else if (curr_sz.y < min_sz.y)
        {
            setHeight(min_sz.y);
        }

        return *this;
    }

    //-----------------------------------------------------------------------
    //                          o p e r a t o r =
    //-----------------------------------------------------------------------
    TGRect& TGRect::operator=(const TGRect& rhs)
    {
        d_left = rhs.d_left;
        d_top = rhs.d_top;
        d_right = rhs.d_right;
        d_bottom = rhs.d_bottom;

        return *this;
    }

} 
