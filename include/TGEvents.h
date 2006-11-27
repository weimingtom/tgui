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

    class TGEventArgs
    {
    public:
        TGEventArgs(void) : m_handled(false) {}
        virtual ~TGEventArgs(void) {}
        bool	m_handled;		
    };

    class SlotFunctorBase
    {
    public:
        virtual ~SlotFunctorBase() {};
        virtual bool operator()(const TGEventArgs& args) = 0;
    };

    template<typename T>
    class MemberFunctionSlot : public SlotFunctorBase
    {
    public:
        //! Member function slot type.
        typedef bool(T::*MemberFunctionType)(const TGEventArgs&);

        MemberFunctionSlot(MemberFunctionType func, T* obj) :
        d_function(func),
            d_object(obj)
        {}

        virtual bool operator()(const TGEventArgs& args)
        {
            return (d_object->*d_function)(args);
        }

    private:
        MemberFunctionType d_function;
        T* d_object;
    };



    class TGEventHandler
    {
    public:

        template<typename T>
        TGEventHandler(bool (T::*function)(const TGEventArgs&), T* obj) :
            d_functor_impl(new MemberFunctionSlot<T>(function, obj))
        {}

        virtual bool operator()(const TGEventArgs& args)
        {
            return (*d_functor_impl)(args);
        }

    private:
        SlotFunctorBase* d_functor_impl;
    };

    class TGAction
    {
        bool	        m_autoDelete;

    public:
        TGAction();
        virtual ~TGAction();
        bool getAutoDelete() {return m_autoDelete;};            

        virtual void run(TGControl *sender){}
    };

    typedef void    (*TGCallbackActionFunc)(TGControl *sender);

    class TGCallbackAction : public TGAction
    {
        TGCallbackActionFunc      m_func;

    public:

        TGCallbackAction(TGCallbackActionFunc cbFunc);
        virtual void run(TGControl *sender);
        TGCallbackActionFunc getFunc() {return m_func;};
    };

#define BSGUI_FREEACTION(a) { \
    if ((a) && (a)->getAutoDelete()) \
    delete a; }
#define BSGUI_RUNACTION(a) { \
    if (a) (a)->run(this); }
#define BSGUI_RUNACTION_OF(o,a) { \
    if (a) (a)->run(o); }
}
#endif
