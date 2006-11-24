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
    //                            T G F o n t
    //-----------------------------------------------------------------------
    TGFont::TGFont(string fontName,string resourceGroup)
    {
        if(resourceGroup.empty())
            resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME.c_str();

        
        m_font = (Ogre::FontPtr) Ogre::FontManager::getSingleton().getByName(fontName);
        if (m_font.isNull())
            Ogre::Exception(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Could not find font " + fontName, "TGFont::TGFont");
        m_font->load();
        m_material = m_font->getMaterial();
        Ogre::TexturePtr tp = m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->_getTexturePtr();
        m_texture = TGSystem::getSingleton().getRenderer()->createTexture();
        m_texture->setOgreTexture(tp);
        m_height = 14;

    }

    //-----------------------------------------------------------------------
    //                           ~ T G F o n t
    //-----------------------------------------------------------------------
    TGFont::~TGFont()
    {
    }

}