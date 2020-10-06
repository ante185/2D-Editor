#pragma once
#include <iostream>
#include <string>
#include "WorldMap.h"
#include <sstream>      // std::stringstream

static std::string commandsHelp = "quit, help, open, save, getRegion, saveRegion, setBiome  \n help more for more \n";
static std::string moreHelp = "open/save expects filepath \n getRegion expects X Y coordinates of a region \n setBiome sets the biome for last gotten region : more in help region \n saveRegion saves the last changed region to the worldmap";
static std::string regionHelp = "setBiome expects 5 values, corresponding to CLIMATE, RELIEF, VEGETATION, WATER, WORLD OBJECT \n valid int values are ranges: 0-8 | 0-4 | 0-1 | 0-5 | 0-1 \n";

class Editor
{	
private:
	WorldMap currentMap;
	Region currentRegion;
	Region* region_ptr;

public:
	WorldMap* getROworldMap();
	bool update();
};

