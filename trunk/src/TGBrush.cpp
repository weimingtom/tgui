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
    //                             T G B r u s h
    //-----------------------------------------------------------------------
    TGBrush::TGBrush()
    {
        m_colourRect = TGColourRect(TGColour(1.0,1.0,1.0,1.0));
        m_texture.bind(TGSystem::getSingleton().getDefaultTexture());
    }

    //-----------------------------------------------------------------------
    //                             T G B r u s h
    //-----------------------------------------------------------------------
    TGBrush::TGBrush(TGSTexture texture)
    {
        m_texture = texture;
    }

    //-----------------------------------------------------------------------
    //                             T G B r u s h
    //-----------------------------------------------------------------------
    TGBrush::TGBrush(const TGColour& col, TGSTexture texture)
    {
        m_colourRect = TGColourRect(col);
        if(texture.isNull())
            m_texture.bind(TGSystem::getSingleton().getDefaultTexture());
    }

    //-----------------------------------------------------------------------
    //                             T G B r u s h
    //-----------------------------------------------------------------------
    TGBrush::TGBrush(const TGColourRect& colRect, TGSTexture texture)
    {
        m_colourRect = colRect;
        if(texture.isNull())
            m_texture.bind(TGSystem::getSingleton().getDefaultTexture());
    }

    //-----------------------------------------------------------------------
    //                            ~ T G B r u s h
    //-----------------------------------------------------------------------
    TGBrush::~TGBrush()
    {
    }

    //-----------------------------------------------------------------------
    //                           s e t C o l o u r
    //-----------------------------------------------------------------------
    void TGBrush::setColour(const TGColour& col)
    {
        m_colourRect = TGColourRect(col);
    }

    //-----------------------------------------------------------------------
    //                           s e t C o l o u r
    //-----------------------------------------------------------------------
    void TGBrush::setColour(const TGColourRect& colRect)
    {
        m_colourRect = colRect;
    }

    //-----------------------------------------------------------------------
    //                           s e t T e x t u r e
    //-----------------------------------------------------------------------
    void TGBrush::setTexture(const TGSTexture texture)
    {
        m_texture = texture;
    }


}