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
#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

FroshController::FroshController(sf::RenderWindow* _window,
		GameState* _gameState, const std::vector<sf::Vector2f> _path) :
		window(_window), gameState(_gameState), pathInCubits(_path) {
	froshVec = new std::vector<shared_ptr<Frosh>>;
	modifier = 1;
	froshSprites = new sf::Texture;
	if (!froshSprites->loadFromFile("assets/FroshSprite.png")) {
		std::cerr << "The frosh texture could not be loaded" << std::endl;
	}
}

FroshController::~FroshController() {
	// Shared pointers delete themselves
//	for (shared_ptr<Frosh> frosh : *froshVec) {
//		delete frosh;
//		frosh = nullptr;
//	}
//	delete froshSprites;
//	froshSprites = nullptr;
}

// This is used to produce frosh, and will be placed
// within the froshVec vector
shared_ptr<Frosh> FroshController::spawnFrosh(sf::Vector2f position,
		FroshType type) {
	shared_ptr<Frosh> frosh = nullptr;
	std::map<string, int> props;

	std::vector<std::map<string, int>> waveOne;
	waveOne.push_back( { { "count", 50 }, { "slow", 4 } });
	waveOne.push_back( { { "count", 120 }, { "regular", 4 }, {"fast", 2} });

	switch (type) {
	case FroshType::slow:
		props = gameState->getFroshProps(type);
		frosh = std::make_shared<Frosh>(position, froshBaseSize, froshSprites,
				sf::IntRect(0, 0, 120, 120), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier);
		break;
	case FroshType::regular:
		props = gameState->getFroshProps(type);
		frosh = std::make_shared<Frosh>(position, froshBaseSize, froshSprites,
				sf::IntRect(0, 130, 120, 120), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier);
		break;
	case FroshType::fast:
		props = gameState->getFroshProps(type);
		frosh = std::make_shared<Frosh>(position, froshBaseSize, froshSprites,
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
int wave = 1;
void FroshController::froshWave(int number, FroshType type){
		spawnFrosh(sf::Vector2f(875,0), type);
	}

void FroshController::waveOne()	{
	if (::counter == 50 || ::counter == 150 || ::counter == 300) {
		froshWave(3, FroshType::slow);
	}
	if (::counter == 100 || ::counter == 250 || ::counter == 350 || ::counter == 450 || ::counter == 500) {
		froshWave(3, FroshType::regular);
	}
	if (::counter == 200 || ::counter == 400 || ::counter == 550) {
		froshWave(3, FroshType::fast);
	}
	if (::counter == 1750){
		::counter = 0;
		::wave = 2;
		gameState->setCurrentWave(2);
	}
}

void FroshController::waveTwo()	{
	if (::counter == 50 || ::counter == 150 || ::counter == 300) {
		froshWave(3, FroshType::slow);
	}
	if (::counter == 100 || ::counter == 250 || ::counter == 350) {
		froshWave(3, FroshType::regular);
	}
	if (::counter == 200 || ::counter == 400 || ::counter == 550 || ::counter == 450 || ::counter == 500) {
		froshWave(3, FroshType::fast);
	}
}
// This goes through the array and releases all frosh objects
// whose health are < 0, erasing them from the vector
void FroshController::updateFrosh() {

}

// Deprecated. This causes unknown memory accesses
void FroshController::removeFrosh(shared_ptr<Frosh> targetFrosh) {
// This is an acceptable computational cost due to rarity of action.
// O(N) for each deletion
	for (int i = 0, size = froshVec->size(); i < size; i++) {
		if ((*froshVec)[i] == targetFrosh) {
			targetFrosh = nullptr;
			froshVec->erase(froshVec->begin() + i);
			break;
		}
	}
}

void FroshController::dealDamage(shared_ptr<Frosh> frosh, int damage) {
	if (frosh != nullptr && frosh->reduceHealth(damage) <= 0) {
		gameState->updateTamBy(frosh->getTamValue());
		removeFrosh(frosh);
		updateFrosh();
	}
}

void FroshController::update() {
// Go through each frosh object, and find the best point.
// Follow that path! This is a simple implementation, which
// relies on the fact that all paths follow linear changes,
// aka no need for diagonal travel.

	if (::wave == 1){
		waveOne();
	}
	else if (::wave == 2){
		waveTwo();
	}

	sf::Vector2f currentPos, targetPos, distancePos;
	int cubit = gameState->cubit;
	int maxPathIndex = pathInCubits.size();
	float pixelSpeed;
	for (shared_ptr<Frosh> frosh : *froshVec) {
		// Frosh has reached the finish line
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
	updateFrosh();
	::counter++;
}

void FroshController::render() {
	for (shared_ptr<Frosh> frosh : *froshVec) {
		frosh->render(window);
	}
}

float FroshController::getModifier() {
	return this->modifier;
}

void FroshController::setModifier(float _modifier) {
	this->modifier = _modifier;
}

std::vector<shared_ptr<Frosh>>* FroshController::getFroshVec() {
	return this->froshVec;
}
