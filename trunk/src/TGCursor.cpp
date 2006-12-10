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
#include "tgui.h"


namespace TGUI
{
    //-----------------------------------------------------------------------
    //                           T G C u r s o r
    //-----------------------------------------------------------------------
    TGCursor::TGCursor(string fname,string resourceGroup) : TGImage(NULL,0,0,fname,resourceGroup)
    {

    }

    //-----------------------------------------------------------------------
    //                           T G C u r s o r
    //-----------------------------------------------------------------------
    TGCursor::TGCursor(TGTexture* texture) : TGImage(NULL,0,0,texture)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T G C u r s o r
    //-----------------------------------------------------------------------
    TGCursor::~TGCursor()
    {
    }

    //-----------------------------------------------------------------------
    //                               m o v e
    //-----------------------------------------------------------------------
    void TGCursor::move(int x, int y)
    {
        //
        // check screen bounds
        //
        int maxWidth = getRenderer()->getWidth();
        int maxHeight = getRenderer()->getHeight();

        if(x < 0)
            x = 0;
        else if(x > maxWidth)
            x = maxWidth;

        if(y < 0)
            y = 0;
        else if(y > maxHeight)
            y = maxHeight;
       

        TGImage::moveRel(x,y);
    }

   //-----------------------------------------------------------------------
   //                               d r a w
   //-----------------------------------------------------------------------
   void TGCursor::draw()
    {
        TGRect r(x1,y1,x2,y2);
        TGRect ruv(0.f,0.f,1.f,1.f);
        TGColourRect cr(gColor);
        getRenderer()->renderQuadDirect(r,0,texture,ruv,cr);
    }


}