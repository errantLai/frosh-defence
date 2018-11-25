/*
 * Frosh.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: Chris
 */

#include "Frosh.h"

Frosh::Frosh(sf::Vector2f _position, sf::Vector2f _size, sf::Texture* _texture,
		sf::IntRect _textureRect, int _tam, int _health, int _damage,
		float _pixelSpeed) :
		texture(_texture), textureRect(_textureRect), tamValue(_tam), health(
				_health), damage(_damage), pixelSpeed(_pixelSpeed) {
	// Map shape properties
	shape = sf::RectangleShape(sf::Vector2f(_size.x, _size.y));
	shape.setPosition(_position);
	shape.setSize(_size);
	shape.setTexture(texture);
	shape.setTextureRect(textureRect);
	shape.setFillColor(sf::Color(255, 255, 255, 180)); // Half transparency

	targetPathPoint = 0;

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

sf::Vector2f Frosh::getCenterPosition() {
	sf::Vector2f center = this->shape.getPosition();
	center.x += this->shape.getSize().x / 2;
	center.y += this->shape.getSize().y / 2;
	return center;
}

void Frosh::setPosition(sf::Vector2f position) {
	this->shape.setPosition(position);
}

sf::IntRect Frosh::getTextureRect() {
	return this->textureRect;
}
void Frosh::setTextureRect(sf::IntRect textureRect) {
	this->textureRect = textureRect;
}

int Frosh::reduceHealth(int damage) {
	this->health -= damage;
	return this->health;
}

int Frosh::getPixelSpeed() {
	return this->pixelSpeed;
}

int Frosh::getPathIndex() {
	return this->targetPathPoint;
}

void Frosh::increasePathIndex() {
	this->targetPathPoint++;
}

//	This is the movement logic that updates the position
void Frosh::update() {

}
void Frosh::render(sf::RenderWindow* window) {
	window->draw(shape);
}

