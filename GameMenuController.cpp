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

// The position is relative to the top left of the menu region,
// so zero is used as the start menu height
sf::Vector2f GameMenuController::menuPosition(float xCubits, float yCubits) {
	return sf::Vector2f(menuPos.x + (xCubits * cubit),
			menuPos.y + (yCubits * cubit));
}

sf::Vector2f GameMenuController::getMenuPos() {
	return this->menuPos;
}

GameMenuController::GameMenuController(sf::RenderWindow* windowPointer,
		GameState* gameState) :
		windowPointer(windowPointer), gameState(gameState) {
	cubit = gameState->cubit;
	float menuRatio = 0.2, frecButtonCubits = 1.9 * cubit, menuButtonCubits =
			1.8 * cubit;

	gameSize = sf::Vector2f(windowPointer->getSize());
	menuPos = sf::Vector2f(gameSize.x - (gameSize.x * menuRatio), 0);
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
	if (!_texture->loadFromFile("assets/FrecIcon3.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	texturesVector.push_back(_texture);
	std::cerr << menuPos.x << ", " << menuPos.y << std::endl;
	FrecButton* _clickable;
	_clickable = new FrecButton(menuPosition(1.4, 2.2), frecButtonCubits,
			_texture, "20T", "Damage: 1\nRate: 1s", FrecType::thrower,
			gameState);
	_clickable->setTextureRect(sf::IntRect(512 * 0, 0, 512, 512));
	frecButtonVec.push_back(_clickable);

	_clickable = new FrecButton(menuPosition(1.4, 6.2), frecButtonCubits,
			_texture, "30T", "Damage: 2\nRate: 2s", FrecType::slammer,
			gameState);
	_clickable->setTextureRect(sf::IntRect(512 * 1, 0, 512, 512));
	frecButtonVec.push_back(_clickable);

	_clickable = new FrecButton(menuPosition(1.4, 10.2), frecButtonCubits,
			_texture, "40T", "Damage: 3\nRate: 2s", FrecType::swinger,
			gameState);
	_clickable->setTextureRect(sf::IntRect(512 * 2, 0, 512, 512));
	frecButtonVec.push_back(_clickable);

	// -------------------------
	// Menu Buttons
	// -------------------------
	sf::Texture* _menuTexture = new sf::Texture;
	if (!_menuTexture->loadFromFile("assets/menuButtons.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	texturesVector.push_back(_menuTexture);

	music = new sf::Music;
	if (!music->openFromFile("assets/give_it_up.ogg"))
		std::cerr << "The music file was not found" << std::endl;
	music->setLoop(true);
	MenuButton* _sound = new VolumeButton(menuPosition(0.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, music);
	_sound->setTextureRect(sf::IntRect(896, 0, 128, 128));
	clickVec.push_back(_sound);
	MenuButton* _help = new InfoButton(menuPosition(2.35, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, gameState);
	_help->setTextureRect(sf::IntRect(896, 128, 128, 128));
	clickVec.push_back(_help);
	MenuButton* _pause = new PauseButton(menuPosition(4.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, gameState->timer);
	_pause->setTextureRect(sf::IntRect(896, 384, 128, 128));
	clickVec.push_back(_pause);
	UpgradeButton* _upgrade = new UpgradeButton(menuPosition(0.9, 14.3), 289,
			200, _menuTexture);
	_upgrade->setTextureRect(sf::IntRect(1056, 0, 224, 160));
	this->upgradeButton = _upgrade;
	clickVec.push_back(_upgrade);
}

GameMenuController::~GameMenuController() {
	for (sf::Drawable* d : drawVec) {
		delete d;
		d = nullptr;
	}
	for (Clickable* c : frecButtonVec) {
		sf::Vector2f temp = c->getPosition();
		temp.x = (temp.x - menuPos.x) / cubit;
		temp.y = (temp.y - menuPos.y) / cubit;
		cout << "Clickable Cubits: (" << temp.x << ", " << temp.y << ")"
				<< endl;
		delete c;
		c = nullptr;
	}
	for (Clickable* c : clickVec) {
		sf::Vector2f temp = c->getPosition();
		temp.x = (temp.x - menuPos.x) / cubit;
		temp.y = (temp.y - menuPos.y) / cubit;
		cout << "Clickable Cubits: (" << temp.x << ", " << temp.y << ")"
				<< endl;
		delete c;
		c = nullptr;
	}
	for (sf::Texture* t : texturesVector) {
		delete t;
		t = nullptr;
	}

	// Delete menu assets
	music->stop();
}

void GameMenuController::setDebug(bool mode) {
	if (mode) {
		for (Clickable* c : frecButtonVec) {
			c->setDebug(true);
		}
		for (Clickable* c : clickVec) {
			c->setDebug(true);
		}
	}
}

// Handle windowPointer events
void GameMenuController::process(sf::Event event, sf::Vector2i mousePos) {
	// Clear the selectedFrec if the menu is selected
	if ((mousePos.x >= menuPos.x)
			&& gameState->getPurchaseFrec() != FrecType::empty
			&& (event.type == sf::Event::MouseButtonPressed)
			&& (event.mouseButton.button == sf::Mouse::Left)) {
		gameState->setPurchaseFrec(FrecType::empty);
	}
	for (Clickable* c : frecButtonVec) {
		c->process(event, mousePos);
	}
	for (Clickable* c : clickVec) {
		c->process(event, mousePos);
	}
}

void GameMenuController::update() {
	// TODO: Check the upgrade cost of the frec to toggle opacity
	if (gameState->getBoardFrec() != nullptr) {
		upgradeButton->setTransparency(255);
	} else {
		upgradeButton->setTransparency(180);
	}
	for (FrecButton* f : frecButtonVec) {
		if (f->getFrecType() == gameState->getPurchaseFrec()) {
			f->setTransparency(255);
		} else {
			f->setTransparency(180);
		}
	}
}
void GameMenuController::render() {
	for (sf::Drawable* d : drawVec) {
		windowPointer->draw(*d);
	}
	for (Clickable* c : frecButtonVec) {
		c->render(*windowPointer);
	}
	for (Clickable* c : clickVec) {
		c->render(*windowPointer);
	}
}

