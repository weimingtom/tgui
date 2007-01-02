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
#ifndef __TGRENDERER_H__
#define __TGRENDERER_H__

namespace TGUI
{

    class TGTexture;
    class TGRenderer;
    class TGBrush;
    typedef Ogre::SharedPtr<TGBrush> TGSBrush;

    struct TGQuadVertex {
        TGReal x, y, z;                         // The position for the vertex.
        Ogre::RGBA diffuse;                     // colour of the vertex
        TGReal tu1, tv1;                        // texture coordinates
    };

    struct TGQuadInfo
    {
        bool                isClipped;
        Ogre::TexturePtr	texture;
        TGRect				position;
        TGQuadVertex        lpos[6];
        TGReal				z;
        TGRect				texPosition;
        uint32		        topLeftCol;
        uint32		        topRightCol;
        uint32		        bottomLeftCol;
        uint32		        bottomRightCol;

        TGQuadInfo();
        TGQuadInfo(const TGQuadInfo& rhs);

        TGQuadInfo& TGQuadInfo::operator= (const TGQuadInfo& rhs);

        bool operator<(const TGQuadInfo& other) const
        {
            // this is intentionally reversed.
            return z > other.z;
        }
    };

    typedef std::vector<TGQuadInfo> TGQuadList;

    class _TGUIExport TGRQListener : public Ogre::RenderQueueListener
    {
    public:
        TGRQListener(TGRenderer* renderer, Ogre::uint8 queueID, bool postQueue)
        {
            m_renderer		= renderer;
            m_queueID		= queueID;
            m_postQueue	    = postQueue;
        }

        virtual ~TGRQListener() {}

        virtual void	renderQueueStarted(Ogre::uint8 id, const Ogre::String& invocation, bool& skipThisQueue);
        virtual void	renderQueueEnded(Ogre::uint8 id, const Ogre::String& invocation, bool& repeatThisQueue);

        void	setTargetRenderQueue(Ogre::uint8 queueID)		{m_queueID = queueID;}
        void	setPostRenderQueue(bool postQueue)		{m_postQueue = postQueue;}

    private:
        TGRenderer*             m_renderer;    // TGUI renderer object for Ogre.
        Ogre::uint8	            m_queueID;     // ID of the queue that we are hooked into
        bool                    m_postQueue;   // true if we render after everything else in our queue.
    };

    struct TGClipArea
    {
        int		x1;
        int		y1;
        int		x2;
        int		y2;
    };

    typedef std::vector<TGClipArea*> TGClipList;

    class _TGUIExport TGRenderer 
    {
        unsigned int    texture;
        void*           rendererListEntry;
        bool            enabled;
        TGClipList      m_clipList;
        TGQuadInfo      quad;


    public:
        TGRenderer(Ogre::RenderWindow* window,
            Ogre::uint8 queue_id = Ogre::RENDER_QUEUE_OVERLAY,
            bool post_queue = false);

        TGRenderer(Ogre::RenderWindow* window, Ogre::uint8 queue_id, bool post_queue, Ogre::SceneManager* scene_manager);

        virtual ~TGRenderer();

        void openClipArea(int x1, int y1, int x2, int y2);
        void closeClipArea();
        void resetClipping();

        virtual	TGQuadInfo	addQuad(const TGRect& dest_rect, TGReal z, const TGSBrush brush);
        virtual	TGQuadInfo	addLine(const TGRect& dest_rect, TGReal z, const TGSBrush brush, int thickness);
        virtual	TGQuadInfo	addTri(const TGRect& dest_rect, TGReal z, const TGSBrush brush, int pointDir);

        void renderQuadDirect(const TGRect& dest_rect, TGReal z, TGSBrush brush);
        virtual	void	doRender(TGQuadList& quadList);

        virtual	TGTexture*	createTexture(void);
        virtual	TGTexture*	createTexture(const TGString& filename, const TGString& resourceGroup = "General");
        virtual	TGTexture*	createTexture(TGReal size);
        virtual	void		destroyTexture(TGTexture* texture);
        virtual void		destroyAllTextures(void);

        virtual bool	isQueueingEnabled(void) const	{return m_queueing;}
        virtual TGReal	getWidth(void) const		{return m_displayArea.getWidth();}
        virtual TGReal	getHeight(void) const		{return m_displayArea.getHeight();}
        virtual TGSize	getSize(void) const			{return m_displayArea.getSize();}
        virtual TGRect	getRect(void) const			{return m_displayArea;}
        virtual	uint	getMaxTextureSize(void) const		{return 2048;}
        virtual	uint	getHorzScreenDPI(void) const	{return 96;}
        virtual	uint	getVertScreenDPI(void) const	{return 96;}
        void	setTargetSceneManager(Ogre::SceneManager* scene_manager);
        void	setTargetRenderQueue(Ogre::uint8 queue_id, bool post_queue);
        TGTexture*	createTexture(Ogre::TexturePtr& texture);
        void	setDisplaySize(const TGSize& sz);
        void	resetZValue(void)				{d_current_z = GuiZInitialValue;}
        void	advanceZValue(void)				{d_current_z -= GuiZElementStep;}
        TGReal	getCurrentZ(void) const			{return d_current_z;}
        TGReal	getZLayer(uint layer) const		{return d_current_z - ((TGReal)layer * GuiZLayerStep);}
    private:
        static const TGReal	GuiZInitialValue;       // Initial value to use for 'z' each frame.
        static const TGReal	GuiZElementStep;        // Value to step 'z' for each GUI element.
        static const TGReal	GuiZLayerStep;          // Value to step 'z' for each GUI layer.


        TGReal	d_current_z;		//!< The current z co-ordinate value.

        static const size_t    VERTEX_PER_QUAD;     // number of vertices per quad
        static const size_t    VERTEX_PER_TRIANGLE;	// number of vertices for a triangle
        static const size_t    VERTEXBUFFER_INITIAL_CAPACITY; // initial capacity of the allocated vertex buffer
        static const size_t    UNDERUSED_FRAME_THRESHOLD;     // number of frames to wait before shrinking buffer

        void	initRenderStates(void);

        bool clipQuad(TGClipArea* clip, TGRect& drect, TGRect& tRect, TGColourRect colours);

        uint32 colourToOgre(const TGColour& col) const;

        void constructor_impl(Ogre::RenderWindow* window, Ogre::uint8 queue_id, bool post_queue);


        TGRect				        m_displayArea;

        bool	                    m_queueing;	        // setting for queueing control.

        // Ogre specific bits.
        Ogre::Root*                 m_ogreRoot;		    // pointer to the Ogre root object that we attach to
        Ogre::RenderSystem*         m_renderSys;		// Pointer to the render system for Ogre.
        Ogre::uint8	                m_queue_id;			// ID of the queue that we are hooked into
        Ogre::TexturePtr            m_currTexture;		// currently set texture;
        Ogre::RenderOperation       m_render_op;		// Ogre render operation we use to do our stuff.
        Ogre::HardwareVertexBufferSharedPtr	m_buffer;	// vertex buffer to queue sprite rendering
        size_t                      m_underused_framecount;                  //!< Number of frames elapsed since buffer utilization was above half the capacity
        Ogre::RenderOperation       m_direct_render_op;	// Renderop for cursor
        Ogre::HardwareVertexBufferSharedPtr	m_direct_buffer;	//!< Renderop for cursor
        Ogre::SceneManager*	        m_sceneMgr;		    // The scene manager we are hooked into.
        Ogre::LayerBlendModeEx      m_colourBlendMode;	// Controls colour blending mode used.
        Ogre::LayerBlendModeEx      m_alphaBlendMode;	// Controls alpha blending mode used.
        Ogre::TextureUnitState::UVWAddressingMode m_uvwAddressMode;

        TGRQListener*			    m_ourlistener;
        bool                        m_post_queue;		// true if we render after everything else in our queue.
        size_t                      m_bufferPos;		// index into buffer where next vertex should be put.
        bool                        m_modified;			// true when data in quad list is modified.
        TGPoint                     m_texelOffset;		// Offset required for proper texel mapping.

        std::list<TGTexture*>       m_texturelist;		// List used to track textures.

    };
}

#endif
