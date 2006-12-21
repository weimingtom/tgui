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

namespace TGUI
{
    //-----------------------------------------------------------------------
    //                         T G I m a g e S e t
    //-----------------------------------------------------------------------
    TGImageSet::TGImageSet(TGString fname,int imagecount, TGString resourceGroup)
    {
        m_imageCount = imagecount;
        if(resourceGroup.empty())
        {
            resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME.c_str();
        }
        m_texture = TGSystem::getSingleton().getRenderer()->createTexture(fname,resourceGroup);
        m_width = m_texture->getWidth();
        m_height = m_texture->getHeight();

        TGReal w=m_width,h=m_height;
        int ih = m_height / m_imageCount;

        TGRect  uv;
        uv.d_left = 0.f;
        uv.d_right = 1.f;

        for(int i=0;i<m_imageCount;i++)
        {
            int ps = ih * i;
            int pe = ps + ih;

            uv.d_top = (TGReal) ps / m_height;
            uv.d_bottom = (TGReal) pe / m_height;

            m_uvList.push_back(TGRect(uv));
        }
    }

    //-----------------------------------------------------------------------
    //                        ~ T G I m a g e S e t
    //-----------------------------------------------------------------------
    TGImageSet::~TGImageSet()
    {
    }

    //-----------------------------------------------------------------------
    //                           g e t U V R e c t
    //-----------------------------------------------------------------------
    TGRect TGImageSet::getUVRect(int index)
    {
        TGRect res;

        if((index > 0) && ((size_t)index < m_uvList.size()))
            res = m_uvList[index];

        return res;
    }


}