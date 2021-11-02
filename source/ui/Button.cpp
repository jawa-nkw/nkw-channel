#include "Button.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <grrlib.h>
#include <wiiuse/wpad.h>

using namespace std;
Button::Button(int x, int y, int height, string text, int fontSize, 
	           GRRLIB_ttfFont* font, u32 color, u32 textColor, int* selected, 
	           int* menu, int wpad_button, bool enabled, int id, int menuId) {
    _x=x;
	_y=y;
	_height=height;
	_text=text;
	_fontSize=fontSize;


	_font=font;
	_color=color;
	_textColor=textColor;

	_selected=selected;
	_menu=menu;
	_wpad_button=wpad_button;
	_enabled=enabled;
	_id=id;
	_menuId=menuId;
	ncolor=_color;
	clicked=false;
};
void Button::draw() {
	//frame=frame>32767?0:frame+1;
	int textLen=GRRLIB_WidthTTF(_font, _text.c_str(), _fontSize);
	_width=textLen+textLen/4;
	int xc=_x-_width/2;
	GRRLIB_Rectangle(xc, _y, _width, _height, ncolor, true);
	int sides=(_width-textLen) / 2;
	bool buttonPressed=*Button::pressedMask & _wpad_button;
	bool inBox=(*_selected == _id) & (*_menu == _menuId);
	_textColor=_enabled?0x000000FF:0xB0B0B0FF;
	GRRLIB_PrintfTTF(xc+sides, _y-(_fontSize/10), _font, _text.c_str(), _fontSize, _textColor);

	clicked=buttonPressed & inBox;
	//char bools[128];
	//sprintf(bools, "textLen: %d, text: %s", textLen, _text.c_str());
	//sprintf(bools, "alles: %d, xg: %d, xl: %d, yg: %d, yl: %d, ir->x-200: %d, ir->y-250: %d", inBox, xg, xl, yg, yl, (int)_ir->x, (int)_ir->y);
	//string print=bools;
	//GRRLIB_PrintfTTF(50, 50+textLen, _font, print.c_str(), 22, _textColor);
	ncolor = inBox ? _color-0x1A1A1A00 : _color;
	if (inBox) 
	{
		GRRLIB_Rectangle(xc, _y, _width, _height, 0x000000FF, false);
		WPAD_Rumble(0, 1);
	}


	WPAD_Rumble(0, 0);
	
}

