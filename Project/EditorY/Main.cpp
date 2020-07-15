#include <fstream>

const char* fileName = "../../worldmap/world.ybin";

int main() {

	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::ate | std::ios::binary);
	
	unsigned int fileLenght = file.tellg();
	file.seekg(0);

	char * data = new char[fileLenght];

	file.read(data, fileLenght);






	delete[] data;
	return 0;
}