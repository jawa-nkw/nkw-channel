#include <string>
#include <grrlib.h>
#include <wiiuse/wpad.h>
using namespace std;
class Label {
public:
	u64 frame;
	int _width;
	int _x;
	int _y;
	int _height;
	string _text;
	int _fontSize;
	GRRLIB_ttfFont* _font;
	u32 _color;
	Label (int x, int y, string text, int fontSize, 
		   GRRLIB_ttfFont* font, u32 color);
	void draw();
};