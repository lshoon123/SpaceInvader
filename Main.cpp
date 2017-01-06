#include "collision.h"
#include "invader.h"
#include "missile.h"
#include "spaceship.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <stdexcept>

#define NumberInvader1 5
#define NumberInvader2 10
#define WIDTH 800
#define HEIGHT 600

using namespace std;

int main(int, char *argv[])
{
	const float spaceshipSpeed = 4.f;
	int invaderSpeed = 5;
	int missileCount = 0;
	const float bulletSpeed = 500.f;
	
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Invader");
	window.setVerticalSyncEnabled(true);

	//create missile
	missile Missile[100];

	//create spaceship
	spaceship Spaceship;
	Spaceship.setlocation(WIDTH/2 - 20, HEIGHT - Spaceship.Spaceship.getGlobalBounds().height-10);

	//create an array of invader
	invader InvaderArray[NumberInvader1][NumberInvader2];
	for (int i = 0; i < NumberInvader1; i++)
	{
		int k = NumberInvader2;
		for (int j = 0; j < NumberInvader2; j++)
		{
			k *= i;
			invader Invader(k+j);
			Invader.setlocation(j * 30, i*30 +Invader.Invader.getGlobalBounds().height / 2);
			InvaderArray[i][j] = Invader;
		}		
	}
	
	//main clock
	sf::Clock clock;
	sf::Clock checkMissile;

	

	//set timepeFrame
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//start the game loop
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// get the time since last update
		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			//spaceship movement right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (Spaceship.Spaceship.getPosition().x < WIDTH)
				{
					Spaceship.Spaceship.move(spaceshipSpeed + deltaTime, 0.f);
				}
				else
				{
					Spaceship.Spaceship.setPosition(-Spaceship.Spaceship.getGlobalBounds().width, HEIGHT - Spaceship.Spaceship.getGlobalBounds().height - 10);
				}
			}
			// spaceship movement left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (Spaceship.Spaceship.getPosition().x > 0.f)
				{
					Spaceship.Spaceship.move(-spaceshipSpeed + deltaTime, 0.f);
				}
				else
				{
					Spaceship.Spaceship.setPosition(WIDTH, HEIGHT - Spaceship.Spaceship.getGlobalBounds().height - 10);
				}
			}
			// invader movement
			int i=0, j=0, checkChange;
			for (i = 0; i < NumberInvader1; i++)
			{
				for (j = 0; j < NumberInvader2; j++)
				{
					InvaderArray[i][j].Invader.move(invaderSpeed, 0);
				}
			}
			checkChange = invaderSpeed;
			//invader arrived right side
			for (int i = 0; i < NumberInvader1; i++)
			{
				for (int j = 0; j < NumberInvader2; j++)
				{
					if (InvaderArray[i][j].Invader.getPosition().x >= WIDTH - 20 && InvaderArray[i][j].isAlive())
					{
						invaderSpeed *= -1;
						break;
					}
				}
				if (checkChange != invaderSpeed)
				{
					break;
				}
			}
			//invader arrived left side
			for (int i = 0; i < NumberInvader1; i++)
			{
				for (int j = 0; j < NumberInvader2; j++)
				{
					if (InvaderArray[i][j].Invader.getPosition().x < 0 && InvaderArray[i][j].isAlive())
					{
						invaderSpeed *= -1;
						break;
					}
				}
				if (checkChange != invaderSpeed)
				{
					break;
				}
			}
			if (checkChange != invaderSpeed)
			{
				for (int i = 0; i < NumberInvader1; i++)
				{
					for (int j = 0; j < NumberInvader2; j++)
					{
						InvaderArray[i][j].Invader.move(0, 30);
					}
				}
			}
			// missile movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				//getElapsedTime : how much time is passed?  asSecond() : as Second
				if (checkMissile.getElapsedTime().asSeconds() > 0.2f)
				{
					Missile[missileCount].spawn(true);
					Missile[missileCount].setlocation(Spaceship.Spaceship.getPosition().x + 20, HEIGHT - Spaceship.Spaceship.getGlobalBounds().height);
					if (missileCount != 100)
					{
						missileCount++;
					}
					// clear pass time
					checkMissile.restart();
				}												
			}
			//collision invader and bottom
			for (int i = 0; i < NumberInvader1; i++)
			{
				for (int j = 0; j< NumberInvader2; j++)
				{
					if (InvaderArray[i][j].Invader.getPosition().y + InvaderArray[i][j].Invader.getGlobalBounds().height > HEIGHT)
					{
						Spaceship.kill();
					}
				}
				
			}
			//collision invader and ship
			for (int i = 0; i < NumberInvader1; i++)
			{
				for (int j = 0; j < NumberInvader2; j++)
				{
					if (collision::collidesWith(Spaceship, InvaderArray[i][j]) && InvaderArray[i][j].isAlive())
					{
						Spaceship.kill();
					}
				}				
			}
			//collision missile and invader
			for (int i = 0; i < NumberInvader1; i++)
			{
				for (int j = 0; j < NumberInvader2; j++)
				{
					for (int k = 0; k <= missileCount; k++)
					{
						if (collision::collidesWith(Missile[k], InvaderArray[i][j]) && InvaderArray[i][j].isAlive() && Missile[k].isAlive())
						{
							InvaderArray[i][j].kill();
							Missile[k].kill();
						}
					}					
				}				
			}

			// collision Missile and top
			for (int k = 0; k <= missileCount; k++)
			{
				if (Missile[k].Missile.getPosition().y < 0)
				{
					Missile[k].kill();
				}
			}
			
			//clear the screen
			window.clear();
			//draw to screen
			for (int i = 0; i < NumberInvader1; i++)
			{
				for (int j = 0; j < NumberInvader2; j++)
				{
					if (InvaderArray[i][j].isAlive())
					{
						InvaderArray[i][j].draw(window);
					}
				}				
			}
			if (Spaceship.isAlive())
			{
				Spaceship.draw(window);
			}
			for (int k = 0; k <= missileCount; k++)
			{
				if (Missile[k].isAlive())
				{
					Missile[k].draw(window);
					Missile[k].Missile.move(0, -10);
				}
			}			
			window.display();
		}
		if (!Spaceship.isAlive())
		{
			window.close();
		}
	}

}