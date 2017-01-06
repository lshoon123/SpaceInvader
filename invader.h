#ifndef invader_h
#define invader_h

#include <SFML/Graphics.hpp>

#include<iostream>
#include<string>

class invader
{
public:
	sf::RectangleShape Invader;

	invader(){};
	invader(const int);
	void setlocation(float, float);
	void kill();
	bool isAlive();
	float getSpeed() const;
	void draw(sf::RenderWindow &window);


private:	
	bool alive;
	float speed;
};

#endif