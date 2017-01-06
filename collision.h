#ifndef collision_h
#define collision_h

#include "spaceship.h"
#include "invader.h"
#include "missile.h"

class collision
{
public:
	static bool collidesWith(spaceship &, invader &);
	static bool collidesWith(missile &, invader &);
};

#endif