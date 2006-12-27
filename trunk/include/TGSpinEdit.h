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
#ifndef __TGSPINEDIT_H__
#define __TGSPINEDIT_H__

namespace TGUI
{

    class TGSpinEdit : public TGControl
    {
    private:
        TGReal          m_value;
        TGReal          m_minValue;
        TGReal          m_maxValue;
        TGReal          m_increment;
        TGReal          m_pulseTime;

        int             m_decimals;

        int             m_height;
        bool            m_upPressed;
        bool            m_downPressed;
        TGEditbox*      m_inputbox;

    public:

        TGSpinEdit(TGControl *parent, int x1=0, int y1=0, int x2=5, int y2=5);
        virtual ~TGSpinEdit();

        virtual void render();
        virtual TGString getControlType() {return "TGSpinEdit";};
        virtual void setBounds(int x1, int y1, int x2, int y2);
        virtual TGControl *childAt(TGReal x, TGReal y);
        virtual bool pointInControl(TGReal x, TGReal y);
        virtual void setTheme(TGTheme theme,bool updateChildren=false);
        virtual void onFocusExit();

        virtual void setMaximumValue(TGReal value) {m_maxValue = value;};
        virtual void setMinimumValue(TGReal value) {m_minValue = value;};
        virtual void setCurrentValue(TGReal value) {m_value = value;};


        virtual bool focused();
        virtual void pulse(TGReal timeElapsed);
        void updateValue();

        virtual void onMouseDown(int x, int y, int b);
        virtual void onMouseUp(int x, int y, int b);

        virtual void onMouseMoved(int x, int y);
        virtual void onMouseEnter();
        virtual void onMouseExit(int x, int y);

    };
}
#endif
