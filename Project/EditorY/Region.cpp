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
