#include "editor.h"

WorldMap * Editor::getROworldMap()
{
	return &currentMap;
}

bool Editor::update()
{
	std::string str;
	std::string currentWord;
	int intA, intB, intC, intD;

	std::stringstream cmdstream;
	std::getline(std::cin, str);
	cmdstream << str;
	cmdstream >> currentWord;

	if(currentWord == "quit"){
		return false;
	}
	else if (currentWord == "help") {
		cmdstream >> currentWord;
		if (currentWord == "region") {
			std::cout << regionHelp;
		}
		else if (currentWord == "more") {
			std::cout << moreHelp;
		}
		else {
			std::cout << commandsHelp;
		}
	}
	else if (currentWord == "open") {
		cmdstream >> currentWord;
		if (!currentMap.loadWorldMap(currentWord.c_str())) {
			std::cout << "Could not open file \n";
		}
		else {
			std::cout << "File loaded \n";
			std::cout << "Mapsize: " << (unsigned short)currentMap.sizeX << " by " << (unsigned short)currentMap.sizeY << std::endl;
			}
	}
	else if (currentWord == "save") {
		cmdstream >> currentWord;
		currentMap.saveWorldMap(currentWord.c_str());
		std::cout << "World saved to: " << currentWord << std::endl;
	}
	else if (currentWord == "getRegion") {
		cmdstream >> intA >> intB;
		region_ptr = &currentMap.regions[intA + intB * currentMap.sizeX];
		currentRegion = *region_ptr;
		std::cout << currentRegion.getStrDescription() << std::endl;
	}
	else if (currentWord == "saveRegion") {
		*region_ptr = currentRegion;
	}
	else if (currentWord == "setBiome") {

		CLIMATE clm;
		RELIEF rlf;
		VEGETATION veg;
		WATER wat;
		WORLDOBJECT wob;

		cmdstream >> intA >> intB;
		cmdstream >> intC >> intD;
		clm = (CLIMATE)intA;
		rlf = (RELIEF)intB;
		veg = (VEGETATION)intC;
		wat = (WATER)intD;
		cmdstream >> intA;
		wob = (WORLDOBJECT)intA;

		currentRegion.setRegionInfo(clm, rlf, veg, wat, wob);
		std::cout << currentRegion.getStrDescription() << std::endl;
	}
	else if (currentWord == "fillArea") {
		cmdstream >> intA >> intB;
		cmdstream >> intC >> intD;
		currentMap.fillArea(intA, intB, intC, intD, currentRegion);
	}
	else {
		std::cout << "Unknown command \n";
	}

	std::cout << std::endl << '>';

	return true;
}
