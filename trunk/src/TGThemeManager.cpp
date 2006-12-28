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
#include <tgui.h>
namespace TGUI
{

    //-----------------------------------------------------------------------
    //                         T G T h e m e M a n a g e r
    //-----------------------------------------------------------------------
    TGThemeManager::TGThemeManager() : TGWindow(getActiveScreen(),"Theme Manager")
    {
        m_isTabbedCaption = true;
        setBounds(0.1f,0.1f,0.55f,0.5f);
        TGLabel* l;
        l = new TGLabel(this,"","Red");
        l->setPos(0.1f,0.1f);
        l = new TGLabel(this,"","Green");
        l->setPos(0.1f,0.2f);
        l = new TGLabel(this,"","Blue");
        l->setPos(0.1f,0.3f);
        l = new TGLabel(this,"","Alpha");
        l->setPos(0.1f,0.4f);

        m_red = new TGSlider(this);
        m_red->setBounds(0.3f,0.1f,0.85f,0.18f);
        m_red->setMax(255);
        m_red->setValue(100);
        m_red->addEventHandler(TGEvent::Modified, new TGEventHandler(&TGThemeManager::colourModified,this));

        m_green = new TGSlider(this);
        m_green->setBounds(0.3f,0.2f,0.85f,0.28f);
        m_green->setMax(255);
        m_green->setValue(114);
        m_green->addEventHandler(TGEvent::Modified, new TGEventHandler(&TGThemeManager::colourModified,this));

        m_blue = new TGSlider(this);
        m_blue->setBounds(0.3f,0.3f,0.85f,0.38f);
        m_blue->setMax(255);
        m_blue->setValue(115);
        m_blue->addEventHandler(TGEvent::Modified, new TGEventHandler(&TGThemeManager::colourModified,this));

        m_alpha = new TGSlider(this);
        m_alpha->setBounds(0.3f,0.4f,0.85f,0.48f);
        m_alpha->setMax(255);
        m_alpha->setValue(204);
        m_alpha->addEventHandler(TGEvent::Modified, new TGEventHandler(&TGThemeManager::colourModified,this));

        m_activeOnly = new TGCheckBox(this,"Modify Active Only");
        m_activeOnly->setBounds(0.3f,0.5f,0.85f,0.59f);
    }

    //-----------------------------------------------------------------------
    //                        ~ T G T h e m e M a n a g e r
    //-----------------------------------------------------------------------
    TGThemeManager::~TGThemeManager()
    {
    }

    //-----------------------------------------------------------------------
    //                         c o l o u r M o d i f i e d
    //-----------------------------------------------------------------------
    bool TGThemeManager::colourModified(const TGEventArgs& args)
    {
        TGReal r,g,b,a;
        r = (TGReal)m_red->value.get() / 255.f;
        g = (TGReal)m_green->value.get() / 255.f;
        b = (TGReal)m_blue->value.get() / 255.f;
        a = (TGReal)m_alpha->value.get() / 255.f;

        TGTheme ct(TGColour(r,g,b,a));

        getActiveScreen()->setTheme(ct,true);

        return true;
    }

    //-----------------------------------------------------------------------
    //                         o n F o c u s E n t e r
    //-----------------------------------------------------------------------
    void TGThemeManager::onFocusEnter(TGControl* oldFocus)
    {
        TGControl::onFocusEnter(oldFocus);
        m_lastControl = oldFocus;
    
    }



}