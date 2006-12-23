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
#include "tguidemo.h"
#include <ExampleApplication.h>
#include <ExampleFrameListener.h>
#include <math.h>

using namespace TGUI;

static bool mShutdownRequested=false;

class MinListener : public ExampleFrameListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
    MinListener(RenderWindow* win, Camera* cam, bool bufferedKeys = false, bool bufferedMouse = false, 
        bool bufferedJoy = false ) : ExampleFrameListener(win,cam,true,true,true) 
    {
        mMouse->setEventCallback(this);
        mKeyboard->setEventCallback(this);
        mShutdownRequested = false;
    };


	bool frameStarted(const FrameEvent& evt)
    {
        TGSystem::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
        return ExampleFrameListener::frameStarted(evt);
    }

    bool frameEnded(const FrameEvent& evt)
    {
        if (mShutdownRequested)
            return false;
        else
            return ExampleFrameListener::frameEnded(evt);
    }

    //----------------------------------------------------------------//
    bool mouseMoved( const OIS::MouseEvent &arg )
    {
        TGSystem::getSingleton().injectMouseMove( arg.state.X.rel,arg.state.Y.rel);
        return true;
    }

    //----------------------------------------------------------------//
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
    {
        OIS::MouseState ms = getMouseState();
        TGSystem::getSingleton().injectMouseButtonDown(arg.state.X.rel,arg.state.Y.rel,id);
        return true;
    }

    //----------------------------------------------------------------//
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
    {
        OIS::MouseState ms = getMouseState();
        TGSystem::getSingleton().injectMouseButtonUp(arg.state.X.rel,arg.state.Y.rel,id);
        return true;
    }

    bool keyPressed( const OIS::KeyEvent &arg )
    {

        if( arg.key == OIS::KC_ESCAPE )
            mShutdownRequested = true;

        if(mKeyboard->isKeyDown(OIS::KC_SYSRQ))
        {
            std::ostringstream ss;
            ss << "screenshot_" << ++mNumScreenShots << ".png";
            mWindow->writeContentsToFile(ss.str());
        }

        TGSystem::getSingleton().injectKeyDown(arg.key,arg.text);
        return true;

    }

    //----------------------------------------------------------------//
    bool keyReleased( const OIS::KeyEvent &arg )
    {
        TGUI::TGSystem::getSingleton().injectKeyUp(arg.key,arg.text);
        return true;
    }


    OIS::MouseState getMouseState()
    {
        return mMouse->getMouseState();
    }


};

class MinimalApp : public ExampleApplication
{
    TGUI::TGSystem* mGUISystem;
    OIS::MouseState ms;
public:
    ~MinimalApp()
    {
        delete mGUISystem;
    }

    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure(void)
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(mRoot->showConfigDialog())
        //if(mRoot->restoreConfig())
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mWindow = mRoot->initialise(true,"tgui Demo");
            return true;
        }
        else
        {
            return false;
        }
    }

    void createFrameListener(void)
    {
        mFrameListener= new MinListener(mWindow, mCamera);
        mFrameListener->showDebugOverlay(true);
        mRoot->addFrameListener(mFrameListener);
        ms = ((MinListener*)mFrameListener)->getMouseState();
    }

    bool aboutBoxAction(const TGEventArgs& args)
    {
        (new TGMessagebox("Tiny GUI 0.1 Demo", "About"))->show();
        return true;
    }

    bool terminateAppAction(const TGEventArgs& args)
    {
        mShutdownRequested = true;
        return true;
    }

    void createTest1()
    {

        TGSBrush    brush;

        TGWindow	*win = new TGWindow("");
        win->resize(256, 256);
        win->center();
        win->setResizeEnabled(true);
        win->setTitlebarEnabled(true);
        win->setFrameEnabled(false);
        win->setTitlebarHeight(50);

        
        TGSBrush b1,b2;
        b1.bind(new TGBrush());
        b1->setTexture("cap2.png");
        win->getTheme().m_caption = b1;

        b2.bind(new TGBrush());
        b2->setTexture("win2.png");
        win->getTheme().m_base = b2;
        //win->getColourTheme().m_base->setColour(TGColour(.5f,0,0));


        TGImageButton* b = new TGImageButton(win,"playbutton.png");
        b->setWidth(128);
        b->setHeight(64);
        b->center();

        
        TGWindow *win2 = new TGWindow("");
        win2->setPos(10,10);
        win2->resize(384,256);
        win2->setResizeEnabled(true);
        win2->setFrameEnabled(false);
        win2->setTitlebarEnabled(false);

        b = new TGImageButton(win2,"playbutton.png");
        b->setPos(60,94);
        b->setWidth(256);
        b->setHeight(128);

        //new TGButton(win2,10,10,100,40,"Test");

        TGTexture* tex = TGSystem::getSingleton().getRenderer()->createTexture("win1.png");
        brush.setNull();
        brush.bind(new TGBrush(tex));
        win2->getTheme().m_base = brush;

        //new TGButton(win2,10,50,100,90,"Test 2");

    }

    void createTest2()
    {

        TGWindow	*win = new TGWindow("Test Window");
        win->center();
        win->moveRel(win->x1, win->y1-100);
        win->resize(190, 200);
        win->setResizeEnabled(true);

        
        TGCombobox* cb = new TGCombobox(win);
        cb->setPos(5,15);
        cb->resize(175,25);
        cb->addItem("test item 1");
        cb->addItem("test item 2");
        
        cb->addItem("test item 3");
        cb->addItem("test item 4");
        cb->addItem("test item 5");
        cb->addItem("test item 6");
        cb->addItem("test item 7");
        cb->addItem("test item 8");
        cb->addItem("test item 9");
        cb->addItem("test item 10");
        
        TGSpinEdit* c = new TGSpinEdit(win,0,0,0,0);
        c->setPos(5,60);
        c->resize(80,25);
        win->focus();
       
    }

    void createScene()
    {
        mGUISystem = new TGUI::TGSystem(mWindow,mSceneMgr,"Garamond");

        mCamera->getViewport()->setBackgroundColour(TGColour(0.25,0.25,0.25));

        createTest1();
        createTest2();

        TGMenubar* mb = new TGMenubar(TGSystem::getSingleton().getActiveScreen());
        mb->addItem("File");
        mb->addItem("Edit");
        mb->addItem("View");
        mb->addItem("Community");
        mb->addItem("Help");


    }
};


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{

    int i =1;
    MinimalApp app;

    app.go();

    return 0;
}
