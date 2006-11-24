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
#ifndef __TGLISTBOX_H__
#define __TGLISTBOX_H__

namespace TGUI
{

    class TGListbox;

    class TGListboxItem : public TGControl
    {
        TGListbox*              box;
        string                  text;

    public:
        unsigned int            minimumWidth;
        unsigned int            itemHeight;
        void                    *data;
        size_t                  index;

    public:
        TGListboxItem(TGControl *parent);
        virtual ~TGListboxItem();

        virtual void setText(string newText);
        virtual string getText() {return text;};
        size_t  getIndex() {return index;};

        virtual void render();
        virtual void focus();
    };

    class TGListbox : public TGScrollbox
    {
    public:
        TGListboxItem*          active;

    public:
        TGListbox(TGControl *parent, int x1, int y1, int x2, int y2);
        virtual ~TGListbox();

        virtual void addItem(string text);
        virtual void addItem(TGListboxItem *item);
        virtual TGListboxItem *findItem(string text);
        virtual TGListboxItem *getItem(unsigned int index);
        virtual void removeItem(TGListboxItem *item);
        virtual void selectItem(unsigned int index);
        virtual void selectItem(TGListboxItem *item);

        virtual void layout();
    };
}
#endif
