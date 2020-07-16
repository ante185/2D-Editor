#pragma once

enum CLIMATE{SEA, CONTINENTAL, OCEANIC, MEDITERRAN, TROPICAL, ARID, DESERT, NORDIC, POLAR};
enum RELIEF{ RELIEF_NONE, PLAIN, ROCKY, HILLS, MOUNTAINS};
enum VEGETATION{VEG_NONE, FOREST};
enum WATER{ WATER_NONE, RIVER_SMALL, RIVER_MED, RIVER_LARGE, LAKE, SWAMP};
enum WORLDOBJECT{WOBJ_NONE, PRIM_SPAWN};

class Region
{
private:
	int	x,	y;
	CLIMATE	climate;
	RELIEF	relief;
	VEGETATION	vegetation;
	WATER	water;
	WORLDOBJECT	object;
public:
	Region();
	Region(const Region&);
	~Region();

	Region(int x, int y, CLIMATE, RELIEF, VEGETATION, WATER, WORLDOBJECT);
	Region(int x, int y, char c, char r, char v, char w, char o);
};

