#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiiuse/wpad.h>
#include <string>
#include <fat.h>

#include <grrlib.h>
#include <ogc/isfs.h>
#include <malloc.h>
#include <fstream>


#include "font_ttf.h"
#include "revo-kart/rksys.h"
#include "ui/Button.hpp"
#include "ios/IOSPatch.h"

using namespace std;
void CSV() {
	string csv="License 1;;;;License 2;;;;License 3;;;;License 4\n;;;;\n";
	for (int i = 0; i < 66; ++i)
	{

		for (int j = 0; j < 4; ++j)
		{
			u8* buffer=cbuf(0x2800);
			ReadRKG(j, i, buffer);
			csv+=names[i];
			csv+=";;";
			csv+=getTime(buffer);
			csv+=";;";
			if (j == 3) {
				csv+="\n";
			}
		}
	}
	ofstream _csv("/table.csv");
	_csv << csv;
	_csv.close();
}
int main() {
	IOSPATCH_Apply();
	WPAD_Init();
	GRRLIB_Init();
	ISFS_Initialize();


	GRRLIB_ttfFont *font=GRRLIB_LoadTTF(font_ttf, font_ttf_size);

	//u8* buffer=(u8*)memalign(32, 0x2800);
	//memset(buffer, 0, 0x2800);

	string fdret;


	long long int frame=0;
	int device=fatInitDefault();
	int menu=0;
	int max=1;
	int selected = 0;

	bool enabled=access("/NewerKartWii/data/rkg/lic0/Luigi Circuit.rkg", F_OK) == 0;

	u32 etcColor=enabled?0xDDDDDDFF:0xcFcFcFFF;
	u32 clr=0xffffffff;




	Button exitButton(640/2, 400, 22, "Exit", 22, font, 
		              0xDDDDDDFF, 0x000000ff, 
		              &selected, &menu, WPAD_BUTTON_A ,true, 0, 0);



	Button ghostManager(640/2, 300, 22, "Ghost Manager", 22, font, 
		               0xDDDDDDFF, 0x000000ff, 
		               &selected, &menu, WPAD_BUTTON_A, true, 1, 0);



	Button saveManager(320, 200, 22, "Save Manager", 22, font,
					   0xDDDDDDFF, 0x000000FF,
					   &selected, &menu, WPAD_BUTTON_A, true, 2, 0);



	Button backButtons[2] = {Button(640/2, 400, 22, "Back", 22, font, 
		        					0xDDDDDDFF, 0x000000ff, 
		        					&selected, &menu, WPAD_BUTTON_A ,true, 0, 1),
							 Button(320, 400, 22, "Back", 22, font,
							 		0xDDDDDDFF, 0x000000ff,
							 		&selected, &menu, WPAD_BUTTON_A, true, 0, 2)};



	Button loadGhosts(320, 200, 22, "Load Ghosts", 22, font,
					  0xDDDDDDFF, 0x000000ff,
					  &selected, &menu, WPAD_BUTTON_A, true, 1, 1);



	Button exportToCSV(640/2, 300, 22, "Export To CSV", 22, font, 
		               etcColor, 0x000000ff, 
		               &selected, &menu, WPAD_BUTTON_A, true, 2, 1);



	Button saveGhosts(320, 100, 22, "Save Ghosts", 22, font,
					  0xDDDDDDFF, 0x000000ff,
					  &selected, &menu, WPAD_BUTTON_A, true, 3, 1);



	Button copySave(320, 300, 22, "Copy MKWii Save To NKWii", 22, font,
					0xDDDDDDFF, 0x000000FF,
					&selected, &menu, WPAD_BUTTON_A, true, 1, 2);

	int nkwfd=ISFS_Open("/title/00010004/4a4e4b57/data/rksys.dat", ISFS_OPEN_READ);
	bool nkwExists=nkwfd >= 0;
	ISFS_Close(nkwfd);
	while (true) {
		GRRLIB_FillScreen(clr);
		WPAD_ScanPads();
		

		if (WPAD_ButtonsDown(0) & 0x400) {
			selected=selected>0?selected-1:max;
		}
		if (WPAD_ButtonsDown(0) & 0x800) {
			selected=selected<max?selected+1:0;
		}
		
		
		if ((exitButton.clicked) | (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)) {
			break;
		}
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_B) {
			menu = 0;
		}
		
		exportToCSV._color=enabled?0xDDDDDDFF:0xEDEDEDFF;
		//drawGuides();
		if (menu == 0) {
			exitButton.draw();
			if (ghostManager.clicked) {
				menu = 1;
				selected=0;
			}
			if (saveManager.clicked) {
				menu = 2;
				selected=0;
			}

			ghostManager._enabled=nkwExists;
			ghostManager._text=nkwExists?"Ghost Manager":"No data available.";
			ghostManager.draw();
			saveManager.draw();
			max=2;
		}
		else if (menu == 1) {
			loadGhosts.draw();
			exportToCSV.draw();
			saveGhosts.draw();
			max=enabled?3:2;

			exportToCSV._id=enabled?1:3;
			loadGhosts._id=max-1;
			saveGhosts._id=max;
			if (backButtons[0].clicked) {
				menu = 0;
			}
			
			if (exportToCSV.clicked & enabled) {

				CSV();
			}
			if (loadGhosts.clicked) {
				CopyRKSYS();

				enabled=true;

			}
			if (saveGhosts.clicked) {
				OverwriteRKSYS();
			}
		}
		else {

			max = 1;
			copySave.draw();
			if (copySave.clicked) {
				CopySave();
			}
			if (backButtons[1].clicked) {
				menu = 0;
			}
		}
		if (device < 1) {
			frame=0;
			GRRLIB_PrintfTTF(320-GRRLIB_WidthTTF(font, "Fat Filesystem not initialized. Retrying...", 19)/2, 30, font, "Fat Filesystem not initialized. Retrying...", 19, 0xaa0000ff);
			device=fatInitDefault();
		}
		else {

			frame++;
			if (frame < 60) {
				GRRLIB_PrintfTTF(320-GRRLIB_WidthTTF(font, "Fat Filesystem succesfully initialized.", 19)/2, 30, font, "Fat Filesystem succesfully initialized.", 19, 0x00aa00ff);
				enabled=access("/NewerKartWii/data/rkg/lic0/Luigi Circuit.rkg", F_OK) == 0;
			}
		}

		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_2) {
			enabled=access("/NewerKartWii/data/rkg/lic0/Luigi Circuit.rkg", F_OK) == 0;
			device=fatInitDefault();
			nkwfd=ISFS_Open("/title/00010004/4a4e4b57/data/rksys.dat", ISFS_OPEN_READ);
			nkwExists=nkwfd >= 0;
			ISFS_Close(nkwfd);

		}
		if (menu > 0) {
			backButtons[menu-1].draw();
		}
		exportToCSV._enabled=enabled;
		GRRLIB_Render();
	}
	ISFS_Deinitialize();
	GRRLIB_FreeTTF(font);
	GRRLIB_Exit();
	exit(0);
}
