/*
 * Frosh.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: Chris
 */

#include "Frosh.h"

void Frosh::assignFroshStats(int type, double modifier) {
	if (type == 0) {
		tamValue = 5;
		health = 10;
		damage = 1;
	} else {
		tamValue = 5 * modifier;
		health = 10;
		damage = 1;
	}
}

Frosh::Frosh(sf::Vector2f _position, sf::Vector2f _size, sf::Texture* _texture,
		int type, double modifier) :
		position(_position), size(_size), texture(_texture) {
	assignFroshStats(type, modifier);
	shape = sf::RectangleShape(sf::Vector2f(size.x, size.y));
	shape.setSize(_size);
	shape.setTexture(texture);
	shape.setFillColor(sf::Color(255, 255, 255, 180)); // Half transparency
}

// FroshController is responsible for creating and deleting objects
Frosh::~Frosh() {
	// RectangleShape can safely fall out of scope, should be picked
	// up by garbage collection
}

int Frosh::getTamValue() {
	return this->tamValue;
}
int Frosh::getHealth() {
	return this->health;
}
int Frosh::getDamage() {
	return this->damage;
}

sf::Vector2f Frosh::getPosition() {
	return this->position;
}

int Frosh::reduceHealth(int damage) {
	this->health -= damage;
	return this->health;
}

void Frosh::update() {
//	This is the movement logic that updates the position
//

}
void Frosh::render(sf::RenderWindow* window) {
	window->draw(shape);
}

