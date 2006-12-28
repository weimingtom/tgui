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
#include "minimal.h"
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
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mWindow = mRoot->initialise(true,"Minimal tgui Sample");
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
        (new TGMessageBox("Tiny GUI 0.1 Demo", "About"))->show();
        return true;
    }

    bool terminateAppAction(const TGEventArgs& args)
    {
        mShutdownRequested = true;
        return true;
    }


    void createScene(void)
    {
        
        mGUISystem = new TGUI::TGSystem(mWindow,mSceneMgr,"Garamond");

        TGWindow	*win = new TGWindow("A tgui Window");
        win->center();
        win->moveRel(win->x1, win->y1-100);
        win->resize(190, 200);
        win->setResizeEnabled(true);
        
    }

};


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{

    MinimalApp app;

    app.go();

    return 0;
}
