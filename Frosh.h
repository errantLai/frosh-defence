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
	// Internal game attributes
	int tamValue;
	int health;
	// This determines how much health is lost when it crosses the finish
	int damage;

	sf::RectangleShape shape;
	// The frosh controller will determine which specific frosh
	// spritesheet to use. The frosh object is only responsible
	// for changing specific directions, etc.
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Texture* texture;

	// This assigns the relevant stats, with modifiers for later waves
	void assignFroshStats(int type, double modifier);
public:
	// The actual texture definition occurs within the froshController
	Frosh(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture,
			int type, double modifier);
	virtual ~Frosh();

	// Accessors
	int getTamValue();
	int getHealth();
	int getDamage();
	sf::Vector2f getPosition();
	// This returns the resulting health of the frosh
	int reduceHealth(int damage);

	// Game logic functions
	void update();
	void render(sf::RenderWindow* window);
};

#endif /* FROSH_H_ */
