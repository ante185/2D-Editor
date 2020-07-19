#pragma once
#include "Region.h"
#include <fstream>

class WorldMap
{
private:
public:
	unsigned char sizeX, sizeY;
	char sizeName[7];
	char* worldPath;


	WorldMap();
	WorldMap(const WorldMap&);
	~WorldMap();

	bool loadWorldMap(const char* const filePath);
	void saveWorldMap(const char* const filePath);

	Region* regions;
};

