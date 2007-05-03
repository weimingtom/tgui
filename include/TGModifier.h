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
#ifndef __TGMODIFIER_H__
#define __TGMODIFIER_H__

namespace TGUI
{
    class TGControl;

    class _TGUIExport TGModifier
    {
    protected:
        bool            m_running;
        TGControl*      m_control;
        float           m_duration;

    public:
        enum {
            MOD_CONTINUE   = 0, 
            MOD_DELETE     = -1,
            MOD_DELAY      = -2,        
        };


        TGModifier(TGControl* target);
        virtual ~TGModifier(){};

        void step(TGReal delta)=0;

        void start();
        void pause();
        void resume();
        void stop();
        bool isRunning() {return m_running;}
        float getDuration() {return m_duration;}

    };

    typedef std::vector<TGModifier *> TGModList;
    typedef std::vector<TGModifier *>::iterator TGModListItr;

    typedef Ogre::SharedPtr<TGModifier> TGSModifier;

} 


#endif	
