#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;


string toHex(string s, bool upper) {
    string hex;
    string uppercase=upper?"%X":"%x";
    for (char c : s) {
        char hxchr[2];
        sprintf(hxchr, uppercase.c_str(), c);
        hex += hxchr;
    }
    return hex;
}
u8* cbuf(unsigned int size) {
    u8* buf=(u8*)memalign(32, size);
    memset(buf, 0, size);
    return buf;
}
char names[66][64]=
{
    "Luigi Circuit",
    "Moo Moo Meadows",
    "Mushroom Gorge",
    "Toad's Factory",
    "Mario Circuit",
    "Coconut Mall",
    "DK Summit",
    "Wario's Gold Mine",
    "Daisy Circuit",
    "Koopa Cape",
    "Grumble Volcano",
    "Maple Treeway",
    "Moonview Highway",
    "Dry Dry Ruins",
    "Bowser's Castle",
    "Rainbow Road",
    "GBA Shy Guy Beach",
    "SNES Ghost Valley 2",
    "SNES Mario Circuit 3",
    "GBA Bowser Castle 3",
    "N64 Sherbet Land",
    "N64 Mario Raceway",
    "N64 DK's Jungle Parkway",
    "N64 Bowser's Castle",
    "GCN Peach Beach",
    "GCN Mario Circuit",
    "GCN Waluigi Stadium",
    "GCN DK Mountain",
    "DS Yoshi Falls",
    "DS Desert Hills",
    "DS Peach Gardens",
    "DS Delfino Square",
    "Downloaded Ghost Data Slot 1",
    "Downloaded Ghost Data Slot 2",
    "Downloaded Ghost Data Slot 3",
    "Downloaded Ghost Data Slot 4",
    "Downloaded Ghost Data Slot 5",
    "Downloaded Ghost Data Slot 6",
    "Downloaded Ghost Data Slot 7",
    "Downloaded Ghost Data Slot 8",
    "Downloaded Ghost Data Slot 9",
    "Downloaded Ghost Data Slot 10",
    "Downloaded Ghost Data Slot 11",
    "Downloaded Ghost Data Slot 12",
    "Downloaded Ghost Data Slot 13",
    "Downloaded Ghost Data Slot 14",
    "Downloaded Ghost Data Slot 15",
    "Downloaded Ghost Data Slot 16",
    "Downloaded Ghost Data Slot 17",
    "Downloaded Ghost Data Slot 18",
    "Downloaded Ghost Data Slot 19",
    "Downloaded Ghost Data Slot 20",
    "Downloaded Ghost Data Slot 21",
    "Downloaded Ghost Data Slot 22",
    "Downloaded Ghost Data Slot 23",
    "Downloaded Ghost Data Slot 24",
    "Downloaded Ghost Data Slot 25",
    "Downloaded Ghost Data Slot 26",
    "Downloaded Ghost Data Slot 27",
    "Downloaded Ghost Data Slot 28",
    "Downloaded Ghost Data Slot 29",
    "Downloaded Ghost Data Slot 30",
    "Downloaded Ghost Data Slot 31",
    "Downloaded Ghost Data Slot 32",
    "Last downloaded Ghost Race ghost",
    "Last Compatibile competition"
};