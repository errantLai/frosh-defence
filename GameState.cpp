/*
 * GameState.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: Chris
 *
 *  This class is responsible for holding all
 *  shared game state properties, allowing for
 *  communication and shared values between different
 *  controllers.
 */

#include "GameState.h"

GameState::GameState(Timer* timer) :
		timer(timer) {

}

// Game State Accessors
int GameState::getHealth() {
	return this->health;
}
int GameState::getTams() {
	return this->tams;
}
int GameState::getCurrentWave() {
	return this->currentWave;
}
int GameState::getFroshRemaining() {
	return this->froshRemaining;
}
int GameState::getFroshEliminated() {
	return this->froshEliminated;
}
bool GameState::getHelperState() {
	return this->helperState;
}

// Start Next Wave
void GameState::startWave() {
	this->currentWave++;
	dirtyBit = true;
}

// Update Player Lives
void GameState::updateHealth(int update) {
	this->health += update;
	dirtyBit = true;
}

// Update Player Currency
void GameState::updateTam(int update) {
	this->tams += update;
}

void GameState::toggleHelpScreen() {
	this->helperState = !helperState;
}

GameState::~GameState() {
}

