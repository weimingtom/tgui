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
#include <tgui.h>

namespace TGUI
{
    uint32    TGTexture::m_texturenumber=0;	        // Counter used to provide unique texture names.

    //-----------------------------------------------------------------------
    //                       s e t O g r e T e x t u r e S i z e
    //-----------------------------------------------------------------------
    void TGTexture::setOgreTextureSize(uint size)
    {
        using namespace Ogre;

        // unload any current Ogre::Texture
        freeOgreTexture();

        // Try to create an empty texture of the given size
        m_ogre_texture = TextureManager::getSingleton().createManual(getUniqueName(), "General", TEX_TYPE_2D, size, size, 0, PF_A8R8G8B8, TU_DEFAULT);

        // if we got a pointer cache some details
        if (!m_ogre_texture.isNull())
        {
            m_width		= m_ogre_texture->getWidth();
            m_height	= m_ogre_texture->getHeight();
        }
        // no texture so throw.
        else
        {
            throw Ogre::Exception(0,"Failed to create texture of specified size: Ogre::Texture creation failed.","TGTexture");
        }

    }

    //-----------------------------------------------------------------------
    //                       f r e e O g r e T e x t u r e
    //-----------------------------------------------------------------------
    void TGTexture::freeOgreTexture(void)
    {
        if ((!m_ogre_texture.isNull()) && !m_isLinked)
        {
            Ogre::TextureManager::getSingleton().remove(m_ogre_texture->getHandle());
        }
        m_ogre_texture.setNull();
    }

    //-----------------------------------------------------------------------
    //                       g e t U n i q u e N a m e
    //-----------------------------------------------------------------------
    Ogre::String TGTexture::getUniqueName(void)
    {
        Ogre::String str;

        Ogre::StringUtil::StrStreamType strstream;
        strstream << "_tgui_ogre_" << m_texturenumber;
        str = strstream.str();

        ++m_texturenumber;

        return str;
    }

    //-----------------------------------------------------------------------
    //                       g e t O g r e T e x t u r e 
    //-----------------------------------------------------------------------
    void TGTexture::setOgreTexture(Ogre::TexturePtr& texture)
    {
        freeOgreTexture();

        m_ogre_texture = texture;
        m_width	 = m_ogre_texture->getWidth();
        m_height = m_ogre_texture->getHeight();
        m_isLinked = true;
    }

    //-----------------------------------------------------------------------
    //                          l o a d F r o m F i l e
    //-----------------------------------------------------------------------
    void TGTexture::loadFromFile(const TGString& filename, const TGString& resourceGroup)
    {
        using namespace Ogre;

        // unload old ogre texture
        freeOgreTexture();

        // create / load a new ogre texture from the specified image
        try
        {
            TextureManager& textureManager = TextureManager::getSingleton();

            // see if texture already exists
            Ogre::TexturePtr ogreTexture = (Ogre::TexturePtr)textureManager.getByName(filename.c_str());

            if (!ogreTexture.isNull())
            {
                // texture already exists, so create a 'linked' texture (ensures texture is not destroyed twice)
                m_ogre_texture = ogreTexture;
                m_isLinked = true;
            }
            // texture does not already exist, so load it in
            else
            {
                String orpGroup;
                if (resourceGroup.empty())
                {
                    const String& defGrp = "";
                    orpGroup = defGrp.empty() ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME.c_str() : defGrp;
                }
                else
                {
                    orpGroup = resourceGroup;
                }

                m_ogre_texture = TextureManager::getSingleton().load(filename.c_str(), orpGroup.c_str(), TEX_TYPE_2D, 0, 1.0f);
                m_isLinked = false;
            }

        }
        catch(Ogre::Exception e)
        {
            throw Ogre::Exception(0,"Failed to create Texture object from file '" + filename + "'. Additional Information:\n" + e.getFullDescription().c_str(),"TGTexture");
        }

        // if we got a pointer cache some details
        if (!m_ogre_texture.isNull())
        {
            m_width		= m_ogre_texture->getWidth();
            m_height	= m_ogre_texture->getHeight();
        }
        // no texture from image so throw.
        else
        {
            throw Ogre::Exception(0,"Failed to create Texture object from file '" + filename + "'.  Ogre returned a NULL pointer.","TGTexture");
        }

    }

}