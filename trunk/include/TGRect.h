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
#ifndef __TGRECT_H__
#define __TGRECT_H__

namespace TGUI
{
    class TGRect
    {
    public:
        TGRect(void) {}


        TGRect(TGReal left, TGReal top, TGReal right, TGReal bottom);

        TGRect(TGPoint pos, TGSize sz);

        TGPoint	getPosition(void) const		{return TGPoint(d_left, d_top);}

        TGReal	getWidth(void) const		{return d_right - d_left;}

        TGReal	getHeight(void) const		{return d_bottom - d_top;}
        TGSize	getSize(void) const			{return TGSize(getWidth(), getHeight());}

        void	setPosition(const TGPoint& pt);


        void	setWidth(TGReal width)		{d_right = d_left + width;}
        void	setHeight(TGReal height)		{d_bottom = d_top + height;}

        void	setSize(const TGSize& sze)	{setWidth(sze.x); setHeight(sze.y);}

        TGRect	getIntersection(const TGRect& rect) const;

        TGRect&	offset(const TGPoint& pt);

        bool	isPointInRect(const TGPoint& pt) const;

        TGRect&	constrainSizeMax(const TGSize& sz);
        TGRect&	constrainSizeMin(const TGSize& sz);

        TGRect&	constrainSize(const TGSize& max_sz, const TGSize& min_sz);

        bool	operator==(const TGRect& rhs) const
        {
            return ((d_left == rhs.d_left) && (d_right == rhs.d_right) && (d_top == rhs.d_top) && (d_bottom == rhs.d_bottom));
        }

        bool	operator!=(const TGRect& rhs) const		{return !operator==(rhs);}

        TGRect&	operator=(const TGRect& rhs);

        TGRect operator*(TGReal scalar) const      { return TGRect(d_left * scalar, d_top * scalar, d_right * scalar, d_bottom * scalar); }
        const TGRect& operator*=(TGReal scalar)    { d_left *= scalar; d_top *= scalar; d_right *= scalar; d_bottom *= scalar; return *this; }

        TGReal	d_top, d_bottom, d_left, d_right;
    };

}


#endif	
