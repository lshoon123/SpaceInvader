#include <SFML/Graphics.hpp>
#include<iostream>
#include<stdexcept>
#include "spaceship.h"

spaceship::spaceship()
{
	spaceshipX = 0;
	spaceshipY = 0;
	Spaceship = sf::RectangleShape(sf::Vector2f(40, 20));
	Spaceship.setPosition(spaceshipX, spaceshipY);
	Spaceship.setFillColor(sf::Color::Green);
	alive = true;
}

void spaceship::setlocation(float spaceshipX, float spaceshipY)
{
	Spaceship.setPosition(spaceshipX, spaceshipY);
}

void spaceship::kill()
{
	alive = false;
}

bool spaceship::isAlive()
{
	return alive;
}

void spaceship::draw(sf::RenderWindow &window)
{
	window.draw(Spaceship);
}

void spaceship::respawn()
{
	alive = true;
}