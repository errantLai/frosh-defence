/*
 * FrecController.cpp
 *
 *  Created on: Nov 24, 2018
 *      Author: Chris
 */

#include "Frec.h"
#include "FrecController.h"

FrecController::FrecController(sf::RenderWindow* _window, GameState* _gameState) :
		window(_window), gameState(_gameState) {
	frecThrowTexture = new sf::Texture;
	frecThrowTexture->loadFromFile("assets/ThrowingFrecSprite.png");
	frecVec = new std::vector<Frec*>;

	/*
	 - upgrades:
	 - Throw:
	 - damage *= 1.25; // up 25%
	 - range += 1;
	 - speed *= 1.25; // up 25%

	 - Slam:
	 - damage *= 1.5; // up 50%
	 - speed *= 1.25; // up 25%

	 - Swing:
	 - damage *= 1.4; // up 40%
	 - range += 1;
	 - speed *= 1.2; // up 20%
	 */

	frecProps[FrecType::slammer]= { {"tam", 10}, {"damage", 10}, {"range", 100}, {"cooldown", 25}};
	frecProps[FrecType::swinger]= { {"tam", 10}, {"damage", 5}, {"range", 200}, {"cooldown", 20}};
	frecProps[FrecType::thrower]= { {"tam", 10}, {"damage", 3}, {"range", 300}, {"cooldown", 25}};
}

FrecController::~FrecController() {
	for (Frec* frec : *frecVec) {
		delete frec;
		frec = nullptr;
	}
	delete frecThrowTexture;
	frecThrowTexture = nullptr;
}

Frec* FrecController::spawnFrec(sf::Vector2f position, FrecType type) {
	Frec* frec;
	if (type == FrecType::empty) {
		return nullptr;
	}
	std::map<string, int> props = frecProps[type];
	frec = new Frec(position, frecThrowTexture, type, props["damage"],
			props["range"], props["cooldown"]);
	frecVec->push_back(frec);
	std::cout << frecVec->size() << std::endl;
	return frec;
}

void FrecController::update() {
}

void FrecController::render() {
	sf::CircleShape range = sf::CircleShape(60);
	sf::Vector2f pos;
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::Red);
	range.setOutlineThickness(-3);
	for (Frec* frec : *frecVec) {
		pos = frec->getCenterPosition();
		window->draw(frec->getFrecSprite());
		range.setRadius(frec->getRange());
		pos.x -= (frec->getRange());
		pos.y -= (frec->getRange());

		range.setPosition(pos);
		window->draw(range);
	}
}

std::vector<Frec*>* FrecController::getFrecVec() {
	return this->frecVec;
}

std::map<string, int> FrecController::getFrecProps(FrecType type) {
	return this->frecProps[type];
}
