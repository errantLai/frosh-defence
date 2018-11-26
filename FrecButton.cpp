/*
 * FrecButton.cpp
 *
 * Created on: Nov 10, 2018
 * Author: Chris
 */
#include <SFML/Graphics.hpp>
#include "Frec.h"
#include "FrecButton.h"
#include "Clickable.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

sf::Font font;

const bool _debug = true;

FrecButton::FrecButton(sf::Vector2f _position, int _radius,
		sf::Texture* _texture, std::string inText, std::string inText2,
		FrecType _type, GameState* _gameState) :
		frecType(_type), gameState(_gameState) {
	if (!font.loadFromFile("assets/georgia.ttf")) {
	}
	sf::Texture* _menuTexture = new sf::Texture;
	if (!_menuTexture->loadFromFile("assets/menuButtons.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}

	graphic = sf::CircleShape(_radius);
	setPosition(_position);
	setSize(sf::Vector2f(_radius * 2, _radius * 2));
	graphic.setTexture(_texture);
	graphic.setFillColor(sf::Color(255, 255, 255, 180)); // half transparent
	graphic.setOutlineColor(sf::Color(210, 16, 52)); // Tri-red

	displayText = false;
	// Text for Price (large)
	frecButtonText = sf::Text();
	frecButtonText.setString(inText);
	frecButtonText.setCharacterSize(40);
	// Text for Damage & Rate (small)
	frecButtonText2 = sf::Text();
	frecButtonText2.setString(inText2);
	frecButtonText2.setCharacterSize(20);
	// Background for text
	frecTextBack = sf::RectangleShape(sf::Vector2f(320, 128));
	frecTextBack.setTexture(_menuTexture);
	frecTextBack.setTextureRect(sf::IntRect(1056, 165, 320, 128));
	// Position by Frec
	int baseY = -15, baseX = 1500;
	if (_type == FrecType::thrower) {
		baseY += 275;
	} else if (_type == FrecType::slammer) {
		baseY += 515;
	} else if (_type == FrecType::swinger) {
		baseY += 755;
	}
	frecButtonText.setPosition(baseX + 70, baseY + 35);
	frecButtonText2.setPosition(baseX + 150, baseY + 40);
	frecTextBack.setPosition(baseX, baseY);

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
	frecButtonText2.setFont(font);
	_window.draw(graphic);
	if (displayText) {
		_window.draw(frecTextBack);
		_window.draw(frecButtonText);
		_window.draw(frecButtonText2);
	}
}

void FrecButton::onClick() {
	graphic.setOutlineThickness(0);
	gameState->setPurchaseFrec(this->frecType);
}

void FrecButton::onMouseEnter() {
	graphic.setFillColor(sf::Color(255, 255, 255, 255)); // Solid Colour
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
