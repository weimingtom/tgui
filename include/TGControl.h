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
    typedef std::map<string, TGEventHandlers> TGEventMap;

    class TGControl
    {
    protected:
        bool                m_isVisible;
        bool                m_redraw;
        TGControlList       m_children;
        TGEventMap          m_handlers;
        TGColourTheme       m_theme;
        TGQuadList          m_quadCache;
        TGQuadList&         m_systemCache;
        TGRenderer*         m_renderer;
        TGTexture*          m_texture;

        TGColour            gColor;

        string              name;
        float               padLeft;
        float               padTop;
        float               padRight;
        float               padBottom;
        float               minWidth;
        float               minHeight;
        float               maxWidth;
        float               maxHeight;
        bool                performLayout;

        TGControl*          m_focusedChild;
        TGPopupMenu*        m_popupMenu;

    public:
        TGControl*          m_parent;
        TGControl*          exclusiveChild;
        bool                mouseOverControl;
        float               xShift;
        float               yShift;
        int                 x1;
        int                 y1;
        int                 x2;
        int                 y2;

    public:
        TGControl(TGControl *parent);
        virtual ~TGControl();

        TGRenderer* getRenderer();

        virtual string getName() {return name;};
        virtual void setName(string newName);

        TGControlList& getChildren() {return m_children;};


        virtual TGControl *findChild(string name);

        TGPopupMenu* getPopupMenu() {return m_popupMenu;};
        void setPopupMenu(TGPopupMenu* value) {m_popupMenu = value;};

        TGControl* getFirstChild();
        TGControl* getLastChild();

        virtual string getControlType() {return "TGControl";};

        TGControl* getFocusedChild(void) {return m_focusedChild;};
        void setFocusedChild(TGControl* child);

        void logMessage(string message);

        virtual void addChild(TGControl *child);
        virtual void removeChild(TGControl *child);
        virtual void removeAllChildren();
        virtual void layout(){};

        bool fireEvent(string eventID,TGEventArgs& args);
        void addEventHandler(string eventID, TGEventHandler* handler);
        void removeEventHandler(string eventID, TGEventHandler* handler);
        void removeAllHandlers(void* obj);
        void removeAllHandlers(TGControl* control);

        virtual TGControl *childAt(float x, float y);
        virtual bool pointInControl(float x, float y);

        TGScreen *getScreen();

        virtual void makeExclusive();

        virtual void show() {m_isVisible = true;};
        virtual void hide() {m_isVisible = false;};
        virtual bool isVisible() {return m_isVisible;};

        virtual TGScreen* getActiveScreen();

        virtual void pulse(float timeElapsed);
        virtual void focus();
        virtual bool focused();

        virtual bool isRenderCached();
        virtual void render();
        virtual void redraw(bool value=true);

        virtual void setTexture(TGTexture* value) {m_texture = value;};
        virtual TGTexture* getTexture() {return m_texture;};

        //
        // integer values = pixels
        // float values = percentage of screen area
        //
        virtual void setBounds(int x1, int y1, int x2, int y2);
        virtual void setBounds(float fx1, float fy1, float fx2, float fy2);
        virtual void getBounds(int &x1, int &y1, int &x2, int &y2);
        virtual void getBounds(float &x1, float &y1, float &x2, float &y2);

        virtual void setPos(int x1, int y1);
        virtual void setPos(float x1, float y1);
        virtual void getPos(int &x1, int &y1);
        virtual void getPos(float &x1, float &y1);

        virtual void setWidth(int width);
        virtual void setWidth(float width);
        virtual void getWidth(int &width);
        virtual void getWidth(float &width);

        virtual void setHeight(int height);
        virtual void setHeight(float height);
        virtual void getHeight(int &height);
        virtual void getHeight(float &height);

        virtual void moveRel(int x, int y);
        virtual void moveRel(float x, float y);

        virtual void resize(int width, int height);
        virtual void center(bool horizontal=true, bool vertical=true);
        virtual void translate(int &x, int &y);
        virtual void setPadding(int left, int top=-1, int right=-1,
            int bottom=-1);
        virtual void getClientSize(int &w, int &h);

        TGColourTheme getColourTheme() {return m_theme;};
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


        void color(int r, int g, int b, int a=255);
        void color(TGColour c);
        void drawRect(int x1, int y1, int x2, int y2,int thickness=1);
        void fillRect(int x1, int y1, int x2, int y2, TGTexture* tex=NULL);
        void drawLine(int x1, int y1, int x2, int y2,int thickness=1);
        void drawTri(int x1, int y1, int x2, int y2, int pointDir);
        void drawFrame(int x1, int y1, int x2, int y2,
            FrameStyle s=FS_FLAT,int thickness=1);
        void drawString(int x, int y, string str, int length=-1);

        int stringWidth(string str, size_t length=-1);
        int stringHeight();

        void setKeyboardFocusControl(TGControl *control);
        bool hasKeyboardFocus(TGControl *control);
        void invalidateControl(TGControl *control);


        // mouse events
        virtual void onMouseEnter();
        virtual void onMouseMoved(int x, int y);
        virtual void onMouseExit();
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
