#pragma once
#include "Region.h"
#include <fstream>

class WorldMap
{
private:
	char size;
	char sizeName[7];
	char* worldPath;

	Region* regions;

public:
	WorldMap();
	WorldMap(const WorldMap&);
	~WorldMap();

	void loadWorldMap(const char* const filePath);

private:
	void createRegionsArray(const char* const data);

};

