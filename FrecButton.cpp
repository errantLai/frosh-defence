/*
 * FrecButton.cpp
 *
 * Created on: Nov 10, 2018
 * Author: Chris
 */
#include <SFML/Graphics.hpp>
#include "FrecButton.h"
#include "Clickable.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

sf::Font font;


const bool _debug = true;


FrecButton::FrecButton(sf::Vector2f _position, int _radius, sf::Texture* _texture,std::string inText) {
		if (!font.loadFromFile("assets/georgia.ttf")) {
	}
	// TODO Auto-generated constructor stub
	graphic = sf::CircleShape(_radius);
	setPosition(_position);
	// The alternative is to use shape's getLocalBounds, and override insideShape().
	// I am unsure where else the size would be useful for the button object
	setSize(sf::Vector2f(_radius * 2, _radius * 2));
	graphic.setTexture(_texture);
	graphic.setFillColor(sf::Color(255, 255, 255, 180)); // half transparent
	graphic.setOutlineColor(sf::Color(210, 16, 52)); // Tri-red
	displayText = false;
	frecButtonText = sf::Text();
	frecButtonText.setString(inText);

	frecButtonText.setCharacterSize(50);
	frecButtonText.setPosition(0,00);

	update();
}

FrecButton::~FrecButton() {
}

void FrecButton::setTextureRect(const sf::IntRect& rect) {
	graphic.setTextureRect(rect);
}

void FrecButton::update() {
	graphic.setPosition(getPosition());
}
void FrecButton::render(sf::RenderWindow& _window) {

	frecButtonText.setFont(font);
	_window.draw(graphic);
//	cout << (frecButtonText.getString()) << endl;
	if(displayText)_window.draw(frecButtonText);
}

void FrecButton::onClick() {
	graphic.setOutlineThickness(0);
	cout << "Button is clicked" << endl;
}

void FrecButton::onMouseEnter() {
	graphic.setFillColor(sf::Color(255, 255, 255, 255)); // half transparent
	displayText = true;
}

void FrecButton::onMousePressed() {
	graphic.setOutlineThickness(10);
}

void FrecButton::onMouseLeave() {
	graphic.setOutlineThickness(0);
	graphic.setFillColor(sf::Color(255, 255, 255, 180)); // half transparent
	displayText = false;
}
