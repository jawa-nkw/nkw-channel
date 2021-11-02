#include <string>
#include <grrlib.h>
#include <wiiuse/wpad.h>
using namespace std;
class Button
{

public:
	int _x;
	int _y;
	int _width;
	int _height;
	string _text;
	int _fontSize;
	GRRLIB_ttfFont* _font;
	u32 _color;
	u32 _textColor;
	bool *_clicked;
	int _wpad_button;
	bool _enabled;
	u32 ncolor;
	int* _selected;
	int* _menu;
	int _menuId;
	int _id;
	int frame=0;
	bool clicked;
	inline static int* pressedMask;

	Button(int x, int y, int height, string text, int fontSize, 
		   GRRLIB_ttfFont* font, u32 color, u32 textColor, int* selected, 
		   int* menu, int wpad_button, bool enabled, int id, int menuId);
	void draw();
};

