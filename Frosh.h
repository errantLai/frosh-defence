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
	sf::IntRect textureRect;

	// Internal game attributes
	int tamValue;
	int health;
	// This determines how much health is lost when it crosses the finish
	int damage;
	float speed;

	// To handle movement, I can have a reference to the array
	// of points, and then a current pathIndex. Once the point is reached,
	// I move to the next index. To check end of screen, have the controller
	// read the pathIndex, and delete it once the final index is reached.
public:
	// The actual texture definition occurs within the froshController
	Frosh(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture,
			sf::IntRect textureRect, int _tam, int _health, int _damage, float _speed);
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
	// The frosh controller will use these to change animations
	sf::IntRect getTextureRect();
	void setTextureRect(sf::IntRect textureRect);
	// This returns the resulting health of the frosh
	int reduceHealth(int damage);
};

#endif /* FROSH_H_ */
