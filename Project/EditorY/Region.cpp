#include "Region.h"

Region::Region()
:x(0), y(0)
{
	climate	=	SEA;
	relief	= RELIEF_NONE;
	vegetation	= VEG_NONE;
	water	= WATER_NONE;
	object	= WOBJ_NONE;
}

Region::Region(const Region &)
{
}

Region::~Region()
{
}

Region::Region(unsigned short x, unsigned short y, CLIMATE c, RELIEF r, VEGETATION v, WATER w, WORLDOBJECT o)
:x(x), y(y), climate(c), relief(r), vegetation(v), water(w), object(o)
{}

Region::Region(unsigned short x, unsigned short y, unsigned char c, unsigned char r, unsigned char v, unsigned char w, unsigned char o)
:Region(x, y, (CLIMATE) c, (RELIEF) r, (VEGETATION) v, (WATER) w, (WORLDOBJECT) o)
{}

const void Region::getRegionInfo(CLIMATE * c, RELIEF * r, VEGETATION * v, WATER * w, WORLDOBJECT * o)
{
	if(c)
		*c = climate;
	if(r)
		*r = relief;
	if(v)
		*v = vegetation;
	if(w)
		*w = water;
	if(o)
		*o = object;
}

void Region::setRegionInfo(CLIMATE c, RELIEF r, VEGETATION v, WATER w, WORLDOBJECT o)
{
	climate = c;
	relief = r;
	vegetation = v;
	water = w;
	object = o;
}

const void Region::getCoordinates(const unsigned short *x, const unsigned short *y)
{
	x = &this->x;
	y = &this->y;
}

void Region::setCoordinates(const unsigned short x, const unsigned short y)
{
	this->x = x;
	this->y = y;
}

std::string Region::getStrDescription()
{
	std::string result = "";

	switch (climate)
	{
	case SEA:
		result.append("SEA ");
		break;
	case CONTINENTAL:
		result.append("CONTINENTAL ");
		break;
	case OCEANIC:
		result.append("OCEANIC ");
		break;
	case MEDITERRAN:
		result.append("MEDITERRAN ");
		break;
	case TROPICAL:
		result.append("TROPICAL ");
		break;
	case ARID:
		result.append("ARID ");
		break;
	case DESERT:
		result.append("DESERT ");
		break;
	case NORDIC:
		result.append("SEA ");
		break;
	case POLAR:
		result.append("POLAR ");
		break;
	default:
		break;
	}

	switch (relief)
	{
	case RELIEF_NONE:
		result.append("NONE ");
		break;
	case PLAIN:
		result.append("PLAIN ");
		break;
	case ROCKY:
		result.append("ROCKY ");
		break;
	case HILLS:
		result.append("HILLS ");
		break;
	case MOUNTAINS:
		result.append("MOUNTAINS ");
		break;
	default:
		break;
	}

	switch (vegetation)
	{
	case VEG_NONE:
		result.append("VEG_NONE ");
		break;
	case FOREST:
		result.append("FOREST ");
		break;
	default:
		break;
	}

	switch (water)
	{
	case WATER_NONE:
		result.append("NONE ");
		break;
	case RIVER_SMALL:
		result.append("RIVER_SMALL ");
		break;
	case RIVER_MED:
		result.append("RIVER_MED ");
		break;
	case RIVER_LARGE:
		result.append("RIVER_LARGE ");
		break;
	case LAKE:
		result.append("LAKE ");
		break;
	case SWAMP:
		result.append("SWAMP ");
		break;
	default:
		break;
	}

	switch (object)
	{
	case WOBJ_NONE:
		result.append("NONE ");
		break;
	case PRIM_SPAWN:
		result.append("PRIM_SPAWN ");
		break;
	default:
		break;
	}

	return result;
}



//Region Region::operator=(const Region&  b)
//{
//	x = b.x;
//	y = b.y;
//	climate = b.climate;
//	relief	= b.relief;
//	vegetation = b.vegetation;
//	water = b.water;
//	object = b.object;
//
//	return *this;
//}
