#include <SFML/Graphics.hpp>
#include "missile.h"

missile::missile()
{
	Missile = sf::RectangleShape(sf::Vector2f(5, 5));
	isFired = false;
}

bool missile::isAlive()
{
	return isFired;
}

void missile::kill()
{
	isFired = false;
}

void missile::spawn(bool bul)
{
	isFired = bul;
}

void missile::draw(sf::RenderWindow &window)
{
	window.draw(Missile);
}

void missile::setlocation(float missileX, float missileY)
{
	Missile.setPosition(missileX, missileY);
}