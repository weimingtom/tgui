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
#ifndef __TGDATAMAN_H__
#define __TGDATAMAN_H__
namespace TGUI
{


    template <class TGData> class TGDataManager
    {
        TGData	data;
        TGData	*dataSource;
        TGControl	*control;

    public:

        TGAction	*modified;
        TGAction	*requested;

        TGDataManager()
        {
            control = NULL;
            dataSource = &data;
            modified = requested = NULL;
        }
        ~TGDataManager()
        {
            BSGUI_FREEACTION(modified);
            BSGUI_FREEACTION(requested);
        }

        void setControl(TGControl *control)
        {
            this->control = control;
        }

        void setDataSource(TGData *place)
        {
            if (place)
                dataSource = (TGData*)place;
            else
                dataSource = &data;
        }

        void set(TGData newData)
        {
            *dataSource = newData;
            BSGUI_RUNACTION_OF(control, modified);
        }

        TGData get()
        {
            BSGUI_RUNACTION_OF(control, requested);
            return *dataSource;
        }
    };
}
#endif
