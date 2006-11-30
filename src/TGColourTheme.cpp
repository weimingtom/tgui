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
    TGColourTheme::TGColourTheme()
    {
        setBase(TGColour(100.f/255.f, 114.f/255.f, 115.f/255.f, 204.f/255.f),
                TGColour(0.9f,0.9f,0.9f,1.0f));
    }

    //-----------------------------------------------------------------------
    //                        T G C o l o u r T h e m e
    //-----------------------------------------------------------------------
    TGColourTheme::TGColourTheme(TGColour baseColour, TGColour baseTextColour)
    {
        setBase(baseColour,baseTextColour);

    }

    //-----------------------------------------------------------------------
    //                       ~ T G C o l o u r T h e m e
    //-----------------------------------------------------------------------
    TGColourTheme::~TGColourTheme()
    {
    }

    //-----------------------------------------------------------------------
    //                            s e t B a s e
    //-----------------------------------------------------------------------
    void TGColourTheme::setBase(TGColour baseColour, TGColour baseTextColour)
    {
        m_base = baseColour;
        m_caption = clamp(m_base * 1.12f);
        m_caption.a = 245.f/255.f;
        m_frame = clamp(m_base * 1.18f);
        m_frame.a = 1.f;
        m_frameFocused = clamp(m_base * 1.9f);
        m_frameFocused.a = 1.f;
        m_text = baseTextColour;
    }

    //-----------------------------------------------------------------------
    //                            s e t B a s e
    //-----------------------------------------------------------------------
    TGColour TGColourTheme::clamp(TGColour c)
    {
        TGColour clamped=c;

        if(clamped.r < 0.0f)
            clamped.r = 0.0f;
        if(clamped.r > 1.0f)
            clamped.r = 1.0f;
        if(clamped.g < 0.0f)
            clamped.g = 0.0f;
        if(clamped.g > 1.0f)
            clamped.g = 1.0f;
        if(clamped.b < 0.0f)
            clamped.b = 0.0f;
        if(clamped.b > 1.0f)
            clamped.b = 1.0f;
        if(clamped.a < 0.0f)
            clamped.a = 0.0f;
        if(clamped.a > 1.0f)
            clamped.a = 1.0f;

        return clamped;
    }

} 
