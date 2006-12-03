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
#ifndef __TGUI_H__
#define __TGUI_H__

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#ifdef DELETE
#undef DELETE
#endif
#endif

#include <ogre.h>
#include <ogrefont.h>
#include <ogrefontmanager.h>

namespace TGUI
{
#define TGSingleton Ogre::Singleton
    typedef Ogre::uint	 uint;
    typedef Ogre::uint32 uint32;
    typedef Ogre::ushort ushort;
#define LeftButton 0
#define RightButton 1
#define MiddleButton 2
}

using std::string;

#include <tglogger.h>
#include <tgcolour.h>
#include <tgcolourtheme.h>
#include <tgvector.h>
#include <tgrect.h>
#include <tgrenderer.h>
#include <tgtexture.h>
#include <tgfont.h>
#include <tgevents.h>
#include <tgdataman.h>
#include <tgcontrol.h>
#include <tgscreen.h>
#include <tgimage.h>
#include <tgcursor.h>
#include <tgwindow.h>
#include <tglabel.h>
#include <tgbutton.h>
#include <tgcheckbox.h>
#include <tgslider.h>
#include <tgscrollbox.h>
#include <tglistbox.h>
#include <tginputbox.h>
#include <tgfilebrowser.h>
#include <tgmessagebox.h>
#include <tgmenu.h>
#include <tgprogressbar.h>
#include <tgthememanager.h>
#include <tgsystem.h>

#endif
