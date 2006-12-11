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
#ifndef __TGTEXTURE_H__
#define __TGTEXTURE_H__

namespace TGUI
{
    class TGTexture
    {
        friend	TGTexture* TGRenderer::createTexture(void);
        friend	TGTexture* TGRenderer::createTexture(const string& filename, const string& resourceGroup);
        friend	TGTexture* TGRenderer::createTexture(float size);
        friend	void	 TGRenderer::destroyTexture(TGTexture* texture);

    public:
        enum PixelFormat
        {
            //! Each pixel is 3 bytes. RGB in that order.
            PF_RGB,
            //! Each pixel is 4 bytes. RGBA in that order.
            PF_RGBA
        };

        virtual	ushort	getWidth(void)          const {return m_width;}
        virtual	ushort	getHeight(void)         const {return m_height;}
        virtual ushort  getOriginalWidth(void)  const { return getWidth(); }
        virtual float   getXScale(void)         const { return 1.0f / static_cast<float>(getOriginalWidth()); } 
        virtual ushort  getOriginalHeight(void) const { return getHeight(); }
        virtual float   getYScale(void) const { return 1.0f / static_cast<float>(getOriginalHeight()); }
        virtual void	loadFromFile(const string& filename, const string& resourceGroup);
        TGRenderer*	    getRenderer(void)       const {return m_owner;}

        Ogre::TexturePtr	getOgreTexture(void) const		{return m_ogre_texture;}
        void	setOgreTextureSize(uint size);
        void	setOgreTexture(Ogre::TexturePtr& texture);
        virtual ~TGTexture(void) {};


    protected:
        TGTexture(TGRenderer* owner) : m_owner(owner) {}
    private:
        TGRenderer* m_owner;		                // Renderer object that created and owns this texture
        void	freeOgreTexture(void);

        // return a Ogre::string that contains a unique name.
        Ogre::String	    getUniqueName(void);

        static	uint32      m_texturenumber;	// Counter used to provide unique texture names.

        Ogre::TexturePtr    m_ogre_texture;		// The 'real' texture.

        ushort				m_width;			// cached width of the texture
        ushort				m_height;			// cached height of the texture

        bool	            m_isLinked;         // True if we are linked to a texture we did not actually create.

    };

    typedef Ogre::SharedPtr<TGTexture> TGSTexture;

} 

#endif