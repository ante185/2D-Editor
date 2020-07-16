#include "WorldMap.h"

WorldMap::WorldMap()
{
}

WorldMap::WorldMap(const WorldMap &)
{
}

WorldMap::~WorldMap()
{
}

void WorldMap::loadWorldMap(const char * const filePath)
{

	std::ifstream file;
	file.open(filePath, std::ios::in | std::ios::ate | std::ios::binary);

	unsigned int fileLenght = file.tellg();
	file.seekg(0);

	unsigned char * data = new unsigned char[fileLenght];

	file.read((char*)data, fileLenght);
	int i = 0;
	(data[i++] + data[i++]);
	(data[i++] + data[i++]);

	delete[] data;
}
