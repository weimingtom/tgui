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
#include "tgui.h"

namespace TGUI
{
    //-----------------------------------------------------------------------
    //                        T G C o l o u r R e c t
    //-----------------------------------------------------------------------
    TGColourRect::TGColourRect(const TGColour& top_left, const TGColour& top_right, 
        const TGColour& bottom_left, const TGColour& bottom_right)
    {
        m_topLeft = top_left;
        m_topRight = top_right;
        m_bottomLeft = bottom_left;
        m_bottomRight = bottom_right;
    }

    //-----------------------------------------------------------------------
    //                        T G C o l o u r R e c t
    //-----------------------------------------------------------------------
    TGColourRect::TGColourRect(const TGColour& col) 
    {
        m_topLeft = col;
        m_topRight = col;
        m_bottomLeft = col;
        m_bottomRight = col;
    }

    //-----------------------------------------------------------------------
    //                        T G C o l o u r R e c t
    //-----------------------------------------------------------------------
    TGColourRect::TGColourRect(void) 
    {
        m_topLeft = TGColour();
        m_topRight = TGColour();
        m_bottomLeft = TGColour();
        m_bottomRight = TGColour();
    }

    //-----------------------------------------------------------------------
    //                           s e t A l p h a
    //-----------------------------------------------------------------------
    void TGColourRect::setAlpha(TGReal alpha)
    {
        m_topLeft.a = alpha;
        m_topRight.a = alpha;
        m_bottomLeft.a = alpha;
        m_bottomRight.a = alpha;
    }

    //-----------------------------------------------------------------------
    //                        s e t T o p A l p h a
    //-----------------------------------------------------------------------
    void TGColourRect::setTopAlpha(TGReal alpha)
    {
        m_topLeft.a = alpha;
        m_topRight.a = alpha;
    }

    //-----------------------------------------------------------------------
    //                     s e t B o t t o m p A l p h a
    //-----------------------------------------------------------------------
    void TGColourRect::setBottomAlpha(TGReal alpha)
    {
        m_bottomLeft.a = alpha;
        m_bottomRight.a = alpha;
    }

    //-----------------------------------------------------------------------
    //                        s e t L e f t p A l p h a
    //-----------------------------------------------------------------------
    void TGColourRect::setLeftAlpha(TGReal alpha)
    {
        m_topLeft.a = alpha;
        m_bottomLeft.a = alpha;
    }

    //-----------------------------------------------------------------------
    //                        s e t R i g h t A l p h a
    //-----------------------------------------------------------------------
    void TGColourRect::setRightAlpha(TGReal alpha)
    {
        m_topRight.a = alpha;
        m_bottomRight.a = alpha;
    }

    //-----------------------------------------------------------------------
    //                      i s M o n o c h r o m a t i c
    //-----------------------------------------------------------------------
    bool TGColourRect::isMonochromatic() const
    {
        return m_topLeft == m_topRight &&
            m_topLeft == m_bottomLeft &&
            m_topLeft == m_bottomRight;
    }

    //-----------------------------------------------------------------------
    //                    g e t C o l o u r A t P o i n t
    //-----------------------------------------------------------------------
    TGColour TGColourRect::getColourAtPoint( TGReal x, TGReal y ) const
    {
        TGColour h1((m_topRight - m_topLeft) * x + m_topLeft);
        TGColour h2((m_bottomRight - m_bottomLeft) * x + m_bottomLeft);
        return TGColour((h2 - h1) * y + h1);
    }

    //-----------------------------------------------------------------------
    //                      g e t S u b R e c t a n g l e
    //-----------------------------------------------------------------------
    TGColourRect TGColourRect::getSubRectangle( TGReal left, TGReal right, TGReal top, TGReal bottom ) const
    {
        return TGColourRect(
            getColourAtPoint(left, top),
            getColourAtPoint(right, top),
            getColourAtPoint(left, bottom),
            getColourAtPoint(right, bottom)
            );
    }

    //-----------------------------------------------------------------------
    //                         s e t C o l o u r s
    //-----------------------------------------------------------------------
    void TGColourRect::setColours(const TGColour& col)
    {
        m_topLeft = m_topRight = m_bottomLeft = m_bottomRight = col;
    }

    //-----------------------------------------------------------------------
    //                      m o d u l a t e A l p h a 
    //-----------------------------------------------------------------------
    void TGColourRect::modulateAlpha(TGReal alpha)
    {
        m_topLeft.a = (m_topLeft.a*alpha);
        m_topRight.a = (m_topRight.a*alpha);
        m_bottomLeft.a = (m_bottomLeft.a*alpha);
        m_bottomRight.a = (m_bottomRight.a*alpha);
    }

    //-----------------------------------------------------------------------
    //                        o p e r a t o r *=
    //-----------------------------------------------------------------------
    TGColourRect& TGColourRect::operator *=(const TGColourRect& other)
    {
        /*
        m_topLeft *= other.m_topLeft;
        m_topRight *= other.m_topRight;
        m_bottomLeft *= other.m_bottomLeft;
        m_bottomRight *= other.m_bottomRight;
        */

        return *this;
    }

} 
