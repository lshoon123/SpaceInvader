#include "invader.h"
#include <iostream>
#include <stdexcept>

invader::invader(const int id)
{
	Invader = sf::RectangleShape(sf::Vector2f(20, 20));
	alive = true;
}

void invader::setlocation(float invaderX, float invaderY)
{
	Invader.setPosition(invaderX, invaderY);
}

void invader::kill()
{
	alive = false;
}

bool invader::isAlive()
{
	return alive;
}

void invader::draw(sf::RenderWindow &window)
{
	window.draw(Invader);
}

float invader::getSpeed() const
{
	return speed;
}