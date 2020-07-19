#pragma once
#include <string>

enum CLIMATE{SEA, CONTINENTAL, OCEANIC, MEDITERRAN, TROPICAL, ARID, DESERT, NORDIC, POLAR};
enum RELIEF{ RELIEF_NONE, PLAIN, ROCKY, HILLS, MOUNTAINS};
enum VEGETATION{VEG_NONE, FOREST};
enum WATER{ WATER_NONE, RIVER_SMALL, RIVER_MED, RIVER_LARGE, LAKE, SWAMP};
enum WORLDOBJECT{WOBJ_NONE, PRIM_SPAWN};

class Region
{
private:
	unsigned short	x,	y;
	CLIMATE	climate;
	RELIEF	relief;
	VEGETATION	vegetation;
	WATER	water;
	WORLDOBJECT	object;
public:
	Region();
	Region(const Region&);
	~Region();

	Region(unsigned short x, unsigned short y, CLIMATE, RELIEF, VEGETATION, WATER, WORLDOBJECT);
	Region(unsigned short x, unsigned short y, unsigned char c, unsigned char r, unsigned char v, unsigned char w, unsigned char o);

	const void getRegionInfo(CLIMATE*, RELIEF*, VEGETATION*, WATER*, WORLDOBJECT*);
	//void updateRegionInfo(CLIMATE*, RELIEF*, VEGETATION*, WATER*, WORLDOBJECT*);
	void setRegionInfo(CLIMATE, RELIEF, VEGETATION, WATER, WORLDOBJECT);

	const void getCoordinates(const unsigned short*, const unsigned short*);
	void setCoordinates(const unsigned short, const unsigned short);

	std::string getStrDescription();
	//Region operator=(const Region&);
};

