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
#include <tgui.h>

namespace TGUI
{

    //-----------------------------------------------------------------------
    //               c a n c e l F i l e B r o w s e r A c t i o n
    //-----------------------------------------------------------------------
    bool TGFileBrowser::cancelFileBrowserAction(const TGEventArgs& args)
    {
        delete args.m_control->m_parent;
        return true;
    }

    //-----------------------------------------------------------------------
    //                c l o s e F i l e B r o w s e r A c t i o n
    //-----------------------------------------------------------------------
    bool TGFileBrowser::closeFileBrowserAction(const TGEventArgs& args)
    {
        TGFileBrowser	*browser = (TGFileBrowser*)args.m_control->m_parent;
        if (browser->filename->getText()[0] == '/')
        {
            string newPath;
            if (!browser->filename->getText().compare("/."))
            {
                browser->reloadFiles();
                return true;
            }
            newPath = browser->path + "/";
            newPath += browser->filename->getText();
            browser->path = newPath;
            browser->reloadFiles();
            return true;
        }
        fireEvent(TGEvent::Selected, TGEventArgs(this));
        delete browser;
        return true;
    }

    //-----------------------------------------------------------------------
    //               s e l e c t F i l e B r o w s e r A c t i o n
    //-----------------------------------------------------------------------
    bool TGFileBrowser::selectFileBrowserAction(const TGEventArgs& args)
    {
        TGFileBrowser	*browser = (TGFileBrowser*)args.m_control->m_parent;
        browser->filename->setText(browser->files->getSelectedItem()->getText());
        return true;
    }

    //-----------------------------------------------------------------------
    //                      T G F i l e B r o w s e r
    //-----------------------------------------------------------------------
    TGFileBrowser::TGFileBrowser(string caption, string path)
        : TGWindow(caption)
    {
        int	w, h;
        TGLabel	*l;
        TGButton	*b;
        resize(500, 300);
        center();
        if(path.empty())
            path = ".";
        this->path = path;

        getClientSize(w, h);

        l = new TGLabel(this,"Files and directories:",5,5);
        files = new TGListbox(this, 5, l->y2 + 5, w-10, h-40);
        files->addEventHandler(TGEvent::Modified,new TGEventHandler(&TGFileBrowser::selectFileBrowserAction,this));
        l = new TGLabel(this,"Filename:", 5, files->y2+9);
        filename = new TGEditbox(this, l->x2 + 5, files->y2 + 5, w-130,
            files->y2 + 30);
        b = new TGButton(this, w-125, files->y2 + 5, w-70, files->y2 + 30, "Ok");
        b->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&TGFileBrowser::closeFileBrowserAction,this));
        b = new TGButton(this, w-65, files->y2 + 5, w-10, files->y2+30, "Cancel");
        b->addEventHandler(TGEvent::MouseClicked,new TGEventHandler(&TGFileBrowser::cancelFileBrowserAction,this));

        reloadFiles();

        makeExclusive();
    }

    //-----------------------------------------------------------------------
    //                     ~ T G F i l e B r o w s e r
    //-----------------------------------------------------------------------
    TGFileBrowser::~TGFileBrowser()
    {
    }

    //-----------------------------------------------------------------------
    //                         g e t F i l e n a m e
    //-----------------------------------------------------------------------
    string TGFileBrowser::getFilename()
    {
        string fname;
        fname = path+"/"+filename->getText();
        return fname;
    }

    //-----------------------------------------------------------------------
    //                         r e l o a d F i l e s
    //-----------------------------------------------------------------------
    void TGFileBrowser::reloadFiles()
    {
        /*
        struct dirent	*dent;
        DIR		*dir;
        files->removeAllChildren();

        dir = opendir(path);
        while ((dent = readdir(dir)))
        {
        DIR	*dir2 = opendir(dent->d_name);
        if (dir2)
        {
        char	*buff = (char*)MALLOC(strlen(dent->d_name)+2);
        closedir(dir2);
        sprintf(buff, "/%s", dent->d_name);
        files->addItem(buff);
        FREE(buff);
        }
        else
        files->addItem(dent->d_name);
        }
        closedir(dir);
        files->layout();

        files->selectItem((unsigned int)0);

        if (files->active)
        filename->setText(files->active->text);
        else
        filename->setText("");
        */
    }
}