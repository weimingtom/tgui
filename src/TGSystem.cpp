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
#include <tgui.h>

static const struct {
    unsigned int 	 width;
    unsigned int 	 height;
    unsigned int 	 bytes_per_pixel; /* 3:RGB, 4:RGBA */ 
    unsigned char	 pixel_data[32 * 32 * 4];
} _defCursor_ = {
    32, 32, 4,
    "\1\1\1\255\1\1\1\254\1\1\1\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\260\15\15\15\376\1\1\1"
    "\334\1\1\1""3\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\1\1\1\263edd\364][[\361\4\4\4\367\1\1\1k\1\1\1\1\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\265ig"
    "g\364\271\266\266\343\206\204\204\342\21\21\21\372\1\1\1\251\1\1\1\17\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\270kii\364\271"
    "\266\266\343\271\266\266\330\246\243\243\321+**\357\1\1\1\332\1\1\1""1\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\273mkk\363\271\266\266"
    "\343\271\266\266\330\271\266\266\315\267\264\264\302POO\333\3\3\3\366\1\1"
    "\1g\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\276omm\363\271\266\266\343"
    "\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266\266{yy\301\15"
    "\15\15\366\1\1\1\246\1\1\1\15\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\301qoo\363\271"
    "\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266"
    "\266\271\266\266\253\237\234\234\252!!!\344\1\1\1\330\1\1\1/\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\1\1\1\303sqq\363\271\266\266\343\271\266\266\330\271\266\266\315\271"
    "\266\266\302\271\266\266\266\271\266\266\253\271\266\266\240\265\262\262"
    "\227BAA\306\2\2\2\364\1\1\1d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\306uss\363\271\266\266\343\271"
    "\266\266\330\271\266\266\315\271\266\266\302\271\266\266\266\271\266\266"
    "\253\271\266\266\240\271\266\266\225\271\266\266\212kii\242\11\11\11\362"
    "\1\1\1\242\1\1\1\14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\1\1\1\311wuu\363\271\266\266\343\271\266\266\330\271\266\266\315"
    "\271\266\266\302\271\266\266\266\271\266\266\253\271\266\266\240\271\266"
    "\266\225\271\266\266\212\271\266\266\177\224\222\222\202\30\30\30\332\1\1"
    "\1\326\1\1\1,\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1"
    "\1\314yww\362\271\266\266\343\271\266\266\330\271\266\266\315\271\266\266"
    "\302\271\266\266\266\271\266\266\253\271\266\266\240\271\266\266\225\271"
    "\266\266\212\271\266\266\177\271\266\266t\262\257\257k100\262\2\2\2\363\1"
    "\1\1a\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\317{yy\362\271"
    "\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266"
    "\266\271\266\266\253\271\266\266\240\271\266\266\225\271\266\266\212\271"
    "\266\266\177\271\266\266t\271\266\266i\271\266\266^UTT\204\6\6\6\357\1\1"
    "\1\237\1\1\1\13\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\321}{{\362\271\266\266"
    "\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266\266\271"
    "\266\266\253\271\266\266\240\271\266\266\225\271\266\266\212\271\266\266"
    "\177\271\266\266t\271\266\266i\271\266\266^\271\266\266S\201\177\177\\\16"
    "\16\16\321\1\1\1\323\1\1\1*\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\324\177}}\362\271"
    "\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266"
    "\266\271\266\266\253\271\266\266\240\271\266\266\225\271\266\266\212\271"
    "\266\266\177\271\266\266t\271\266\266i\271\266\266^\271\266\266S\271\266"
    "\266H\253\250\250@\34\34\34\237\1\1\1\361\1\1\1]\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\327"
    "\202\177\177\362\271\266\266\343\271\266\266\330\271\266\266\315\271\266"
    "\266\302\271\266\266\266\271\266\266\253\271\266\266\240\271\266\266\225"
    "\271\266\266\212\271\266\266\177\271\266\266t\271\266\266i\271\266\266^\271"
    "\266\266S\271\266\266H\271\266\266<\271\266\2661322g\3\3\3\355\1\1\1\234"
    "\1\1\1\12\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\1\1\1\332\204\202\202\362\271\266\266\343\271\266\266\330\271\266"
    "\266\315\271\266\266\302\271\266\266\266\271\266\266\253}{{\267MKK\305ED"
    "D\302>==\277666\275///\273(((\272\"!!\272\34\34\34\271\26\26\26\272\21\21"
    "\21\273\15\14\14\274\5\5\5\326\1\1\1\377\1\1\1\321\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\335\206\204\204"
    "\361\271\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271"
    "\266\266\266\244\241\241\263\13\13\13\367\1\1\1\263\1\1\1\242\1\1\1\234\1"
    "\1\1\226\1\1\1\220\1\1\1\212\1\1\1\204\1\1\1~\1\1\1x\1\1\1r\1\1\1l\1\1\1"
    "f\1\1\1`\1\1\1Y\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\1\1\1\337\210\206\206\361\271\266\266\343\271\266\266\330"
    "\271\266\266\315\271\266\266\302\271\266\266\267211\343\1\1\1\257\1\1\1\1"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\342\212\210\210\361\271\266\266\343"
    "\271\266\266\330\271\266\266\315\271\266\266\302rpp\316\1\1\1\356\1\1\1\32"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\345\214\212\212\361\271\266"
    "\266\343\271\266\266\330\271\266\266\315\251\246\246\306\17\17\17\370\1\1"
    "\1`\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\350\216\214\214"
    "\361\271\266\266\343\271\266\266\330\271\266\266\315;;;\351\1\1\1\267\1\1"
    "\1\1\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\27\1\1\1q\1\1\1\237\1\1\1\233\1\1\1d\1"
    "\1\1\14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\352\220\216"
    "\216\361\271\266\266\343\271\266\266\330|zz\334\2\2\2\360\1\1\1\36\0\0\0"
    "\0\0\0\0\0\0\0\0\0\1\1\1Y\5\1\1\361U\1\1\377\221\0\0\377\213\0\0\377C\1\1"
    "\377\2\1\1\343\1\1\1:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\355\222"
    "\220\220\361\271\266\266\343\255\252\252\332\23\23\23\371\1\1\1h\0\0\0\0"
    "\0\0\0\0\0\0\0\0\1\1\1F\22\1\1\374\304\0\0\377\377\0\0\377\377\0\0\377\377"
    "\0\0\377\377\0\0\377\245\0\0\377\5\1\1\360\1\1\1%\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\1\1\1\360\225\222\222\360\271\266\266\343EDD\360\1\1\1\275\1\1\1"
    "\2\0\0\0\0\0\0\0\0\1\1\1\1\1\1\1\325\245\0\0\377\377\0\0\377\377\0\0\377"
    "\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377x\0\0\377\1\1\1\251\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\363\227\224\224\360\205\203\203\353\2\2"
    "\2\363\1\1\1#\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1*\26\1\1\377\373\0\0\377\377\0"
    "\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\342\0"
    "\0\377\3\1\1\365\1\1\1\10\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\366\220\216\216\361"
    "\30\30\30\374\1\1\1o\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1J9\1\1\377\377"
    "\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377"
    "\0\0\377\376\0\0\377\16\1\1\377\1\1\1\36\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\370"
    "322\373\1\1\1\304\1\1\1\3\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1:&\1\1\377"
    "\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377"
    "\377\0\0\377\362\0\0\377\6\1\1\375\1\1\1\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1"
    "\373\1\1\1\366\1\1\1(\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\10\2"
    "\1\1\360\321\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377"
    "\0\0\377\377\0\0\377\245\0\0\377\1\1\1\313\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\1\1\1\376\1\1\1w\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\1\1\1|8\1\1\377\363\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0"
    "\0\377\342\0\0\377\34\1\1\376\1\1\1P\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1"
    "\1\312\1\1\1\4\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1"
    "\1\1\4\1\1\1\251+\1\1\377\252\0\0\377\346\0\0\377\340\0\0\377\230\0\0\377"
    "\31\1\1\376\1\1\1\201\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1-\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1"
    "\2\1\1\1_\1\1\1\306\1\1\1\364\1\1\1\360\1\1\1\271\1\1\1F\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
};

template<> TGUI::TGSystem* TGSingleton<TGUI::TGSystem>::ms_Singleton = 0;
namespace TGUI
{

    void TGResourceLoader::loadResource(Ogre::Resource* resource)
    {
        int i = 0;

    }

    //-----------------------------------------------------------------------
    //                             T G S y s t e m
    //-----------------------------------------------------------------------
    TGSystem::TGSystem(Ogre::RenderWindow* window, Ogre::SceneManager* sceneMgr,TGString defaultFont) : m_currentFont(NULL), m_defaultFont(NULL)
    {
        m_activeScreen = 0;
        m_childUnderMouse = 0;
        m_lastChildUnderMouse = 0;
        m_currentFont = 0;
        m_trackControl = 0;
        m_keyboardFocusControl = 0;
        m_logger = 0;
        m_activePopup = 0;
        m_eventHook = 0;

        m_version = Ogre::StringConverter::toString(TGUI_VERSION_MAJOR) + "." +
            Ogre::StringConverter::toString(TGUI_VERSION_MINOR) + "." +
            " (" + TGUI_VERSION_NAME + ")";

        m_renderer = new TGUI::TGRenderer(window, 
            Ogre::RENDER_QUEUE_OVERLAY, false, sceneMgr);

        createDefaultCursor();

        m_texture = m_renderer->createTexture();

        // Create the texture
        Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
            "GUIDefaultTexture", // name
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            Ogre::TEX_TYPE_2D,      // type
            2, 2,         // width & height
            0,                // number of mipmaps
            Ogre::PF_BYTE_BGRA,     // pixel format
            Ogre::TU_DEFAULT
            );      // usage; should be TU_DYNAMIC_WRITE_ONLY_DISCARDABLE for
        // textures updated very often (e.g. each frame)

        // Get the pixel buffer
        Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();

        // Lock the pixel buffer and get a pixel box
        pixelBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
        const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

        Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);

        for(size_t i = 0; i < 4; i++)
        {
            *pDest++ = 255; // B
            *pDest++ = 255; // G
            *pDest++ = 255; // R
            *pDest++ = 255; // A
        }
        // Unlock the pixel buffer
        pixelBuffer->unlock();

        m_texture->setOgreTexture(texture);
        m_logger = new TGLogger();

        m_currentTheme = TGTheme();
        pushTheme(&m_currentTheme);

        m_defaultFont = new TGFont(defaultFont);
        m_defaultFont->setHeight(18);
        setCurrentFont(m_defaultFont);

        m_currentTheme.setFont(m_defaultFont);

        m_defaultScreen = new TGScreen();
        m_defaultScreen->activate();

    }

    //-----------------------------------------------------------------------
    //                            ~ T G S y s t e m
    //-----------------------------------------------------------------------
    TGSystem::~TGSystem()
    {
        if(m_defaultFont)
            delete m_defaultFont;

        if(m_defaultCursor)
            delete m_defaultCursor;

        if(m_defaultScreen)
            delete m_defaultScreen;

        if(m_renderer)
            delete m_renderer;

        if(m_logger)
            delete m_logger;

        if(m_eventHook)
            delete m_eventHook;
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------

    TGSystem* TGSystem::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TGSystem& TGSystem::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //              s e t K e y b o a r d F o c u s C o n t r o l
    //-----------------------------------------------------------------------
    void TGSystem::setKeyboardFocusControl(TGControl *control)
    {
        m_keyboardFocusControl = control;
    }

    //-----------------------------------------------------------------------
    //                    h a s K e y b o a r d F o c u s
    //-----------------------------------------------------------------------
    bool TGSystem::hasKeyboardFocus(TGControl *control)
    {
        return (m_keyboardFocusControl == control) && (control->focused());
    }

    //-----------------------------------------------------------------------
    //                  i n v a l i d a t e C o n t r o l
    //-----------------------------------------------------------------------
    void TGSystem::invalidateControl(TGControl *control)
    {
        if (m_lastChildUnderMouse == control)
            m_lastChildUnderMouse = NULL;
        if (m_keyboardFocusControl == control)
            m_keyboardFocusControl = NULL;
    }

    //-----------------------------------------------------------------------
    //                      i n j e c t M o u s e M o v e
    //-----------------------------------------------------------------------
    void TGSystem::injectMouseMove(int relX, int relY)
    {
        if(!m_activeScreen)
            return;

        int absX=relX,absY=relY;
        if(m_mouseCursor)
        {
            m_mouseCursor->move(m_mouseCursor->x1+relX,
                m_mouseCursor->y1+relY);
            absX = m_mouseCursor->x1;
            absY = m_mouseCursor->y1;
        }

        if(m_activeScreen)
        {
            m_activeScreen->setMouseX(absX);
            m_activeScreen->setMouseY(absY);
        }

        if (m_trackControl)
        {
            m_trackControl->onMouseMoved(absX,absY);
        }
        if (m_activeScreen->m_exclusiveChild)
            m_childUnderMouse = m_activeScreen->m_exclusiveChild->childAt(absX,absY);
        else
            m_childUnderMouse = m_activeScreen->childAt(absX,absY);

        if (m_lastChildUnderMouse != m_childUnderMouse)
        {
            if (m_lastChildUnderMouse)
                m_lastChildUnderMouse->onMouseExit(absX, absY);
            m_lastChildUnderMouse = m_childUnderMouse;

            m_childUnderMouse->onMouseEnter();
        }
        m_childUnderMouse->onMouseMoved(absX,absY);

    }

    //-----------------------------------------------------------------------
    //                 i n j e c t M o u s e B u t t o n D o w n
    //-----------------------------------------------------------------------
    void TGSystem::injectMouseButtonDown(int relX, int relY, int buttonID)
    {
        if(!m_activeScreen)
            return;

        int absX=relX,absY=relY;
        if(m_mouseCursor)
        {
            m_mouseCursor->move(m_mouseCursor->x1+relX,
                m_mouseCursor->y1+relY);
            absX = m_mouseCursor->x1;
            absY = m_mouseCursor->y1;
        }

        if(m_activeScreen)
        {
            m_activeScreen->setMouseX(absX);
            m_activeScreen->setMouseY(absY);
        }

        if (m_trackControl)
        {
            m_trackControl->onMouseDown(absX,absY,buttonID);
            return;
        }
        if (m_activeScreen->m_exclusiveChild)
        {
            int	x1, y1, x2, y2;
            m_activeScreen->m_exclusiveChild->getBounds(x1, y1, x2,
                y2);
            if (!(absX >= x1 && absX <= x2
                && absY >= y1 &&
                absY <= y2))
                return;
            m_childUnderMouse = m_activeScreen->m_exclusiveChild->childAt(absX,absY);
        }
        else
        {
            m_childUnderMouse = m_activeScreen->childAt(absX,absY);
        }

        if(m_activePopup && (m_childUnderMouse != m_activePopup))
        {
            if(m_childUnderMouse->getControlType().compare("TGMenuItem"))
            {
                m_activePopup->cancelRoot();
                m_activePopup = NULL;
            }
        }

        m_childUnderMouse->onMouseDown(absX,absY,buttonID);
    }

    //-----------------------------------------------------------------------
    //                   i n j e c t M o u s e B u t t o n U p 
    //-----------------------------------------------------------------------
    void TGSystem::injectMouseButtonUp(int relX, int relY, int buttonID)
    {
        if(!m_activeScreen)
            return;

        int absX=relX,absY=relY;
        if(m_mouseCursor)
        {
            m_mouseCursor->move(m_mouseCursor->x1+relX,
                m_mouseCursor->y1+relY);
            absX = m_mouseCursor->x1;
            absY = m_mouseCursor->y1;
        }

        if(m_activeScreen)
        {
            m_activeScreen->setMouseX(absX);
            m_activeScreen->setMouseY(absY);
        }

        if (m_trackControl)
        {
            m_trackControl->onMouseUp(absX,absY,buttonID);
            return;
        }
        if (m_activeScreen->m_exclusiveChild)
            m_childUnderMouse = m_activeScreen->m_exclusiveChild->childAt(absX,absY);
        else
            m_childUnderMouse = m_activeScreen->childAt(absX,absY);

        if(m_childUnderMouse)
            m_childUnderMouse->onMouseUp(absX,absY,buttonID);
    }

    //-----------------------------------------------------------------------
    //                    i n j e c t T i m e P u l s e
    //-----------------------------------------------------------------------
    void TGSystem::injectTimePulse(TGReal timeElapsed)
    {
        if(m_activeScreen)
            m_activeScreen->pulse(timeElapsed);
    }


    //-----------------------------------------------------------------------
    //                        i n j e c t K e y D o w n
    //-----------------------------------------------------------------------
    void TGSystem::injectKeyDown(int key,unsigned char ascii)
    {
        if(!m_activeScreen)
            return;

        if (!(m_keyboardFocusControl &&
            m_keyboardFocusControl->focused()))
            return;

        m_keyboardFocusControl->onKeyDown(key,ascii);
    }

    //-----------------------------------------------------------------------
    //                         i n j e c t K e y U p
    //-----------------------------------------------------------------------
    void TGSystem::injectKeyUp(int key,unsigned char ascii)
    {
        if(!m_activeScreen)
            return;

        if (!(m_keyboardFocusControl &&
            m_keyboardFocusControl->focused()))
            return;

        m_keyboardFocusControl->onKeyUp(key,ascii);
    }

    //-----------------------------------------------------------------------
    //                          l o a d F o n t
    //-----------------------------------------------------------------------
    TGFont* TGSystem::loadFont(TGString fontName,TGString resourceGroup)
    {

        TGFont*     font;
        font = new TGFont(fontName,resourceGroup);
        return font;
    }

    //-----------------------------------------------------------------------
    //                     s e t M o u s e C u r s o r
    //-----------------------------------------------------------------------
    void TGSystem::setMouseCursor(TGCursor* cursor)
    {
        m_mouseCursor = cursor;
        int x = (m_renderer->getWidth()/2) - (cursor->getImageWidth()/2);
        int y = (m_renderer->getHeight()/2) - (cursor->getImageHeight()/2);
        m_mouseCursor->move(x,y);
        if(m_activeScreen)
        {
            m_activeScreen->setMouseX(x);
            m_activeScreen->setMouseY(y);
        }
    }

    //-----------------------------------------------------------------------
    //                 c r e a t e D e f a u l t C u r s o r 
    //-----------------------------------------------------------------------
    void TGSystem::createDefaultCursor()
    {

        TGTexture* ctexture = m_renderer->createTexture();

        // Create the texture
        Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
            "GUIDefaultCursorTexture", // name
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            Ogre::TEX_TYPE_2D,      // type
            32, 32,         // width & height
            0,                // number of mipmaps
            Ogre::PF_BYTE_RGBA,     // pixel format
            Ogre::TU_DEFAULT);      // usage; should be TU_DYNAMIC_WRITE_ONLY_DISCARDABLE for
        // textures updated very often (e.g. each frame)

        // Get the pixel buffer
        Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();

        // Lock the pixel buffer and get a pixel box
        pixelBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
        const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

        Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);
        const unsigned char* pSrc  = _defCursor_.pixel_data;

        // Fill in some pixel data. This will give a semi-transparent blue,
        // but this is of course dependent on the chosen pixel format.
        for(size_t y = 0; y < _defCursor_.height; y++)
        {
            for(size_t x = 0; x < _defCursor_.width; x++)
            {
                unsigned char r,g,b,a;
                r = *pSrc++; g = *pSrc++; b = *pSrc++; a=*pSrc++;

                *pDest++ = b;
                *pDest++ = g;
                *pDest++ = r;
                *pDest++ = a;
            }
        }

        // Unlock the pixel buffer
        pixelBuffer->unlock();
        ctexture->setOgreTexture(texture);
        m_defaultCursor = new TGCursor(ctexture);
        setMouseCursor(m_defaultCursor);

    }

    //-----------------------------------------------------------------------
    //                          s e t T h e m e
    //-----------------------------------------------------------------------
    void TGSystem::setTheme(TGTheme theme,bool updateChildren) 
    {
        m_currentTheme = theme;
    }

    //-----------------------------------------------------------------------
    //                          p u s h T h e m e
    //-----------------------------------------------------------------------
    void TGSystem::pushTheme(TGTheme* theme)
    {

        setTheme(*theme);
        m_themeStack.push_front(theme);
    }

    //-----------------------------------------------------------------------
    //                          p o p T h e m e
    //-----------------------------------------------------------------------
    TGTheme* TGSystem::popTheme()
    {
        TGTheme* ctheme = *m_themeStack.begin();

        m_themeStack.pop_front();

        setTheme(**(m_themeStack.begin()));        
        
        return ctheme;
    }

    //-----------------------------------------------------------------------
    //                           s e t L o g g e r
    //-----------------------------------------------------------------------
    void TGSystem::setLogger(TGLogger* logger)
    {
        if(m_logger)
            delete m_logger;

        m_logger = logger;
    }

    //-----------------------------------------------------------------------
    //                           g e t L o g g e r
    //-----------------------------------------------------------------------
    TGLogger* TGSystem::getLogger()
    {
        return m_logger;
    }

    //-----------------------------------------------------------------------
    //                       g e t C u r s o r P o s
    //-----------------------------------------------------------------------
    void TGSystem::getCursorPos(int& x, int& y)
    {
        x = y = 0;
        if(m_mouseCursor)
        {
            x = m_mouseCursor->x1 + m_mouseCursor->getHotSpot().x;
            y = m_mouseCursor->y1 + m_mouseCursor->getHotSpot().y;
        }
    }

    //-----------------------------------------------------------------------
    //                           l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TGSystem::logMessage(TGString message)
    {
        if(m_logger)
            m_logger->logMessage(message);
    }

    //-----------------------------------------------------------------------
    //                      d e s t r o y C o n t r o l
    //-----------------------------------------------------------------------
    void TGSystem::destroyControl(TGControl *control)
    {
        m_dead.push_back(control);
    }

    //-----------------------------------------------------------------------
    //                       s e t E v e n t H o o k
    //-----------------------------------------------------------------------
    TGEventHandler* TGSystem::setEventHook(TGEventHandler* hook)
    {
        TGEventHandler* oldHook = m_eventHook;
        m_eventHook = hook;
        return oldHook;
    }

    //-----------------------------------------------------------------------
    //                          e v e n t H o o k
    //-----------------------------------------------------------------------
    bool TGSystem::eventHook(TGEventArgs& args)
    {
        if(m_eventHook)
            return (*m_eventHook)(args);
        return false;
    }

    //-----------------------------------------------------------------------
    //                        a d d M o d i f i e r
    //-----------------------------------------------------------------------
    void TGSystem::addModifier(TGModifier* mod)
    {

        m_modifiers.push_back(mod);

    }

    //-----------------------------------------------------------------------
    //                 g e t M o u s e C o o r d i n a t e s
    //-----------------------------------------------------------------------
    void TGSystem::getMouseCoordinates(int& x, int& y)
    {
        x = y = 0;
        if(m_mouseCursor)
        {
            x = m_mouseCursor->x1 + m_mouseCursor->getHotSpot().x;
            y = m_mouseCursor->y1 + m_mouseCursor->getHotSpot().y;
        }
    }

    //-----------------------------------------------------------------------
    //                     r e m o v e M o d i f i e r
    //-----------------------------------------------------------------------
    void TGSystem::removeModifier(TGModifier* mod)
    {


    }

    //-----------------------------------------------------------------------
    //                          r e n d e r G U I
    //-----------------------------------------------------------------------
    void TGSystem::renderGUI()
    {
        m_cache.clear();

        m_renderer->resetZValue();
        if (m_activeScreen)
        {
            m_activeScreen->render();
        }

        m_renderer->doRender(m_cache);

        // draw mouse
        if(m_mouseCursor)
        {
            m_mouseCursor->draw();
        }

        for(size_t i=0; i < m_dead.size(); i++)
        {
            TGControl* control = m_dead.back();
            delete control;
            m_dead.pop_back();
        }
    }

}

