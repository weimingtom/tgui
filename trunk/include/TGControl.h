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
#ifndef __TGCONTROL_H__
#define __TGCONTROL_H__

namespace TGUI
{
    enum FrameStyle
    {
        FS_NONE,
        FS_FLAT,
        FS_RAISED,
        FS_LOWERED
    };

    class TGScreen;
    class TGPopupMenu;

    typedef std::list<TGControl *> TGControlList;
    typedef std::list<TGControl *>::iterator TGControlListItr;
    typedef std::list<TGControl *>::reverse_iterator TGControlListRevItr;
    typedef std::list<TGEventHandler *> TGEventHandlers;
    typedef std::map<TGString, TGEventHandlers> TGEventMap;

    class TGControl
    {
    protected:
        bool                m_isVisible;
        bool                m_redraw;
        bool                m_frameEnabled;
        TGControlList       m_children;
        TGEventMap          m_handlers;
        TGColourTheme       m_theme;
        TGQuadList          m_quadCache;
        TGQuadList&         m_systemCache;
        TGRenderer*         m_renderer;
        TGTexture*          m_texture;

        TGString            m_name;
        TGReal               padLeft;
        TGReal               padTop;
        TGReal               padRight;
        TGReal               padBottom;
        TGReal               minWidth;
        TGReal               minHeight;
        TGReal               maxWidth;
        TGReal               maxHeight;
        bool                performLayout;

        TGControl*          m_focusedChild;
        TGPopupMenu*        m_popupMenu;

    public:
        TGControl*          m_parent;
        TGControl*          exclusiveChild;
        bool                mouseOverControl;
        bool                isComposite;
        TGReal               xShift;
        TGReal               yShift;
        int                 x1;
        int                 y1;
        int                 x2;
        int                 y2;

    public:
        TGControl(TGControl *parent);
        virtual ~TGControl();

        TGRenderer* getRenderer();

        virtual TGString getName() {return m_name;};
        virtual void setName(TGString value);

        TGControlList& getChildren() {return m_children;};


        virtual TGControl *findChild(TGString name);

        TGPopupMenu* getPopupMenu() {return m_popupMenu;};
        void setPopupMenu(TGPopupMenu* value) {m_popupMenu = value;};

        TGControl* getFirstChild();
        TGControl* getLastChild();

        virtual TGString getControlType() {return "TGControl";};

        bool getFrameEnabled() {return m_frameEnabled;};
        void setFrameEnabled(bool value) {m_frameEnabled = value; redraw();};

        TGControl* getFocusedChild(void) {return m_focusedChild;};
        void setFocusedChild(TGControl* child);

        void logMessage(TGString message);

        virtual void addChild(TGControl *child);
        virtual void removeChild(TGControl *child);
        virtual void removeAllChildren();
        virtual void layout(){};

        bool fireEvent(TGString eventID,TGEventArgs& args);
        void addEventHandler(TGString eventID, TGEventHandler* handler);
        void removeEventHandler(TGString eventID, TGEventHandler* handler);
        void removeAllHandlers(void* obj);
        void removeAllHandlers(TGControl* control);

        virtual TGControl *childAt(TGReal x, TGReal y);
        virtual bool pointInControl(TGReal x, TGReal y);

        TGScreen *getScreen();

        virtual void makeExclusive();

        virtual void show() {m_isVisible = true;};
        virtual void hide() {m_isVisible = false;};
        virtual bool isVisible() {return m_isVisible;};

        virtual TGScreen* getActiveScreen();

        virtual void pulse(TGReal timeElapsed);
        virtual void focus();
        virtual bool focused();

        virtual bool isRenderCached();
        virtual void render();
        virtual void redraw(bool value=true);

        virtual void setTexture(TGTexture* value) {m_texture = value;};
        virtual TGTexture* getTexture() {return m_texture;};

        //
        // integer values = pixels
        // TGReal values = percentage of screen area
        //
        virtual void setBounds(int x1, int y1, int x2, int y2);
        virtual void setBounds(TGReal fx1, TGReal fy1, TGReal fx2, TGReal fy2);
        virtual void getBounds(int &x1, int &y1, int &x2, int &y2);
        virtual void getBounds(TGReal &x1, TGReal &y1, TGReal &x2, TGReal &y2);

        virtual void setPos(int x1, int y1);
        virtual void setPos(TGReal x1, TGReal y1);
        virtual void getPos(int &x1, int &y1);
        virtual void getPos(TGReal &x1, TGReal &y1);

        virtual void setWidth(int width);
        virtual void setWidth(TGReal width);
        virtual void getWidth(int &width);
        virtual void getWidth(TGReal &width);

        virtual void setHeight(int height);
        virtual void setHeight(TGReal height);
        virtual void getHeight(int &height);
        virtual void getHeight(TGReal &height);

        virtual void moveRel(int x, int y);
        virtual void moveRel(TGReal x, TGReal y);

        virtual void resize(int width, int height);
        virtual void center(bool horizontal=true, bool vertical=true);
        virtual void translate(int &x, int &y);
        virtual void setPadding(int left, int top=-1, int right=-1,
            int bottom=-1);
        virtual void getClientSize(int &w, int &h);

        TGColourTheme& getColourTheme() {return m_theme;};
        virtual void setColourTheme(TGColourTheme theme,bool updateChildren=false);

        void setMouseTrackingControl(TGControl *control);

        // drawing helpers
        virtual void openClip();
        virtual void closeClip();
        virtual void drawOwnFrame();
        virtual void drawOwnFocus();

        void resetClipping();
        void openClipArea(int x1, int y1, int x2, int y2);
        void closeClipArea();

        void drawRect(int x1, int y1, int x2, int y2, TGSBrush brush, int thickness=1);
        void fillRect(int x1, int y1, int x2, int y2, TGSBrush brush);
        void drawLine(int x1, int y1, int x2, int y2,TGSBrush brush, int thickness=1);
        void drawTri(int x1, int y1, int x2, int y2, TGSBrush brush, int pointDir=0);
        void drawFrame(int x1, int y1, int x2, int y2,
            FrameStyle s=FS_FLAT,int thickness=1);
        void drawString(int x, int y, TGString str, TGSBrush brush, int length=-1);

        int stringWidth(TGString str, size_t length=-1);
        int stringHeight();

        void setKeyboardFocusControl(TGControl *control);
        bool hasKeyboardFocus(TGControl *control);
        void invalidateControl(TGControl *control);


        // mouse events
        virtual void onMouseEnter();
        virtual void onMouseMoved(int x, int y);
        virtual void onMouseExit(int x, int y);
        virtual void onMouseDown(int x, int y, int b);
        virtual void onMouseUp(int x, int y, int b);
        // keyboard events
        virtual void onKeyDown(int key, unsigned char ascii);
        virtual void onKeyUp(int key, unsigned char ascii);
        // focus events
        virtual void onFocusEnter(TGControl* oldFocus){redraw();};
        virtual void onFocusExit(){redraw();};
    };

    typedef TGControl TGWidget;
}
#endif