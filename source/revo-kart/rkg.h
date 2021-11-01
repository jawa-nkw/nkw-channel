#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <sstream>
using namespace std;
string getTime(u8* buffer) {
	string bits;
	for (int i = 0; i < 3; ++i)
	{
		bits+=bitset<8>(buffer[4+i]).to_string();
	}
	string minutes;
	for (int i = 0; i < 7; ++i)
	{
		minutes+=bits[i];
	}
	string seconds;
	for (int i = 0; i < 7; ++i)
	{
		seconds+=bits[7+i];
	}
	string ms;
	for (int i = 0; i < 10; ++i)
	{
		ms+=bits[14+i];
	}
	bitset<7> mbitset;
	istringstream mbits(minutes);
	mbits >>mbitset;
	int m=(int)(mbitset.to_ulong());

	bitset<7> sbitset;
	istringstream sbits(seconds);
	sbits >> sbitset;
	int s=(int)(sbitset.to_ulong());

	bitset<10> msbitset;
	istringstream msbits(ms);
	msbits >> msbitset;
	int mis=(int)(msbitset.to_ulong());
	char time[4096];
	if (s<10) {
		sprintf(time, "%d:0%d.%d", m, s, mis);
	}
	else {
		sprintf(time, "%d:%d.%d", m, s, mis);
	}
	return time;
}