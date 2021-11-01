void drawGuides() {
	GRRLIB_Line(640/2, 0, 640/2, 480, 0xff0000ff);
	GRRLIB_Line(0, 240, 640, 240, 0x00ff00ff);
	GRRLIB_Circle(640/2, 240, 3, 0x000000ff, true);
}