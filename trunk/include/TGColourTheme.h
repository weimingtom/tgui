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
#ifndef __TGCOLOURTHEME_H__
#define __TGCOLOURTHEME_H__

namespace TGUI
{

    class TGColourTheme
    {
        TGColour        m_base;
        TGColour        m_baseOpaque;
        TGColour        m_caption;
        TGColour        m_captionFocused;
        TGColour        m_frame;
        TGColour        m_frameFocused;
        TGColour        m_frameSelected;
        TGColour        m_text;
        TGColour        m_textInverted;
        TGColour        m_textFocused;
        TGColour        m_textHilited;

    public:
        static const TGColour DefaultText;


        TGColourTheme();
        TGColourTheme(TGColour baseColour, TGColour baseTextColour=DefaultText);
        virtual ~TGColourTheme();
        TGColour clamp(TGColour c);

        inline const TGColour getBase() {return m_base;};
        inline const TGColour getBaseOpaque() {return m_baseOpaque;};
        inline const TGColour getTextColour() {return m_text;};
        inline const TGColour getTextFocusedColour() {return m_textFocused;};
        inline const TGColour getTextInvertedColour() {return m_textInverted;};
        inline const TGColour getCaptionColour() {return m_caption;};
        inline const TGColour getFrameColour() {return m_frame;};
        inline const TGColour getFrameFocusedColour() {return m_frameFocused;};
        inline const TGColour getFrameSelectedColour() {return m_frameSelected;};
        void setBase(TGColour baseColour, TGColour baseTextColour);

    };
}

#endif