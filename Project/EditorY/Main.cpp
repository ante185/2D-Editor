#include "WorldMap.h"

const	char*	tinyWorld	=	"../../worldmap/tiny_world.ybin";
const	char*	smallWorld	=	"../../worldmap/small_world.ybin";
const	char*	mediumWorld	=	"../../worldmap/regular_world.ybin";
const	char*	largeWorld	=	"../../worldmap/large_world.ybin";






int main() {
	
	WorldMap testingWorld;
	
	testingWorld.loadWorldMap(mediumWorld);

	return 0;
}