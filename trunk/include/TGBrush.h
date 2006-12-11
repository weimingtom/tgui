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
#ifndef __TGBRUSH_H__
#define __TGBRUSH_H__

namespace TGUI
{
    class TGBrush
    {
    public:
        TGColourRect        m_colourRect;
        TGTexture*          m_texture;
    public:


        TGBrush();
        TGBrush(TGTexture* texture);
        TGBrush(const TGColour& col, TGTexture* texture=NULL);
        TGBrush(const TGColourRect& colRect, TGTexture* texture=NULL);


        virtual ~TGBrush();

        void    setColour(const TGColour& col);
        void    setColour(const TGColourRect& colRect);
        void    setTexture(TGTexture* texture);

    };

    typedef Ogre::SharedPtr<TGBrush> TGSBrush;


} 


#endif	
