#pragma once
#include "Region.h"
#include <fstream>

class WorldMap
{
private:
public:
	unsigned short sizeX, sizeY;
	char sizeName[7];
	char* worldPath;


	WorldMap();
	WorldMap(const WorldMap&);
	~WorldMap();

	WorldMap(unsigned short sizeX, unsigned short sizeY, CLIMATE climateFill);

	void fillArea(short x1, short y1, short x2, short y2, Region& region);

	bool loadWorldMap(const char* const filePath);
	void saveWorldMap(const char* const filePath);

	Region* regions;
};

