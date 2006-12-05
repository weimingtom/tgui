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
#ifndef __TGIMAGE_H__
#define __TGIMAGE_H__

namespace TGUI
{

    class TGImage : public TGControl
    {
        int         m_width;
        int         m_height;

    public:
        TGTexture*	texture;


    public:
        TGImage(TGControl *parent, int x, int y, string fname,string resourceGroup="");
        TGImage(TGControl *parent, int x, int y, TGTexture* texture);
        virtual ~TGImage();

        virtual void setTexture(TGTexture *newTexture, bool resize=true);
        virtual void setTexture(string fname, string resourceGroop="", bool resize=true);

        int getWidth() {return m_width;};
        int getHeight() {return m_height;};

        virtual void render();
        virtual string getControlType() {return "TGImage";};
    };
}
#endif
