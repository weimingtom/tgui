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
#ifndef __TGLISTBOX_H__
#define __TGLISTBOX_H__

namespace TGUI
{

    class TGListBox;

    class _TGUIExport TGListBoxItem : public TGControl
    {
        TGListBox*              box;
        TGString                text;

    public:
        unsigned int            minimumWidth;
        unsigned int            itemHeight;
        void                    *data;
        size_t                  index;

    public:
        TGListBoxItem(TGControl *parent);
        virtual ~TGListBoxItem();

        virtual void setText(TGString newText);
        virtual TGString getText() {return text;};
        size_t  getIndex() {return index;};

        virtual void render();
        virtual void focus();
    };

    class _TGUIExport TGListBox : public TGScrollBox
    {
        friend class TGListBoxItem;
    protected:
        TGListBoxItem*          m_selectedItem;

    public:
        TGListBox(TGControl *parent, TGString name="");
        virtual ~TGListBox();

        virtual void addItem(TGString text);
        virtual void addItem(TGListBoxItem *item);
        virtual TGListBoxItem *findItem(TGString text);
        virtual TGListBoxItem *getItem(unsigned int index);
        virtual void removeItem(TGListBoxItem *item);
        virtual void selectItem(unsigned int index);
        virtual void selectItem(TGListBoxItem *item);
        virtual size_t getItemCount();

        virtual TGString getControlType() {return "TGListBox";};

        virtual TGListBoxItem* getSelectedItem() {return m_selectedItem;};

        virtual void layout();
    };
}
#endif
