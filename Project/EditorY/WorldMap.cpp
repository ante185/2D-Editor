#include "WorldMap.h"
#include <iostream>
#include <string>

WorldMap::WorldMap()
{
}

WorldMap::WorldMap(const WorldMap &)
{
}

WorldMap::~WorldMap()
{
	if(regions)
		delete[] regions;
	if(worldPath)
		delete worldPath;
}

void WorldMap::loadWorldMap(const char * const filePath)
{
	int len = std::strlen(filePath) + 1;
	worldPath = new char[len ];
	strcpy_s(worldPath, len, filePath);

	std::ifstream file;
	file.open(filePath, std::ios::in | std::ios::ate | std::ios::binary);

	unsigned int fileLenght = (unsigned int)file.tellg();
	file.seekg(0);

	unsigned char * data = new unsigned char[fileLenght];

	file.read((char*)data, fileLenght);
	unsigned short width	= ((unsigned short*)data)[0];
	unsigned short height	= ((unsigned short*)data)[1];

	file.close();
	sizeX = width;
	sizeY = height;


	regions = new Region[width * height];

	//Region test[10000];
	//std::ofstream debugFile;
	//debugFile.open("worldLoadText.txt");
	//debugFile << (unsigned short)data[0];
	//debugFile << ' ';
	//debugFile << (unsigned short)data[1];
	//debugFile << '	';
	//debugFile << (unsigned short)data[2];
	//debugFile << ' ';
	//debugFile << (unsigned short)data[3];
	//
	//for (i = 4; i < fileLenght; i++) {
	//	if (!((i - 4) % 5)) {
	//		//std::cout << '	';
	//		debugFile << '	';
	//	}
	//	if (!((i - 4) % 50)) {
	//		//std::cout << '\n';
	//		debugFile << '\n';
	//	}
	//	//std::cout << (unsigned short)data[i] << '|';
	//	debugFile << (unsigned short)data[i] << '|';
	//}

	unsigned int i = 0;
	unsigned short k;
	Region temp;

	for ( k = 0, i = 4; k < width * height; k++) {
			
		temp.setCoordinates(k % width, k / width);

		temp.setRegionInfo(	
			(	CLIMATE		)data[i],
			(	RELIEF		)data[i+1],
			(	VEGETATION	)data[i+2],
			(	WATER		)data[i+3],
			(	WORLDOBJECT	)data[i+4]
		);
		i +=5;
		regions[k] = temp;
	}

	delete[] data;
}

void WorldMap::saveWorldMap()
{
	std::ofstream fileOut;
	fileOut.open("../../saved_worldmap/world.ybin", std::ios::out | std::ios::binary);
	unsigned char* writeBuffer;
	unsigned int bufferLenght = 4 + (sizeX*sizeY*5);

	writeBuffer = new unsigned char[bufferLenght];

	CLIMATE clm_ptr;
	RELIEF rlf_ptr;
	VEGETATION veg_ptr;
	WATER wat_ptr;
	WORLDOBJECT wob_ptr;


	((unsigned short*)writeBuffer)[0] = sizeX;
	((unsigned short*)writeBuffer)[1] = sizeY;
	unsigned int i = 4, k = 0;
	for (; i < bufferLenght;) {
		regions[k].getRegionInfo(&clm_ptr, &rlf_ptr, &veg_ptr, &wat_ptr, &wob_ptr);
		writeBuffer[i++] = (unsigned char)clm_ptr;
		writeBuffer[i++] = (unsigned char)rlf_ptr;
		writeBuffer[i++] = (unsigned char)veg_ptr;
		writeBuffer[i++] = (unsigned char)wat_ptr;
		writeBuffer[i++] = (unsigned char)wob_ptr;
	}

	fileOut.write((const char*)writeBuffer, bufferLenght);

	fileOut.close();
}
