#include <fstream>
#include <iostream>

const char* tinyWorld = "../../worldmap/tiny_world.ybin";
const char* smallWorld = "../../worldmap/small_world.ybin";
const char* mediumWorld = "../../worldmap/regular_world.ybin";
const char* largeWorld = "../../worldmap/large_world.ybin";

void getWorldSize(const char* filePath, unsigned int& width, unsigned int& height) {


	std::ifstream file;
	file.open(filePath, std::ios::in | std::ios::ate | std::ios::binary);

	unsigned int fileLenght = file.tellg();
	file.seekg(0);

	char * data = new char[fileLenght];

	file.read(data, fileLenght);
	int i = 0;
	std::cout << (unsigned short)(data[i++] + data[i++]) << ':';
	std::cout << (unsigned short)(data[i++] + data[i++]) << '	' << '\n';

	delete[] data;
}


int main() {

	unsigned int x = 0, y = 0;

	getWorldSize(tinyWorld, x, y);
	getWorldSize(smallWorld, x, y);
	getWorldSize(mediumWorld, x, y);
	getWorldSize(largeWorld, x, y);



	return 0;
}