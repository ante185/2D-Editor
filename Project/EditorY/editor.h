#pragma once
#include <iostream>
#include <string>
#include "WorldMap.h"


std::string commands = "";

class Editor
{	
private:
	WorldMap currentMap;


public:
	bool update();
};

