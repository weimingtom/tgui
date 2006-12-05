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
#ifndef __TGCHECKBOX_H__
#define __TGCHECKBOX_H__

namespace TGUI
{

    class TGCheckbox : public TGControl
    {
        string			m_caption;
        bool			m_hover;
        bool			m_pushed;
        TGDataManager<bool>	m_checked;

    public:
        TGCheckbox(TGControl *parent,string caption="", int x1=0, int y1=0, int x2=5, int y2=5);
        virtual ~TGCheckbox();

        virtual void setCaption(string newCaption);

        virtual void render();
        virtual string getControlType() {return "TGCheckbox";};

        virtual void setState(bool checked);

        virtual void onMouseDown(int x, int y, int b);
        virtual void onMouseUp(int x, int y, int b);
        virtual void onMouseEnter();
        virtual void onMouseExit();
    };
}
#endif
