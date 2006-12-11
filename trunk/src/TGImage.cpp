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
#include <tgui.h>

#include "bitmaps/new.c"
#include "bitmaps/open.c"
#include "bitmaps/save.c"
#include "bitmaps/saveas.c"
#include "bitmaps/quit.c"
#include "bitmaps/win.c"

namespace TGUI
{
    extern TGColour gColor;

    //-----------------------------------------------------------------------
    //                            T G I m a g e
    //-----------------------------------------------------------------------
    TGImage::TGImage(TGControl *parent, int x, int y, string fname, string resourceGroup)
        : TGControl(parent)
    {
        int	x1 = x, y1 = y, x2, y2;
        m_width = 0;
        m_height = 0;
        if (!fname.empty())
        {
            if(resourceGroup.empty())
            {
                resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME.c_str();
            }
            texture = getRenderer()->createTexture(fname,resourceGroup);
            m_width = texture->getWidth();
            m_height = texture->getHeight();

            x2 = x1 + m_width - 1;
            y2 = y1 + m_height - 1;
        }
        else
        {
            texture = NULL;
            x2 = x1 + 9;
            y2 = y1 + 9;
        }
        m_brush.bind(new TGBrush(texture));
        setBounds(x1, y1, x2, y2);
    }

    //-----------------------------------------------------------------------
    //                            T G I m a g e
    //-----------------------------------------------------------------------
    TGImage::TGImage(TGControl *parent, int x, int y, TGTexture* texture) : TGControl(parent)
    {
        this->texture = texture;
        m_width = texture->getWidth();
        m_height = texture->getHeight();

        x2 = x1 + m_width - 1;
        y2 = y1 + m_height - 1;

        setBounds(x1,y1,x2,y2);
        m_brush.bind(new TGBrush(texture));
    }


    //-----------------------------------------------------------------------
    //                           ~ T G I m a g e
    //-----------------------------------------------------------------------
    TGImage::~TGImage()
    {
        //getRenderer()->destroyTexture(texture);
    }

    //-----------------------------------------------------------------------
    //                         s e t T e x t u r e
    //-----------------------------------------------------------------------
    void TGImage::setTexture(TGTexture *newTexture, bool resize)
    {
        texture = newTexture;
        m_width = texture->getWidth();
        m_height = texture->getHeight();
        if (resize)
            this->resize(m_width, m_height);
    }

    //-----------------------------------------------------------------------
    //                         s e t T e x t u r e
    //-----------------------------------------------------------------------
    void TGImage::setTexture(string fname, string resourceGroup, bool resize)
    {
        if(resourceGroup.empty())
        {
            resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME.c_str();
        }
        texture = getRenderer()->createTexture(fname,resourceGroup);
        m_width = texture->getWidth();
        m_height = texture->getHeight();
        if(resize)
            this->resize(m_width,m_height);
    }

    //-----------------------------------------------------------------------
    //                            r e n d e r
    //-----------------------------------------------------------------------
    void TGImage::render()
    {
        if(isRenderCached())
            return;
        int	x1, y1, x2, y2;
        getBounds(x1, y1, x2, y2);
        fillRect(x1, y1, x2, y2, m_brush);
        TGControl::render();
    }
}