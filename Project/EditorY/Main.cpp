#include "WorldMap.h"

const	char*	tinyWorld	=	"../../worldmap/tiny_world.ybin";
const	char*	smallWorld	=	"../../worldmap/small_world.ybin";
const	char*	mediumWorld	=	"../../worldmap/regular_world.ybin";
const	char*	largeWorld	=	"../../worldmap/large_world.ybin";






int main() {

	CLIMATE clm_ptr;
	RELIEF rlf_ptr;
	VEGETATION veg_ptr;
	WATER wat_ptr;
	WORLDOBJECT wob_ptr;

	WorldMap testingWorld;
	
	testingWorld.loadWorldMap(mediumWorld);
	testingWorld.regions[69 + (51 * 125)].getRegionInfo(&clm_ptr, &rlf_ptr, &veg_ptr, &wat_ptr, &wob_ptr);
	testingWorld.regions[69 + (51 * 125)].setRegionInfo(DESERT, rlf_ptr, veg_ptr, wat_ptr, wob_ptr);
	testingWorld.saveWorldMap();

	return 0;
}