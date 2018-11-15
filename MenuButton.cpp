/*
 * MenuButton.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Connor
 */
#include <SFML/Graphics.hpp>
#include "MenuButton.h"
#include "Clickable.h"
#include <iostream>

MenuButton::MenuButton(sf::Vector2f _position, int _sizex, int _sizey, sf::Texture* _texture, int type) {
	// TODO Auto-generated constructor stub
	graphic = sf::RectangleShape(sf::Vector2f(_sizex,_sizey));
	setPosition(_position);
	// The alternative is to use shape's getLocalBounds, and override insideShape().
	// I am unsure where else the size would be useful for the button object
	graphic.setTexture(_texture);
	update();
}

void MenuButton::setTextureRect(const sf::IntRect& rect) {
	graphic.setTextureRect(rect);
}

void MenuButton::update() {
	graphic.setPosition(getPosition());
}
void MenuButton::render(sf::RenderWindow& _window) {
	_window.draw(graphic);
}

void MenuButton::onClick() {
	graphic.setOutlineThickness(0);
	//cout << "Button is clicked" << endl;
}

void MenuButton::onMouseEnter() {
	graphic.setFillColor(sf::Color(255, 255, 255, 255)); // half transparent
}

void MenuButton::onMousePressed() {
	graphic.setOutlineThickness(10);
}

void MenuButton::onMouseLeave() {
	graphic.setOutlineThickness(0);
	graphic.setFillColor(sf::Color(255, 255, 255, 180)); // half transparent
}

