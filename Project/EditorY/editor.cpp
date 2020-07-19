#include "editor.h"

bool Editor::update()
{
	std::string str;
	std::string currentWord;
	int intA, intB;

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
		clm = (CLIMATE)intA;
		rlf = (RELIEF)intB;
		cmdstream >> intA >> intB;
		veg = (VEGETATION)intA;
		wat = (WATER)intB;
		cmdstream >> intA;
		wob = (WORLDOBJECT)intA;

		currentRegion.setRegionInfo(clm, rlf, veg, wat, wob);
		std::cout << currentRegion.getStrDescription() << std::endl;
	}
	else {
		std::cout << "Unknown command \n";
	}

	std::cout << std::endl << '>';

	return true;
}
