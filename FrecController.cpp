/*
 * FrecController.cpp
 *
 *  Created on: Nov 24, 2018
 *      Author: Chris
 */

#include "FrecController.h"

FrecController::FrecController(sf::RenderWindow* _window, GameState* _gameState) :
		window(_window), gameState(_gameState) {
	frecThrowTexture = new sf::Texture;
	frecThrowTexture->loadFromFile("assets/ThrowingFrecSprite.png");
}

FrecController::~FrecController() {
	for (Frec* frec : frecVec) {
		delete frec;
		frec = nullptr;
	}
	delete frecThrowTexture;
	frecThrowTexture = nullptr;
}

Frec* FrecController::spawnFrec(sf::Vector2f position, FrecType type) {
	Frec* frec;
	std::map<string, int> props;
	switch (type) {
	case FrecType::empty:
		break;
	case FrecType::slammer:
		frec = new Frec(position, frecThrowTexture);
		break;
	case FrecType::swinger:
		frec = new Frec(position, frecThrowTexture);
		break;
	case FrecType::thrower:
		frec = new Frec(position, frecThrowTexture);
		break;
	}
	frecVec.push_back(frec);
	return frec;
}

void FrecController::update() {
}

void FrecController::render() {
	for (Frec* frec : frecVec) {
		window->draw(frec->getFrecSprite());
	}
}

std::vector<Frec*> FrecController::getFrecVec() {
	return this->frecVec;
}
