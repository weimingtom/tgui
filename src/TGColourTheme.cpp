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
    const TGColour TGColourTheme::DefaultText = TGColour(169.f/255.f,175.f/255.f,186.f/255.f,1.0f);

    //-----------------------------------------------------------------------
    //                        T G C o l o u r T h e m e
    //-----------------------------------------------------------------------
    TGColourTheme::TGColourTheme()
    {
        setBase(TGColour(100.f/255.f, 114.f/255.f, 115.f/255.f, 204.f/255.f),
                DefaultText);
    }

    //-----------------------------------------------------------------------
    //                        T G C o l o u r T h e m e
    //-----------------------------------------------------------------------
    TGColourTheme::TGColourTheme(TGColour baseColour, TGColour baseTextColour)
    {
        setBase(baseColour,baseTextColour);
    }

    //-----------------------------------------------------------------------
    //                            o p e r a t o r =
    //-----------------------------------------------------------------------
    TGColourTheme& TGColourTheme::operator= (const TGColourTheme& rhs)
    {
        if ( &rhs != this )
        {
            m_base= rhs.m_base;
            m_baseOpaque= rhs.m_baseOpaque;
            m_caption= rhs.m_caption;
            m_captionFocused= rhs.m_captionFocused;
            m_frame= rhs.m_frame;
            m_frameFocused= rhs.m_frameFocused;
            m_frameSelected= rhs.m_frameSelected;
            m_text= rhs.m_text;
            m_textInverted= rhs.m_textInverted;
            m_textFocused= rhs.m_textFocused;
            m_textHilited= rhs.m_textHilited;
        }
        return *this;
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
        TGColour c = baseColour;
        c.a = 1.f;
        m_base.bind(new TGBrush(baseColour));
        m_baseOpaque.bind(new TGBrush(c));

        c = clamp(baseColour * 1.12f);
        c.a = 245.f/255.f;
        m_caption.bind(new TGBrush(c));
        m_captionFocused = m_caption;

        c = clamp(baseColour * 1.18f);
        c.a = 1.f;
        m_frame.bind(new TGBrush(c));

        c = clamp(baseColour * 1.9f);
        c.a = 1.f;
        m_frameFocused.bind(new TGBrush(c));

        c = clamp(baseColour * 0.8f);
        c.a = 1.f;
        m_frameSelected.bind(new TGBrush(c));

        TGFont* font = TGSystem::getSingleton().getCurrentFont();

        if(font)
        {
            m_text.bind(new TGBrush(baseTextColour,font->m_texture ));

            c = clamp(baseTextColour * 1.9f);
            c.a = baseTextColour.a;
            m_textFocused.bind(new TGBrush(c, font->m_texture));

            c = clamp(baseTextColour * 0.2f);
            c.a = baseTextColour.a;
            m_textInverted.bind(new TGBrush(c, font->m_texture));
        }
        else
        {
            m_text.bind(new TGBrush(baseTextColour));

            c = clamp(baseTextColour * 1.9f);
            c.a = baseTextColour.a;
            m_textFocused.bind(new TGBrush(c));

            c = clamp(baseTextColour * 0.2f);
            c.a = baseTextColour.a;
            m_textInverted.bind(new TGBrush(c));
        }
    }

    //-----------------------------------------------------------------------
    //                            s e t F o n t
    //-----------------------------------------------------------------------
    void TGColourTheme::setFont(TGFont* font)
    {
        m_text->setTexture(font->m_texture);
        m_textFocused->setTexture(font->m_texture);
        m_textInverted->setTexture(font->m_texture);
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
