#ifndef spaceship_h
#define spaceship_h

#include <SFML/Graphics.hpp>

class spaceship
{
public:
	sf::RectangleShape Spaceship;

	spaceship();
	void kill();
	bool isAlive();
	void respawn();
	void draw(sf::RenderWindow &window);
	void setlocation(float spaceshipX, float spaceshipY);

private:
	float spaceshipX;
	float spaceshipY;
	bool alive;
	
};

#endif