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
#include "demo.h"
#include <ExampleApplication.h>
#include <ExampleFrameListener.h>
#include <math.h>

using namespace TGUI;

static bool mShutdownRequested=false;

bool	running = true;
float	rotation = 0.0f, size = 1.0f, backgnd = 0.2f, progress = 0.0f;
int	steps = 5;
TGSlider	*stepCount, *sizeSlider, *backSlider;
TGWindow	*win;
TGScreen	*screen1, *screen2;
TGLabel	*fps;


/*
void terminateAppAction(TGControl *sender)
{
running = false;
}

void closeWindowAction(TGControl *sender)
{
delete sender->m_parent;
}

void newWindowAction(TGControl *sender)
{
TGWindow	*w = new TGWindow("A simple window");
w->place(10, 10, 300, 100);
w->move(rand()%600+30, rand()%500+30);

TGButton	*button = new TGButton(w, 10, 20, 280, 55, "Close me");
button->clicked = new TGCallbackAction(closeWindowAction);
}


void addTheAboveTextAction(TGControl *sender)
{
TGListbox *lbox = (TGListbox*)screen->findChild("listbox");
lbox->addItem(((TGInputbox*)screen->findChild("inputbox"))->getText());
((TGInputbox*)screen->findChild("inputbox"))->setText("");
screen->findChild("inputbox")->focus();
}

void createDynamicSubmenuAction(TGControl *sender)
{
TGMenuItem        *sub = (TGMenuItem*)sender;
TGListbox         *lbox = (TGListbox*)screen1->findChild("listbox");
sub->clear();
for (TGListboxItem *item = (TGListboxItem*)lbox->firstChild;item;
item = (TGListboxItem*)item->next)
sub->addItem(item->text, NULL);
}

void activateScreen1(TGControl *sender)
{
screen1->activate();
}

void activateScreen2(TGControl *sender)
{
screen2->activate();
}

void renderObject()
{
/*
glDisable(GL_CULL_FACE);
glBegin(GL_TRIANGLES);
float	a = 0.0f, step;
step = (360.0f/(float)steps)*3.14f/180.0f;
for (int i=0;i<steps;i++,a+=step)
{
glColor3f(i/(float)steps, i/((float)steps+1.0f),
i/((float)steps+2.0f));
glVertex3f(0.0f, size, 0.0f);
glVertex3f(sinf(a)*size, 0.0f, cosf(a)*size);
glVertex3f(sinf(a+step)*size, 0.0f, cosf(a+step)*size);
}
a = 0.0f;
for (int i=0;i<steps;i++,a+=step)
{
glColor3f(i/(float)steps, i/((float)steps+1.0f),
i/((float)steps+2.0f));
glVertex3f(0.0f, -size, 0.0f);
glVertex3f(sinf(a)*size, 0.0f, cosf(a)*size);
glVertex3f(sinf(a+step)*size, 0.0f, cosf(a+step)*size);
}
glEnd();
glEnable(GL_CULL_FACE);

}


void renderObjectAction(TGControl *sender)
{
/*
glTranslatef(0.0f, 0.0f, -5.0f);
glRotatef(rotation, 0.0f, 1.0f, 0.0f);

renderObject();

}

void fileSelectedAction(TGControl *sender)
{
string fname = ((TGFileBrowser*)sender)->getFilename();
printf("File selected: %s\n", fname.c_str());
}

void selectFileAction(TGControl *sender)
{
TGFileBrowser	*browser = new TGFileBrowser("Select File");
browser->selected = new TGCallbackAction(fileSelectedAction);
}

void aboutBoxAction(TGControl *sender)
{
messageBox("BSGUI (Bad Sector's OpenGL GUI) version 0.2 Demo", "About");
}

void imageWinResizedAction(TGControl *sender)
{
TGImage	*img = (TGImage*)sender->firstChild;
int	w, h;
sender->getClientSize(w, h);
img->minWidth = 10;
img->minHeight = 10;
img->place(img->x1, img->y1, w-img->x1 - 1, h-img->y1 - 1);
}

void enableFiltering(TGControl *sender)
{
TGImage	*img = (TGImage*)screen->findChild("cenda");
//	img->bitmap->setFiltering(true);
}

void disableFiltering(TGControl *sender)
{
TGImage	*img = (TGImage*)screen->findChild("cenda");
//	img->bitmap->setFiltering(false);
}

void cendaClicked(TGControl *sender)
{
messageBox("Hello, i am Cenda :-)");
}

void render()
{
//renderOffscreenBSGUIControls();

/*
glClearColor((146.0f/255.0f)*backgnd, (139.0f/255.0f)*backgnd,
(125.0f/255.0f)*backgnd, 1.0f);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glLoadIdentity();

glTranslatef(0.0f, 0.0f, -5.0f);
glRotatef(rotation, 1.0f, 0.0f, 0.0f);
glRotatef(rotation/0.6f, 0.0f, 1.0f, 0.0f);

renderObject();

renderBSGUI();

SDL_GL_SwapBuffers();


progress += 0.008;
}

void initOpenGL()
{
/*
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);
SDL_WM_SetCaption("Bad Sector's OpenGL GUI Demo", "demo");
SDL_ShowCursor(false);

SDL_EnableUNICODE(true);
SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,
SDL_DEFAULT_REPEAT_INTERVAL);

glShadeModel(GL_SMOOTH);
glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
glClearColor(0, 0, 0, 0);
glViewport(0, 0, 800, 600);
glMatrixMode(GL_PROJECTION);
gluPerspective(60.0f, 800.0f/600.0f, 1.0f, 1024.0f);
glMatrixMode(GL_MODELVIEW);

}

void createUI()
{
//TGUI::loadFontData("demo/fontdata.bmp", "demo/fontsize.dat");
//TGUI::loadCursorImage("demo/cursor.bmp", "demo/cursorAlpha.bmp");

TGWindow* win2;

TGProgressBar	*pbar = new TGProgressBar(win2, 10, 330, 175, 355);
pbar->value.setDataSource(&progress);
TGProgressBar	*pbar2 = new TGProgressBar(win2, 10, 360, 175, 385);
pbar2->setName("pbar2");
pbar2->setMax(61);

TGWindow	*win3 = new TGWindow("A window");
win3->center();
win3->move(win3->x1 - 200, win3->y1 - 70);
win3->resize(190, 400);

new TGLabel(win3, 5, 25, "Object resolution:");
stepCount = new TGSlider(win3, 10, 50, 180, 65);
stepCount->setMax(61);
stepCount->setValue(3);
stepCount->modified = new TGCallbackAction(stepsModifiedAction);

new TGLabel(win3, 5, 80, "Object size:");
sizeSlider = new TGSlider(win3, 10, 105, 180, 120);
sizeSlider->setMax(5);
sizeSlider->value.setDataSource(&size);

new TGLabel(win3, 5, 175, "Background intensity:");
backSlider = new TGSlider(win3, 10, 200, 180, 215);
backSlider->setMax(1.0f);
backSlider->value.setDataSource(&backgnd);

TGScrollbox	*sbox = new TGScrollbox(win3, 10, 240, 175, 350);
new TGButton(sbox, 10, 10, 200, 35, "Clipped TGButton");
new TGButton(sbox, 10, 40, 200, 65, "Another clipped TGButton");
new TGCheckbox(sbox, 10, 80, 200, 100, "Clipped checkbox");
new TGLabel(sbox, 10, 120, "Clipped label");


/*
TGWindow	*win4 = new TGWindow("TGModelView control");
win4->center();
win4->move(win4->x1, win4->y1 + 160);

TGModelView	*mview = new TGModelView(win4, 10, 10, 175, 110);
mview->renderView = new TGCallbackAction(renderObjectAction);


TGWindow	*win5 = new TGWindow("TGImage control");
win5->center();
win5->move(win5->x1, win5->y1 - 160);
TGImage	*cenda = new TGImage(win5, 0, 0, "demo/cenda.bmp");
cenda->center();
cenda->setName("cenda");
cenda->clicked = new TGCallbackAction(cendaClicked);
TGPopupMenu	*cendaMenu = new TGPopupMenu;
cendaMenu->addItem("No filtering", new TGCallbackAction(disableFiltering));
cendaMenu->addItem("Bilinear filtering",
new TGCallbackAction(enableFiltering));
cenda->popupMenu = cendaMenu;
win5->resizeable = true;
win5->resized = new TGCallbackAction(imageWinResizedAction);
//win5->icon = new TGBitmap(INTERNALBMP_WINICON);
win5->menu = new TGPopupMenu;
win5->menu->addItem("No filtering",
new TGCallbackAction(disableFiltering));
win5->menu->addItem("Bilinear filtering",
new TGCallbackAction(enableFiltering));

(new TGButton(screen, 750, 5, 795, 30, "Quit"))->clicked =
new TGCallbackAction(terminateAppAction);


TGPopupMenu       *mainMenu = new TGPopupMenu;
mainMenu->addItem("Select file...",
new TGCallbackAction(selectFileAction), NULL);
//new TGBitmap(INTERNALBMP_OPEN));
TGMenuItem	*sub = mainMenu->addItem("Submenu test", NULL);
sub->addItem("Sub menu item 1", NULL);
sub->addItem("Sub menu item 2", NULL);
sub->addItem("Sub menu item 3", NULL);
sub->addItem("-", NULL);
sub->addItem("Sub sub menu", NULL)->addItem("Hello!", NULL);
sub->addItem("Dynamic submenu", NULL)->popup =
new TGCallbackAction(createDynamicSubmenuAction);
mainMenu->addItem("About...", new TGCallbackAction(aboutBoxAction));
mainMenu->addItem("-", NULL);
mainMenu->addItem("Quit", new TGCallbackAction(terminateAppAction),NULL);
//	new TGBitmap(INTERNALBMP_QUIT));

screen1 = screen;
screen2 = new TGScreen();
TGWindow	*nwin = new TGWindow(screen2, "A window in screen 2");
nwin->center();

screen1->popupMenu = screen2->popupMenu = mainMenu;


(new TGButton(screen, 5, 5, 105, 30, "TGScreen 1"))->clicked =
new TGCallbackAction(activateScreen1);
(new TGButton(screen, 110, 5, 210, 30, "TGScreen 2"))->clicked =
new TGCallbackAction(activateScreen2);
(new TGButton(screen2, 5, 5, 105, 30, "TGScreen 1"))->clicked =
new TGCallbackAction(activateScreen1);
(new TGButton(screen2, 110, 5, 210, 30, "TGScreen 2"))->clicked =
new TGCallbackAction(activateScreen2);

fps = new TGLabel(screen1, 5, 40, "?? fps");
}

void runMe()
{
//TGEvent	event;
/*
uint		last = SDL_GetTicks();
float		frames = 0, tenths = 0;

while (running)
{
frames++;
if (SDL_GetTicks() - last > 10)
{
char	buff[128];
rotation += 1;
last = SDL_GetTicks();
tenths++;
float seconds = tenths/100.0f;
sprintf(buff, "%i fps for %i seconds and %i frames",
(int)(frames/seconds), (int)seconds,
(int)frames);
fps->setText(buff);
}
tickBSGUI();
while (SDL_PollEvent(&event))
{
if (!handleSDLEvent(&event))
switch (event.type)
{
case SDL_QUIT:
running = false;
break;
}
}
render();
}

}
*/


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
        TGUI::TGSystem::getSingleton().injectMouseMove( arg.state.relX,arg.state.relY);
        return true;
    }

    //----------------------------------------------------------------//
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
    {
        OIS::MouseState ms = getMouseState();
        TGUI::TGSystem::getSingleton().injectMouseButtonDown(arg.state.relX,arg.state.relY,id);
        return true;
    }

    //----------------------------------------------------------------//
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
    {
        OIS::MouseState ms = getMouseState();
        TGUI::TGSystem::getSingleton().injectMouseButtonUp(arg.state.relX,arg.state.relY,id);
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

    void createFrameListener(void)
    {
        mFrameListener= new DemoListener(mWindow, mCamera);
        mFrameListener->showDebugOverlay(false);
        mRoot->addFrameListener(mFrameListener);
        ms = ((DemoListener*)mFrameListener)->getMouseState();
    }

    bool imageWinResizedAction(const TGEventArgs& args)
    {
        TGImage	*img = (TGImage*)args.m_control->getFirstChild();
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
        (new TGMessagebox("BSGUI (Bad Sector's OpenGL GUI) version 0.2 Demo", "About"))->show();
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
            sub->addItem(lbi->getText(),NULL);
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
        lbox->removeItem(lbox->active);
        return true;
    }

    bool addTheAboveTextAction(const TGEventArgs& args)
    {
        TGScreen* screen = TGSystem::getSingleton().getActiveScreen();

        TGListbox *lbox = (TGListbox*)screen->findChild("listbox");
        lbox->addItem(((TGInputbox*)screen->findChild("inputbox"))->getText());
        ((TGInputbox*)screen->findChild("inputbox"))->setText("");
        screen->findChild("inputbox")->focus();
        return true;
    }

    bool selectFileAction(const TGEventArgs& args)
    {
        TGFileBrowser	*browser = new TGFileBrowser("Select File");
        return true;
    }

    bool configure(void)
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        //if(mRoot->showConfigDialog())
        if(mRoot->restoreConfig())
        {
            mWindow = mRoot->initialise(true);
        }
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

        new TGLabel(win, 5, 0, "A Label");

        new TGButton(win, 10, 55, 180, 80, "Another Button");
        new TGButton(win, 10, 85, 180, 110, "Yet another Button");

        TGWindow	*win2 = new TGWindow("Another fluffy window");
        win2->center();
        win2->move(win2->x1 + 200, win2->y1 - 70);
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

        (new TGInputbox(win2, 10, 270, 175, 295))->setName("inputbox");

        (new TGButton(win2, 10, 300, 175, 325, "Add the above text"))->addEventHandler(
            TGEvent::MouseClicked,new TGEventHandler(&DemoApp::addTheAboveTextAction,this));

        TGPopupMenu       *mainMenu = new TGPopupMenu();
        mainMenu->setName("mainMenu");

        TGMenuItem* mi = mainMenu->addItem("Select file...", NULL);
        mi->addEventHandler(TGEvent::Selected,new TGEventHandler(&DemoApp::selectFileAction,this));
        //new TGBitmap(INTERNALBMP_OPEN));
        TGMenuItem	*sub = mainMenu->addItem("Submenu test", NULL);
        sub->addItem("Sub menu item 1", NULL);
        sub->addItem("Sub menu item 2", NULL);
        sub->addItem("Sub menu item 3", NULL);
        sub->addItem("-", NULL);
        mi = sub->addItem("Sub sub menu", NULL);
        mi->addItem("Hello!", NULL)->setName("Hello!");

        mi = sub->addItem("Dynamic submenu", NULL);
        mi->addItem(" ");
        mi->addEventHandler(TGEvent::MenuPopup,new TGEventHandler(&DemoApp::createDynamicSubmenuAction,this));
        
        mi = mainMenu->addItem("About...");
        mi->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&DemoApp::aboutBoxAction,this));

        mi = mainMenu->addItem("-", NULL);
        //	new TGBitmap(INTERNALBMP_QUIT));
        mi = mainMenu->addItem("Quit");
        mi->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&DemoApp::terminateAppAction,this));


        TGWindow	*win3 = new TGWindow("A window");
        win3->center();
        win3->move(win3->x1 - 200, win3->y1 - 70);
        win3->resize(190, 400);

        new TGLabel(win3, 5, 25, "Object resolution:");
        stepCount = new TGSlider(win3, 10, 50, 180, 65);
        stepCount->setMax(61);
        stepCount->setValue(3);
        stepCount->addEventHandler(TGEvent::Modified, new TGEventHandler(&DemoApp::stepsModifiedAction,this));

        new TGLabel(win3, 5, 80, "Object size:");
        sizeSlider = new TGSlider(win3, 10, 105, 180, 120);
        sizeSlider->setMax(5);
        sizeSlider->value.setDataSource(&size);

        new TGLabel(win3, 5, 175, "Background intensity:");
        backSlider = new TGSlider(win3, 10, 200, 180, 215);
        backSlider->setMax(1.0f);
        backSlider->value.setDataSource(&backgnd);

        TGScrollbox	*sbox = new TGScrollbox(win3, 10, 240, 175, 350);
        new TGButton(sbox, 10, 10, 200, 35, "Clipped TGButton");
        new TGButton(sbox, 10, 40, 200, 65, "Another clipped TGButton");
        new TGCheckbox(sbox,"Clipped checkbox", 10, 80, 200, 100);
        new TGLabel(sbox, 10, 120, "Clipped label");



        screen1 = TGSystem::getSingleton().getActiveScreen();
        screen2 = new TGScreen();
        TGWindow	*nwin = new TGWindow(screen2, "A window in screen 2");
        nwin->center();



        screen1->setPopupMenu(mainMenu);

        /*
        TGControl* l = new TGLabel(screen1, 5, 10, "A Label on the Screen");
        l->setPopupMenu(mainMenu);
        */


        TGWindow	*win5 = new TGWindow("TGImage control");
        //TGColourTheme ct(TGColour(0.2,0.5,0.6,0.75));
        //win5->setColourTheme(ct);

        win5->center();
        win5->move(win5->x1, win5->y1 - 160);
        TGImage	*cenda = new TGImage(win5, 0, 0, "cenda.png");
        cenda->center();
        cenda->setName("cenda");
        cenda->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&DemoApp::cendaClicked,this));

        TGPopupMenu	*cendaMenu = new TGPopupMenu;
        cendaMenu->addItem("No filtering");
        cendaMenu->addItem("Bilinear filtering");
        cenda->setPopupMenu(cendaMenu);
        win5->resizeable = true;
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

        win = new TGWindow("A Test Window");
        win->center();
        win->resizeable = true;
        (new TGCheckbox(win,"Checker", 10, 0, 180, 20))->setState(true);
        new TGCheckbox(win,"Checker 2", 10, 25, 180, 45);
    }

    void createScene(void)
    {
        // setup GUI system

        //TGColourTheme ct(TGColour(0.6,0.2,0.2,0.75),TGColour());
        //TGColourTheme ct(TGColour(0.1,0.6,0.2,0.75),TGColour(0.9,0.9,0,1.0));
        TGColourTheme ct(TGColour(0.2,0.2,0.6,0.75));
        //mGUISystem->setColourTheme(ct);
        mGUISystem = new TGUI::TGSystem(mWindow,mSceneMgr,"Garamond",ct);

        createTest3();
    }

};


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{

    int i =1;
    DemoApp app;

    app.go();

    return 0;
}
