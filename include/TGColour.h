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
#ifndef __TGCOLOUR_H__
#define __TGCOLOUR_H__

namespace TGUI
{
    #define TGColour Ogre::ColourValue
    class TGColourRect
    {
    public:


        TGColourRect(void);
        TGColourRect(const TGColour& col);
        TGColourRect(const TGColour& top_left, const TGColour& top_right, const TGColour& bottom_left, const TGColour& bottom_right);


        void	setAlpha(TGReal alpha);
        void	setTopAlpha(TGReal alpha);
        void	setBottomAlpha(TGReal alpha);
        void	setLeftAlpha(TGReal alpha);
        void	setRightAlpha(TGReal alpha);

        bool	isMonochromatic() const;
        TGColourRect getSubRectangle( TGReal left, TGReal right, TGReal top, TGReal bottom ) const;
        TGColour getColourAtPoint( TGReal x, TGReal y ) const;
        void	setColours(const TGColour& col);
        void	modulateAlpha(TGReal alpha);
        TGColourRect& operator*=(const TGColourRect& other);

        TGColour	m_topLeft, m_topRight, m_bottomLeft, m_bottomRight;		//<! ColourRect component colours
    };


} 


#endif	
