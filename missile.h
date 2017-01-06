#ifndef missile_h
#define missile_h

#include <SFML/Graphics.hpp>

class missile
{
public:
	sf::RectangleShape Missile;

	missile();
	bool isAlive();
	void kill();
	void spawn(bool);
	void draw(sf::RenderWindow &window);
	void setlocation(float missileX, float missileY);
private:
	bool isFired;
};

#endif