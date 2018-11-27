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
	slammerTexture = new sf::Texture;
	swingerTexture = new sf::Texture;
	throwerTexture = new sf::Texture;
	slammerTexture->loadFromFile("assets/SlammingFrecSprite.png");
	swingerTexture->loadFromFile("assets/SwingFrecSprite.png");
	throwerTexture->loadFromFile("assets/ThrowingFrecSprite.png");
	frecVec = new std::vector<Frec*>;
}

FrecController::~FrecController() {
	for (Frec* frec : *frecVec) {
		delete frec;
		frec = nullptr;
	}
	delete slammerTexture;
	delete swingerTexture;
	delete throwerTexture;
}

Frec* FrecController::spawnFrec(sf::Vector2f position, FrecType type) {
	Frec* frec;
	sf::Texture* texture = slammerTexture; //visual studio wants texture to be initilized to something
	if (type == FrecType::empty) {
		return nullptr;
	} else if (type == FrecType::slammer) {
		texture = slammerTexture;
	} else if (type == FrecType::swinger) {
		texture = swingerTexture;
	} else if (type == FrecType::thrower) {
		texture = throwerTexture;
	}
	std::map<string, int> props = gameState->getFrecProps(type);
	frec = new Frec(position, texture, type, props["damage"], props["range"],
			props["cooldown"]);
	frecVec->push_back(frec);
	std::cout << frecVec->size() << std::endl;
	return frec;
}

void FrecController::process(const sf::Event& event,
		const sf::Vector2i& mousePos) {
	for (Frec* frec : *frecVec) {
		frec->process(event, mousePos);
		if (frec->wasClicked) {
			gameState->setBoardFrec(frec);
			gameState->setPurchaseFrec(FrecType::empty);
			frec->wasClicked = false;
		}
	}
}

void FrecController::update() {
}

void FrecController::render() {
	sf::CircleShape range;
	sf::Vector2f pos;
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::Red);
	range.setOutlineThickness(-3);
	for (Frec* frec : *frecVec) {
		window->draw(frec->getFrecSprite());
		if(gameState->getBoardFrec() == frec){
			pos = frec->getCenterPosition();
					range.setRadius(frec->getRange());
					pos.x -= (frec->getRange());
					pos.y -= (frec->getRange());

					range.setPosition(pos);
					window->draw(range);
		}
	}
}

std::vector<Frec*>* FrecController::getFrecVec() {
	return this->frecVec;
}

