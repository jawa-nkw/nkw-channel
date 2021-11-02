#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ogc/isfs.h>
#include <fstream>
#include <malloc.h>
#include "val.h"
#include "rkg.h"


class RKSYS {
public:
	struct RKG_DataBlock {
		static const int topLeft=0x28000;
		static const int topRight=0xCD000;
		static const int bottomLeft=0x172000;
		static const int bottomRight=0x217000;
		static const int length=topRight-topLeft;
		static constexpr int licenses[4]={topLeft, topRight, bottomLeft, bottomRight};
	};
	struct RKPD {
		static const int length=0x8CC0;
		static const int topLeft=0x8;
		static const int topRight=0x8CC8;
		static const int bottomLeft=0x11988;
		static const int bottomRight=0x1A648;
	};
	struct RKG {
		static const int length=0x2800;
	};
};
void CopyRKSYS() 
{
	int fd;
	u8* buffer;
	fd=ISFS_Open("/title/00010004/4a4e4b57/data/rksys.dat", ISFS_OPEN_READ);
	buffer=(u8*)memalign(32, 0x2BC000);
	memset(buffer, 0, 0x2BC000);
	ISFS_Read(fd, buffer, 0x2BC000);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 66; ++j)
		{
			u8 data[0x2800];
			for (int k = 0; k < 0x2800; ++k)
			{
			    data[k]=buffer[RKSYS::RKG_DataBlock::licenses[i]+(0x2800*j)+k];
			}
			char fn[4256];
			sprintf(fn, "/NewerKartWii/data/rkg/lic%d/%s.rkg", i, names[j]);
			FILE *rkg=fopen(fn, "wb");
			fwrite(data, sizeof(u8), 0x2800, rkg);
			fclose(rkg);
		}
	}
}
string ReadRKG(int lic, int j, u8* buf) {
	char fn[4608];
	sprintf(fn, "/NewerKartWii/data/rkg/lic%d/%s.rkg", lic, names[j]);
	FILE *rkg=fopen(fn, "rb");
	fread(buf, sizeof(u8), 0x2800, rkg);
	fclose(rkg);
	return fn;
}
int OverwriteRKSYS() 
{
	
	u8* buffer=cbuf(0x28000);
	int fd;
	fd=ISFS_Open("/title/00010004/4a4e4b57/data/rksys.dat", ISFS_OPEN_RW);
	ISFS_Read(fd, buffer, 0x28000);
	ISFS_Close(fd);
	u8* chunk=cbuf(0x294000);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 66; ++j)
		{
			u8 buffer[0x2800];
			ReadRKG(i, j, buffer);
			for (int k = 0; k < 0x2800; ++k)
			{
				
				chunk[(i*0xA5000) + (j*0x2800) + k]=buffer[k];
			}
		}
	}
	u8* rksys=cbuf(0x2BC000);
	for (int i = 0; i < 0x28000; ++i)
	{
		rksys[i]=buffer[i];
	}
	for (int i = 0; i < 0x294000; ++i)
	{
		rksys[i+0x28000]=chunk[i];
	}
	fd=ISFS_Open("/title/00010004/4a4e4b57/data/rksys.dat", ISFS_OPEN_WRITE);
	int ret=ISFS_Write(fd, rksys, 0x2BC000);
	return ret;
	//FILE *fp=fopen("chunk.rkgd", "wb");
	//fwrite(rksys, sizeof(u8), 0x2BC000, fp);
	//fclose(fp);
}
string CopySave() {
	const int amount=5;
	char paths[amount][32]={"/data/rksys.dat","/data/wc24dl.vff", "/data/wc24scr.vff", "/data/banner.bin", "/content/title.tmd"};

	int retr=0;
	int retw=0;
	
	for (int i = 0; i < amount; ++i)
	{
		if (i<=2) {
			string fn="/title/00010004/";
			fn+=toHex("RMCE", false);
			string fn_=fn+paths[i];
			fstats* attr=cfstats();
			int fd=ISFS_Open(fn_.c_str(), ISFS_OPEN_READ);

			ISFS_GetFileStats(fd, attr);
			u32 size=attr->file_length;


			u8* buf=cbuf(size);

			if (!buf) {
				return "No memory available.";
			}
			int tmp=ISFS_Read(fd, buf, size);


			if (tmp < 0) {
				retr--;
			}
			else {
				retr++;
			}



			ISFS_Close(fd);


			fn="/title/00010004/";
			fn+=toHex("JNKW", false);

			fn_=fn+paths[i];

			fd=ISFS_Open(fn_.c_str(), ISFS_OPEN_WRITE);


			tmp=ISFS_Write(fd, buf, size);

			if (tmp < 0) {
				retw--;
			}
			else {
				retw++;
			}


			ISFS_Close(fd);
		}
		else {
			string base="/NewerKartWii/channel";
			string file=paths[i];
			string full=base+file;

			FILE* fp=fopen(full.c_str(), "r");


			u32 size=fsize(fp);

			u8* buf=cbuf(size);


			u32 read=fread(buf, sizeof(u8), size, fp);
			if (read<size) {
				retr--;
			}
			else {
				retr++;
			}
			fclose(fp);

			base="/title/00010004/4a4e4b57";
			file=paths[i];
			full=base+file;

			int fd=ISFS_Open(full.c_str(), ISFS_OPEN_WRITE);
			int w=ISFS_Write(fd, buf, size);
			if (w<0) {
				char write[64];
				sprintf(write, "fn: %s, %d", base.c_str(), w);
				return write;
				retw--;
			}
			else {
				retw++;
			}
			ISFS_Close(fd);
		}
		//return "1amount9";
	}
	if ((retr < amount) & (retw == amount)) {
		return "Read error.";
	}
	else if ((retr == amount) & (retw == amount)) {
		return "Succesfully copied.";
	}
	else if ((retr < amount) & (retw < amount)) {
		return "Read and write error.";
	}
	else {
		return "Write error.";
	}

	return "return error.";
}