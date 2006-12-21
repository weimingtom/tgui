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
#include "obsdemo.h"
#include <ExampleApplication.h>
#include <ExampleFrameListener.h>
#include <math.h>

using namespace TGUI;

static bool mShutdownRequested=false;

bool	running = true;
TGReal	rotation = 0.0f, size = 1.0f, backgnd = 0.2f, progress = 0.0f;
int	steps = 5;
TGSlider	*stepCount, *sizeSlider, *backSlider;
TGWindow	*win;
TGScreen	*screen1, *screen2;
TGLabel	*fps;



void enableFiltering(TGControl *sender)
{
    TGImage	*img = (TGImage*)TGSystem::getSingleton().getActiveScreen()->findChild("cenda");
//img->bitmap->setFiltering(true);
}

void disableFiltering(TGControl *sender)
{
TGImage	*img = (TGImage*)TGSystem::getSingleton().getActiveScreen()->findChild("cenda");
//	img->bitmap->setFiltering(false);
}



class DemoListener : public ExampleFrameListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
    DemoListener(RenderWindow* win, Camera* cam, bool bufferedKeys = false, bool bufferedMouse = false, 
        bool bufferedJoy = false ) : ExampleFrameListener(win,cam,true,true,true) 
    {
        mMouse->setEventCallback(this);
        mKeyboard->setEventCallback(this);
        mShutdownRequested = false;
    };


	bool frameStarted(const FrameEvent& evt)
    {
        TGUI::TGSystem::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
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
        TGUI::TGSystem::getSingleton().injectMouseMove( arg.state.X.rel,arg.state.Y.rel);
        return true;
    }

    //----------------------------------------------------------------//
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
    {
        OIS::MouseState ms = getMouseState();
        TGUI::TGSystem::getSingleton().injectMouseButtonDown(arg.state.X.rel,arg.state.Y.rel,id);
        return true;
    }

    //----------------------------------------------------------------//
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
    {
        OIS::MouseState ms = getMouseState();
        TGUI::TGSystem::getSingleton().injectMouseButtonUp(arg.state.X.rel,arg.state.Y.rel,id);
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

        TGUI::TGSystem::getSingleton().injectKeyDown(arg.key,arg.text);
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

class DemoApp : public ExampleApplication
{
    TGUI::TGSystem* mGUISystem;
    OIS::MouseState ms;
    TGThemeManager* mThemeManager;
public:
    ~DemoApp()
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
            mWindow = mRoot->initialise(true,"Original BS GUI Demo");
            return true;
        }
        else
        {
            return false;
        }
    }

    void createFrameListener(void)
    {
        mFrameListener= new DemoListener(mWindow, mCamera);
        mFrameListener->showDebugOverlay(true);
        mRoot->addFrameListener(mFrameListener);
        ms = ((DemoListener*)mFrameListener)->getMouseState();
    }

    bool imageWinResizedAction(const TGEventArgs& args)
    {
        TGImage	*img = (TGImage*)args.m_control->getFirstChild();
        if(!img)
            return true;
        int	w, h;
        args.m_control->getClientSize(w, h);
        img->setBounds(img->x1, img->y1, w-img->x1 - 1, h-img->y1 - 1);
        return true;
    }

    bool cendaClicked(const TGEventArgs& args)
    {
        (new TGMessagebox("Hello, I am Cenda :)"))->show();
        return true;
    }

    bool stepsModifiedAction(const TGEventArgs& args)
    {
        TGProgressBar	*pbar2 = (TGProgressBar*)TGSystem::getSingleton().getActiveScreen()->findChild("pbar2");
        steps = (int)stepCount->value.get() + 3;
        pbar2->setValue(steps - 3);
        return true;
    }

    bool aboutBoxAction(const TGEventArgs& args)
    {
        (new TGMessagebox("tgui version 0.1 Demo", "About"))->show();
        return true;
    }

    bool terminateAppAction(const TGEventArgs& args)
    {
        running = false;
        mShutdownRequested = true;
        return true;
    }

    bool createDynamicSubmenuAction(const TGEventArgs& args)
    {
        TGMenuItem        *sub = (TGMenuItem*)args.m_control;
        TGListbox         *lbox = (TGListbox*)TGSystem::getSingleton().getActiveScreen()->findChild("listbox");
        sub->clear();


        TGListboxItem* lbi;

        for (TGControlListItr itr = lbox->getChildren().begin(); itr != lbox->getChildren().end(); ++itr)
        {
            lbi = (TGListboxItem*)(*itr);
            sub->addItem(lbi->getText());
        }
        return true;
    }

    bool windowResized(const TGEventArgs& args)
    {
        return true;
    }

    bool addWideItemAction(const TGEventArgs& args)
    {
        TGListbox *lbox = (TGListbox*)TGSystem::getSingleton().getActiveScreen()->findChild("listbox");
        lbox->addItem("A very wide item to test horizontal scrolling");
        return true;
    }

    bool removeItemAction(const TGEventArgs& args)
    {
        TGListbox *lbox = (TGListbox*)TGSystem::getSingleton().getActiveScreen()->findChild("listbox");
        lbox->removeItem(lbox->getSelectedItem());
        return true;
    }

    bool addTheAboveTextAction(const TGEventArgs& args)
    {
        TGScreen* screen = TGSystem::getSingleton().getActiveScreen();

        TGListbox *lbox = (TGListbox*)screen->findChild("listbox");
        lbox->addItem(((TGEditbox*)screen->findChild("inputbox"))->getText());
        ((TGEditbox*)screen->findChild("inputbox"))->setText("");
        screen->findChild("inputbox")->focus();
        return true;
    }

    bool selectFileAction(const TGEventArgs& args)
    {
        TGFileBrowser	*browser = new TGFileBrowser("Select File");
        return true;
    }

    bool themeAction(const TGEventArgs& args)
    {
        if(mThemeManager->isVisible())
            mThemeManager->hide();
        else 
        {
            mThemeManager->show();
            mThemeManager->focus();
        }
        return true;
    }

    void createTest1()
    {
        TGWindow* win = new TGWindow("A fluffy window");
        win->center();

        TGListbox *lbox = new TGListbox(win, 10, 10, 175, 120);

        lbox->addItem("A string item");
        for (int i=0;i<20;i++)
        {
            char    buff[100];
            sprintf(buff, "Item %i of 20", i+1);
            lbox->addItem(buff);
        }
        lbox->setName("listbox");
    }

    void createTest2()
    {

        win = new TGWindow("A fluffy window");
        win->center();

        new TGLabel(win,"A Label", 5, 0);

        new TGButton(win, 10, 55, 180, 80, "Another Button");
        new TGButton(win, 10, 85, 180, 110, "Yet another Button");

        
        TGWindow	*win2 = new TGWindow("Another fluffy window");
        win2->center();
        win2->moveRel(win2->x1 + 200, win2->y1 - 70);
        win2->resize(win2->x2-win2->x1+1, win2->y2-win2->y1+270);

        TGProgressBar	*pbar2 = new TGProgressBar(win2, 10, 360, 175, 387);
        pbar2->setName("pbar2");
        pbar2->setMax(61);


        (new TGCheckbox(win2,"Checker", 10, 0, 180, 20))->setState(true);
        new TGCheckbox(win2,"Checker 2", 10, 25, 180, 45);
        new TGCheckbox(win2,"Checker 3", 10, 50, 180, 70);

        
        TGListbox *lbox = new TGListbox(win2, 10, 80, 175, 200);
        
        lbox->addItem("A string item");
        
        for (int i=0;i<20;i++)
        {
            char    buff[100];
            sprintf(buff, "Item %i of 20", i+1);
            lbox->addItem(buff);
        }
        lbox->setName("listbox");
        
        (new TGButton(win2, 10, 210, 175, 235, "Add wide item"))->addEventHandler(
            TGEvent::MouseClicked,new TGEventHandler(&DemoApp::addWideItemAction,this));

        (new TGButton(win2, 10, 240, 175, 265, "Remove active item"))->addEventHandler(
            TGEvent::MouseClicked,new TGEventHandler(&DemoApp::removeItemAction,this));

        (new TGEditbox(win2, 10, 270, 175, 295))->setName("inputbox");

        (new TGButton(win2, 10, 300, 175, 325, "Add the above text"))->addEventHandler(
            TGEvent::MouseClicked,new TGEventHandler(&DemoApp::addTheAboveTextAction,this));

        /*
        TGPopupMenu       *mainMenu = new TGPopupMenu();
        mainMenu->setName("mainMenu");

        TGMenuItem* mi = mainMenu->addItem("Select file...");
        mi->addEventHandler(TGEvent::Selected,new TGEventHandler(&DemoApp::selectFileAction,this));
        //new TGBitmap(INTERNALBMP_OPEN));
        TGMenuItem	*sub = mainMenu->addItem("Submenu test");
        sub->addItem("Sub menu item 1");
        sub->addItem("Sub menu item 2");
        sub->addItem("Sub menu item 3");
        sub->addItem("-");
        mi = sub->addItem("Sub sub menu");
        mi->addItem("Hello!")->setName("Hello!");

        mi = sub->addItem("Dynamic submenu");
        mi->addItem(" ");
        mi->addEventHandler(TGEvent::MenuPopup,new TGEventHandler(&DemoApp::createDynamicSubmenuAction,this));
        
        mi = mainMenu->addItem("About...");
        mi->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&DemoApp::aboutBoxAction,this));

        mi = mainMenu->addItem("-");
        //	new TGBitmap(INTERNALBMP_QUIT));
        mi = mainMenu->addItem("Quit");
        mi->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&DemoApp::terminateAppAction,this));
        */

/*
        TGWindow	*win3 = new TGWindow("A window");
        win3->center();
        win3->moveRel(win3->x1 - 200, win3->y1 - 70);
        win3->resize(190, 400);

        new TGLabel(win3,"Object resolution", 5, 25);
        stepCount = new TGSlider(win3, 10, 50, 180, 65);
        stepCount->setMax(61);
        stepCount->setValue(3);
        stepCount->addEventHandler(TGEvent::Modified, new TGEventHandler(&DemoApp::stepsModifiedAction,this));

        new TGLabel(win3,"Object size:", 5, 80);
        sizeSlider = new TGSlider(win3, 10, 105, 180, 120);
        sizeSlider->setMax(5);
        sizeSlider->value.setDataSource(&size);

        new TGLabel(win3,"Background intensity", 5, 135);
        backSlider = new TGSlider(win3, 10, 155, 180, 170);
        backSlider->setMax(1.0f);
        backSlider->value.setDataSource(&backgnd);

        new TGLabel(win3,"Test Combobox", 5, 185);
        TGCombobox* cb = new TGCombobox(win3);
        cb->moveRel(5,205);
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

        
        TGScrollbox	*sbox = new TGScrollbox(win3, 10, 240, 175, 350);
        new TGButton(sbox, 10, 10, 200, 35, "Clipped TGButton");
        new TGButton(sbox, 10, 40, 200, 65, "Another clipped TGButton");
        new TGCheckbox(sbox,"Clipped checkbox", 10, 80, 200, 100);
        new TGLabel(sbox,"Clipped label", 10, 120);
        


        screen1 = TGSystem::getSingleton().getActiveScreen();

        //screen1->setPopupMenu(mainMenu);


        /*

        TGWindow	*win5 = new TGWindow("TGImage control");

        win5->center();
        win5->moveRel(win5->x1, win5->y1 - 160);
        TGImage	*cenda = new TGImage(win5, 0, 0, "cenda.png");
        cenda->center();
        cenda->setName("cenda");
        cenda->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&DemoApp::cendaClicked,this));

        TGPopupMenu	*cendaMenu = new TGPopupMenu;
        cendaMenu->addItem("No filtering");
        cendaMenu->addItem("Bilinear filtering");
        cenda->setPopupMenu(cendaMenu);
        win5->setResizeEnabled(true);
        win5->addEventHandler(TGEvent::Resized,new TGEventHandler(&DemoApp::imageWinResizedAction,this));
        //win5->icon = new TGBitmap(INTERNALBMP_WINICON);

        win5->menu = new TGPopupMenu;
        win5->menu->addItem("No filtering");
        win5->menu->addItem("Bilinear filtering");

        win5->addEventHandler("controlResized",new TGEventHandler(&DemoApp::windowResized,this));

        (new TGButton(screen1, 750, 5, 795, 30, "Quit"))->addEventHandler(TGEvent::MouseClicked,
            new TGEventHandler(&DemoApp::terminateAppAction,this));

        (new TGButton(screen1, 5, 5, 150, 30, "Theme Manager"))->addEventHandler(TGEvent::MouseClicked,
            new TGEventHandler(&DemoApp::themeAction,this));


        mThemeManager = new TGThemeManager();
        mThemeManager->hide();
        /*
        win5 = new TGWindow("Float Window");
        win5->setBounds(0.25f, 0.25f, 1.f, 0.75f);
        win5->setPos(0.1f,0.1f);
        */

    }

    void createTest3()
    {
        
        TGWindow	*win = new TGWindow("A window");
        win->center();
        win->moveRel(win->x1, win->y1-100);
        win->resize(190, 200);

        TGCombobox* cb = new TGCombobox(win);
        cb->moveRel(5,5);
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

        new TGLabel(win,"A Test Label 123456789",5,35);

    }

    void createScene(void)
    {
        // setup GUI system
        mGUISystem = new TGUI::TGSystem(mWindow,mSceneMgr,"Garamond");

        createTest2();
    }

};


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{

    int i =1;
    DemoApp app;

    app.go();

    return 0;
}
