#include "collision.h"

bool collision::collidesWith(spaceship &Spaceship, invader &invader)
{
	//create new spaceship rec
	sf::FloatRect ship;
	ship.left = Spaceship.Spaceship.getPosition().x;
	ship.top = Spaceship.Spaceship.getPosition().y;
	ship.width = Spaceship.Spaceship.getGlobalBounds().width;
	ship.height = Spaceship.Spaceship.getGlobalBounds().height;

	//create new invader rec
	sf::FloatRect enemy;
	enemy.left = invader.Invader.getPosition().x;
	enemy.top = invader.Invader.getPosition().y;
	enemy.width = invader.Invader.getGlobalBounds().width;
	enemy.height = invader.Invader.getGlobalBounds().height;

	// are two rec intersected? 
	return ship.intersects(enemy);
}

bool collision::collidesWith(missile &missile, invader &invader)
{
	//create new missile rec
	sf::FloatRect bullet;
	bullet.left = missile.Missile.getPosition().x;
	bullet.top = missile.Missile.getPosition().y;
	bullet.width = missile.Missile.getGlobalBounds().width;
	bullet.height = missile.Missile.getGlobalBounds().height;

	//create new invader rec
	sf::FloatRect enemy;
	enemy.left = invader.Invader.getPosition().x;
	enemy.top = invader.Invader.getPosition().y;
	enemy.width = invader.Invader.getGlobalBounds().width;
	enemy.height = invader.Invader.getGlobalBounds().height;

	// are two rec intersected? 
	return bullet.intersects(enemy);
}