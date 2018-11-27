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
				sf::IntRect(0, 0, 130, 130), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier, FroshType::slow);
		break;
	case FroshType::regular:
		props = gameState->getFroshProps(type);
		frosh = std::make_shared<Frosh>(position, froshBaseSize, froshSprites,
				sf::IntRect(0, 130, 130, 130), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier, FroshType::regular);
		break;
	case FroshType::fast:
		props = gameState->getFroshProps(type);
		frosh = std::make_shared<Frosh>(position, froshBaseSize, froshSprites,
				sf::IntRect(0, 260, 130, 130), props["tam"] * modifier,
				props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifier, FroshType::fast);
		break;
	}
	froshVec->push_back(frosh);
	std::cout << "Frosh added" << std::endl;
	return frosh;
}

int counter = 90;
int wave = 1;
void FroshController::froshWave(int number, FroshType type){
	//if (froshCount < 4*number){
		spawnFrosh(sf::Vector2f(875,0), type);
		//::froshCount++;
	}
//}

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
	if (::counter == 1500){
		::counter = 0;
		::wave = 2;
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
	if (::counter == 1000){
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

//		if (::counter == 50) {
//			froshWave(3, FroshType::slow);
//		} else if (::counter == 100) {
//			froshWave(3, FroshType::regular);
//		} else if (::counter == 150) {
//			froshWave(3, FroshType::fast);
//			::counter = 0;
//		}
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
			//string froshType = ToString(frosh->getFroshType());

			int y;
			FroshType type = frosh->getFroshType();
			if(type == FroshType::slow) {
				y = 0;
			} else if (type == FroshType::regular) {
				y = 130;
			} else if (type == FroshType::fast) {
				y = 260;
			} else {
				y = 75;
			}


			if (distancePos.x > 0) {
				currentPos.x += pixelSpeed;
				frosh->setTextureRect(sf::IntRect(260, y, 130, 130));
			} else if (distancePos.x < 0) {
				currentPos.x -= pixelSpeed;
				frosh->setTextureRect(sf::IntRect(260, y, -130, 130));
			} else if (distancePos.y > 0) {
				currentPos.y += pixelSpeed;
				frosh->setTextureRect(sf::IntRect(0, y, 130, 130));
			} else if (distancePos.y < 0) {
				currentPos.y -= pixelSpeed;
				frosh->setTextureRect(sf::IntRect(0, y, 130, 130));
			}
			frosh->setPosition(currentPos);
		}
	}
	updateFrosh();
	::counter++;
}
/*
void FroshController::turnFrosh(shared_ptr<Frosh> frosh, sf::IntRect _textureRect, int direction){
	frosh->getTextureRect();

	int x = 0;
	int y = 0;
	char froshType = ToString(frosh->getFroshtype());

	switch(froshType) {
		case "slow":  y=0;
		case "regular": y=130;
		case "fast": y=260;
	}

	//1 means down, 2 means right
	switch(direction) {
	case 1: x = 0;
	case 2: x = 1;
	}
	frosh->setTextureRect(sf::IntRect());

	if(froshType == "regular") {
		frosh->setTextureRect(sf::IntRect(222, 120, 120, 120));
		frosh->setTextureRect(_textureRect);

	}
	//frosh->setTextureRect(sf::IntRect(222, 120, 120, 120));
	//frosh->setTextureRect(textureRect);
	frosh->setPosition(sf::Vector2f(100, 400));
}
*/

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
