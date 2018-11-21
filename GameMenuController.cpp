/*
 * GameMenuController.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: Chris
 */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "GameMenuController.h"
#include "Clickable.h"
#include "FrecButton.h"
#include "MenuButton.h"

using std::cout;
using std::endl;

sf::Event event;

const int cubit = 60;
float menuRatio = 0.2, frecButtonCubits = 3.2 * cubit, menuButtonCubits = 2
		* cubit;
sf::Vector2f gameSize = sf::Vector2f(1920, 1080);
sf::Vector2f menuPos = sf::Vector2f(gameSize.x - (gameSize.x * menuRatio), 0);

// The position is relative to the top left of the menu region,
// so zero is used as the start menu height
sf::Vector2f menuPosition(float xCubits, float yCubits) {
	return sf::Vector2f(menuPos.x + (xCubits * cubit),
			menuPos.y + (yCubits * cubit));
}

GameMenuController::GameMenuController(sf::RenderWindow* windowPointer, Timer* timer) :
		windowPointer(windowPointer), timer(timer) {
	// -----------------------
	// Menu Borders
	// -----------------------
	sf::RectangleShape* _drawable = new sf::RectangleShape(
			sf::Vector2f(gameSize.x - menuPos.x, gameSize.y));
	_drawable->setFillColor(sf::Color(0, 37, 105)); // tri-blue
	_drawable->setPosition(menuPos.x, 0);
	_drawable->setOutlineThickness(-14);
	_drawable->setOutlineColor(sf::Color(210, 16, 52)); //tri-red
	drawVec.push_back(_drawable);

	// -----------------------
	// Frec Buttons
	// -----------------------
	sf::Texture* _texture = new sf::Texture;
	if (!_texture->loadFromFile("assets/frec_texture.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	texturesVector.push_back(_texture);
	std::cerr << menuPos.x << ", " << menuPos.y << std::endl;
	FrecButton* _clickable = new FrecButton(menuPosition(1.667, 2.5),
			frecButtonCubits / 2, _texture);
	_clickable->setTextureRect(sf::IntRect(220 * 0, 0, 220, 250));
	clickVec.push_back(_clickable);

	_clickable = new FrecButton(menuPosition(1.667, 6), frecButtonCubits / 2,
			_texture);
	_clickable->setTextureRect(sf::IntRect(220 * 1, 0, 220, 250));
	clickVec.push_back(_clickable);

	_clickable = new FrecButton(menuPosition(1.667, 9.5), frecButtonCubits / 2,
			_texture);
	_clickable->setTextureRect(sf::IntRect(220 * 2, 0, 220, 250));
	clickVec.push_back(_clickable);

	// -------------------------
	// Menu Buttons
	// -------------------------
	sf::Texture* _menuTexture = new sf::Texture;
	if (!_menuTexture->loadFromFile("assets/menuInfo.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	texturesVector.push_back(_menuTexture);

	music = new sf::Music;
	if (!music->openFromFile("assets/give_it_up.ogg"))
		std::cerr << "The music file was not found" << std::endl;
	music->setLoop(true);
	MenuButton* _sound = new VolumeButton(menuPosition(0.3, 0.3), 107, 98,
			_menuTexture, 0, music);
	_sound->setTextureRect(sf::IntRect(888, 9, 107, 98));
	clickVec.push_back(_sound);
	MenuButton* _help = new MenuButton(menuPosition(2.3, 0.3), 107, 98,
			_menuTexture, 1);
	_help->setTextureRect(sf::IntRect(887, 143, 107, 98));
	clickVec.push_back(_help);
	MenuButton* _pause = new PauseButton(menuPosition(4.3, 0.3), 107, 98,
			_menuTexture, 2, timer);
	_pause->setTextureRect(sf::IntRect(888, 277, 107, 98));
	clickVec.push_back(_pause);

}

GameMenuController::~GameMenuController() {
	for (sf::Drawable* d : drawVec) {
		delete d;
	}
	for (Clickable* c : clickVec) {
		sf::Vector2f temp = c->getPosition();
		temp.x = (temp.x - menuPos.x) / cubit;
		temp.y = (temp.y - menuPos.y) / cubit;
		cout << "Clickable Cubits: (" << temp.x << ", " << temp.y << ")"
				<< endl;
		delete c;
	}
	for (sf::Texture* t : texturesVector) {
		delete t;
	}

	// Delete menu assets
	music->stop();
}

void GameMenuController::setDebug(bool mode) {
	if (mode) {
		for (Clickable* c : clickVec) {
			c->setDebug(true);
		}
	}
}

void GameMenuController::process(sf::Event event, sf::Vector2i mousePos) {
	// Handle windowPointer events
	for (Clickable* c : clickVec) {
		c->process(event, mousePos);
	}
}

void GameMenuController::update() {
}
void GameMenuController::render() {
	for (sf::Drawable* d : drawVec) {
		windowPointer->draw(*d);
	}
	for (Clickable* c : clickVec) {
		c->render(*windowPointer);
	}
}

