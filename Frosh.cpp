/*
 * Frosh.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: Chris
 */

#include "Frosh.h"

Frosh::Frosh(sf::Vector2f _position, sf::Vector2f _size, sf::Texture* _texture,
		int _tam, int _health, int _damage) :
		texture(_texture), tamValue(_tam), health(_health), damage(_damage) {
	shape = sf::RectangleShape(sf::Vector2f(_size.x, _size.y));
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
	return this->shape.getPosition();
}

void Frosh::setPosition(sf::Vector2f position) {
	this->shape.setPosition(position);
}

int Frosh::reduceHealth(int damage) {
	this->health -= damage;
	return this->health;
}

//	This is the movement logic that updates the position
void Frosh::update() {

}
void Frosh::render(sf::RenderWindow* window) {
	window->draw(shape);
}

