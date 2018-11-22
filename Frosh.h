/*
 * Frosh.h
 *
 *  Created on: Nov 22, 2018
 *      Author: Chris
 */

#ifndef FROSH_H_
#define FROSH_H_
#include <SFML/Graphics.hpp>

class Frosh {
private:
	sf::RectangleShape shape;
	// The frosh controller will determine which specific frosh
	// spritesheet to use. The frosh object is only responsible
	// for changing specific directions, etc.
	sf::Texture* texture;

	// Internal game attributes
	int tamValue;
	int health;
	// This determines how much health is lost when it crosses the finish
	int damage;

public:
	// The actual texture definition occurs within the froshController
	Frosh(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture,
			int _tam, int _health, int _damage);
	virtual ~Frosh();

	// Game logic functions
	void update();
	void render(sf::RenderWindow* window);

	// Accessors
	int getTamValue();
	int getHealth();
	int getDamage();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	// This returns the resulting health of the frosh
	int reduceHealth(int damage);
};

#endif /* FROSH_H_ */
