
#include <stdio.h>
#include <stdlib.h>
#include <grrlib.h>
#include <wiiuse/wpad.h>

#include "Label.hpp"
using namespace std;
Label::Label(int x, int y, string text, int fontSize, 
		     GRRLIB_ttfFont* font, u32 color) {
	_x=x;
	_y=y;
	_text=text;
	_fontSize=fontSize;


	_font=font;
	_color=color;
}
void Label::draw() {
		int textLen=GRRLIB_WidthTTF(_font, _text.c_str(), _fontSize);
		int xc=_x-textLen/2;
		GRRLIB_PrintfTTF(xc, _y, _font, _text.c_str(), _fontSize, _color);


}