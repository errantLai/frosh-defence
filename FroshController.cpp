/*
 * FroshController.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: Chris
 */

#include "FroshController.h"
#include "Frosh.h"
#include <iostream>
#include <algorithm> // remove and remove_if

FroshController::FroshController(sf::RenderWindow* _window,
		GameState* _gameState, const std::vector<sf::Vector2f> _path) :
		window(_window), gameState(_gameState), pathInCubits(_path) {
	froshVec = new std::vector<Frosh*>;
	modifier = 1;
	froshSprites = new sf::Texture;
	if (!froshSprites->loadFromFile("assets/FroshSprite.png")) {
		std::cerr << "The frosh texture could not be loaded" << std::endl;
	}

	froshProps["slow"]= { {"tam", 1}, {"health", 30}, {"damage", 3}, {"speed", 1}};
	froshProps["regular"]= { {"tam", 2}, {"health", 20}, {"damage", 2}, {"speed", 1.8}};
	froshProps["fast"]= { {"tam", 3}, {"health", 10}, {"damage", 1}, {"speed", 2.6}};
}

FroshController::~FroshController() {
	for (Frosh* frosh : *froshVec) {
		delete frosh;
		frosh = nullptr;
	}
	delete froshSprites;
	froshSprites = nullptr;
}

Frosh* FroshController::spawnFrosh(sf::Vector2f position, FroshType type) {
	Frosh* frosh;
	std::map<string, int> props;
	switch (type) {
	case FroshType::slow:
		props = froshProps["slow"];
		frosh = new Frosh(position, froshBaseSize, froshSprites,
				sf::IntRect(0, 0, 120, 120), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier);
		break;
	case FroshType::regular:
		props = froshProps["regular"];
		frosh = new Frosh(position, froshBaseSize, froshSprites,
				sf::IntRect(0, 130, 120, 120), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier);
		break;
	case FroshType::fast:
		props = froshProps["fast"];
		frosh = new Frosh(position, froshBaseSize, froshSprites,
				sf::IntRect(0, 260, 120, 120), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier);
		break;
	}
	froshVec->push_back(frosh);
	std::cout << "Frosh added" << std::endl;
	return frosh;
}
int counter = 90;


void FroshController::removeFrosh(Frosh* targetFrosh) {
	// This is an acceptable computational cost due to rarity of action.
	// O(N) for each deletion
	for (int i = 0, size = froshVec->size(); i < size; i++) {
		if ((*froshVec)[i] == targetFrosh) {
			delete (*froshVec)[i];
			(*froshVec)[i] = nullptr; // CYA
			froshVec->erase(froshVec->begin() + i);
			break;
		}
	}
}

void FroshController::dealDamage(Frosh* frosh, int damage) {
	if (frosh->reduceHealth(damage) <= 0) {
		gameState->updateTamBy(frosh->getTamValue());
		removeFrosh(frosh);
	}
}

void FroshController::update() {
	// Go through each frosh object, and find the best point.
	// Follow that path! This is a simple implementation, which
	// relies on the fact that all paths follow linear changes,
	// aka no need for diagonal travel.
    int size = froshVec->size();
    if (size < 10){

    	if (::counter > 99 && :: counter < 101){
    		spawnFrosh(sf::Vector2f(875,0), FroshType::slow);
    		std::cout << size << std::endl;
    	}
    	else if (::counter > 199  && ::counter < 201){
    		spawnFrosh(sf::Vector2f(875, 0), FroshType::regular);
    		std::cout << size << std::endl;
    		std::cout << "Regular" << std::endl;
    	}
    	else if (::counter > 299 && ::counter < 301){
    		spawnFrosh(sf::Vector2f(875, 0), FroshType::fast);
    		::counter = 0;
    		std::cout << size << std::endl;
    		std::cout << "Fast" << std::endl;
    		std::cout << ::counter << std::endl;
    	}
    }
    //std::cout <<  ::counter << std::endl;
	sf::Vector2f currentPos, targetPos, distancePos;
	int cubit = gameState->cubit;
	int maxPathIndex = pathInCubits.size() - 1;
	float pixelSpeed;
	for (Frosh* frosh : *froshVec) {
		if (frosh->getPathIndex() == maxPathIndex) {
			gameState->updateHealthBy(-(frosh->getDamage()));
			removeFrosh(frosh);
			break;
		}
		currentPos = frosh->getPosition();
		targetPos = pathInCubits[frosh->getPathIndex()];
		// Convert the path vector to one in cubits
		targetPos = sf::Vector2f(
				(pathInCubits[frosh->getPathIndex()].x * cubit) - cubit / 2,
				(pathInCubits[frosh->getPathIndex()].y * cubit) - cubit / 2);
		distancePos = targetPos - currentPos;

		if (distancePos.x == 0 && distancePos.y == 0) {
			frosh->increasePathIndex();
		} else {
			pixelSpeed = frosh->getPixelSpeed();
			// Deal with excess movements
			if (distancePos.x != 0 && (abs(distancePos.x) < pixelSpeed)) {
				pixelSpeed = abs(distancePos.x);
			} else if (distancePos.y != 0 && abs(distancePos.y) < pixelSpeed) {
				pixelSpeed = abs(distancePos.y);
			}

			//In each of these indexes, change the frosh sprite to reflect direction
			if (distancePos.x > 0) {
				currentPos.x += pixelSpeed;
				//frosh->setTextureRect(sf::IntRect(120, 0, 120, 120));
			} else if (distancePos.x < 0) {
				currentPos.x -= pixelSpeed;
				//frosh->setTextureRect(sf::IntRect(120, 0, 120, 120));
			} else if (distancePos.y > 0) {
				currentPos.y += pixelSpeed;
				//frosh->setTextureRect(sf::IntRect(0, 0, 120, 120));
			} else if (distancePos.y < 0) {
				currentPos.y -= pixelSpeed;
				//frosh->setTextureRect(sf::IntRect(0, 0, 120, 120));
			}
			frosh->setPosition(currentPos);
		}
	}
	::counter++;
}

void FroshController::render() {
	for (Frosh* frosh : *froshVec) {
		frosh->render(window);
	}
}

float FroshController::getModifier() {
	return this->modifier;
}

void FroshController::setModifier(float _modifier) {
	this->modifier = _modifier;
}

std::vector<Frosh*>* FroshController::getFroshVec() {
	return this->froshVec;
}
