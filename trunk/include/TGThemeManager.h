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
#ifndef __TGTHEMEMANAGER_H__
#define __TGTHEMEMANAGER_H__
namespace TGUI
{


    class _TGUIExport TGThemeManager : public TGWindow
    {
    protected:
        TGSlider*           m_red;
        TGSlider*           m_green;
        TGSlider*           m_blue;
        TGSlider*           m_alpha;
        TGCheckBox*         m_activeOnly;
        TGControl*          m_lastControl;
    protected:
        bool colourModified(const TGEventArgs& args);

    public:
        TGThemeManager();
        virtual ~TGThemeManager();
        virtual void onFocusEnter(TGControl* oldFocus);
        virtual TGString getControlType() {return "TGThemeManager";};
    };
}
#endif
