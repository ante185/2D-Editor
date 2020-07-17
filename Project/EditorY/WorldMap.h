#pragma once
#include "Region.h"
#include <fstream>

class WorldMap
{
private:
	unsigned char sizeX, sizeY;
	char sizeName[7];
	char* worldPath;

	Region* regions;

public:
	WorldMap();
	WorldMap(const WorldMap&);
	~WorldMap();

	void loadWorldMap(const char* const filePath);
	void saveWorldMap();
};

