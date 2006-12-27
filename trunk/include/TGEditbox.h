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
#ifndef __TGEDITBOX_H__
#define __TGEDITBOX_H__

namespace TGUI
{

    class TGEditbox : public TGControl
    {
        TGDataManager<TGString>	m_text;
        int     		        tScroll;
        size_t     		        m_cursor;
        int     		        m_cursorX;
        TGReal                  m_pulseTime;
        bool                    m_cursorVisible;
        int                     m_lastKey;
        char                    m_lastChar;
        TGReal                  m_repeatRate;
        TGReal                  m_repeatDelay;
        TGReal                  m_repeatElapsed;
        bool                    m_readOnly;

    public:

        TGEditbox(TGControl *parent, int x1=0, int y1=0, int x2=0, int y2=0);
        virtual ~TGEditbox();

        virtual void setText(TGString newText);
        virtual TGString getText();

        virtual void render();
        virtual TGString getControlType() {return "TGEditbox";};

        virtual void pulse(TGReal timeElapsed);

        void setReadOnly(bool value) {m_readOnly = value;};
        bool getReadOnly() {return m_readOnly;};

        virtual void onKeyDown(int key, unsigned char ascii);
        virtual void onKeyUp(int key, unsigned char ascii);
        virtual void onFocusEnter(TGControl* oldFocus);
        virtual void onFocusExit();

    };
}
#endif
