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
#ifndef __TGACTIONS_H__
#define __TGACTIONS_H__

namespace TGUI
{
    class TGControl;

    class TGEvent
    {
    public:
        static const string Resized;
        static const string Moved;
        static const string Scrolled;
        static const string Modified;
        static const string Selected;

        static const string MouseEnter;
        static const string MouseLeave;
        static const string MouseDown;
        static const string MouseUp;
        static const string MouseMove;
        static const string MouseClicked;

        static const string MenuPopup;
    };

    class TGEventArgs
    {
    public:
        TGEventArgs(TGControl* control) : m_control(control) {}
        virtual ~TGEventArgs(void) {}
        TGControl*      m_control;
        string          m_eventID;
    };

    class TGMouseEventArgs : public TGEventArgs
    {
    public:
        TGMouseEventArgs(TGControl* control) : TGEventArgs(control) {}

    };

    class TGFunctor
    {
    public:
        virtual ~TGFunctor() {};
        virtual bool operator()(const TGEventArgs& args) = 0;
    };

    template<typename T>
    class TGMemberFunction : public TGFunctor
    {
    public:
        //! Member function slot type.
        typedef bool(T::*TGMemberFunctionType)(const TGEventArgs&);

        TGMemberFunction(TGMemberFunctionType func, T* obj) :
        m_function(func),
            m_object(obj)
        {}

        virtual bool operator()(const TGEventArgs& args)
        {
            return (m_object->*m_function)(args);
        }

    private:
        TGMemberFunctionType m_function;
        T*                   m_object;
    };



    class TGEventHandler
    {
    public:

        template<typename T>
        TGEventHandler(bool (T::*function)(const TGEventArgs&), T* obj) :
            m_functor(new TGMemberFunction<T>(function, obj))
        {};

            virtual ~TGEventHandler() {delete m_functor;};

        virtual bool operator()(const TGEventArgs& args)
        {
            return (*m_functor)(args);
        }

    private:
        TGFunctor* m_functor;
    };

}
#endif
