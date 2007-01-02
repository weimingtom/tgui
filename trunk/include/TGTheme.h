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
#ifndef __TGTHEME_H__
#define __TGTHEME_H__

namespace TGUI
{
    class TGBrush;
    class TGFont;
    typedef Ogre::SharedPtr<TGBrush> TGSBrush;

    class _TGUIExport  TGTheme
    {
    public:
        TGSBrush        m_base;
        TGSBrush        m_baseOpaque;
        TGSBrush        m_baseBright;
        TGSBrush        m_caption;
        TGSBrush        m_captionFocused;
        TGSBrush        m_frame;
        TGSBrush        m_frameFocused;
        TGSBrush        m_frameSelected;
        TGSBrush        m_text;
        TGSBrush        m_textInverted;
        TGSBrush        m_textFocused;
        TGSBrush        m_textHilited;

    public:
        static const TGColour DefaultText;


        TGTheme();
        TGTheme(TGColour baseColour, TGColour baseTextColour=DefaultText);
        TGTheme& TGTheme::operator= (const TGTheme& rhs);

        virtual ~TGTheme();
        TGColour clamp(TGColour c);

        inline const TGSBrush getBase() {return m_base;};
        inline const TGSBrush getBaseBright() {return m_baseBright;};
        inline const TGSBrush getBaseOpaque() {return m_baseOpaque;};
        inline const TGSBrush getTextBrush() {return m_text;};
        inline const TGSBrush getTextFocusedBrush() {return m_textFocused;};
        inline const TGSBrush getTextInvertedBrush() {return m_textInverted;};
        inline const TGSBrush getCaptionBrush() {return m_caption;};
        inline const TGSBrush getFrameBrush() {return m_frame;};
        inline const TGSBrush getFrameFocusedBrush() {return m_frameFocused;};
        inline const TGSBrush getFrameSelectedBrush() {return m_frameSelected;};
        void setBase(TGColour baseColour, TGColour baseTextColour);
        void setFont(TGFont* font);

    };
}

#endif