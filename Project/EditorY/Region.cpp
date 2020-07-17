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

const void Region::getRegionInfo(const CLIMATE * c, const RELIEF * r, const VEGETATION * v, const WATER * w, const WORLDOBJECT * o)
{
	if(c)
		c = &climate;
	if(r)
		r = &relief;
	if(v)
		v = &vegetation;
	if(w)
		w = &water;
	if(o)
		o = &object;
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
