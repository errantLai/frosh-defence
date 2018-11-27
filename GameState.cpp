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
#include "Timer.h"
#include "Frec.h"

const int FPS = 30;

GameState::GameState(Timer* timer) :
		timer(timer) {
	frecProps[FrecType::slammer]= { {"tam", 30}, {"damage", 15}, {"range", 200}, {"cooldown", 1.5*FPS}};
	frecProps[FrecType::swinger]= { {"tam", 50}, {"damage", 50}, {"range", 125}, {"cooldown", 3*FPS}};
	frecProps[FrecType::thrower]= { {"tam", 40}, {"damage", 10}, {"range", 300}, {"cooldown", 1.25*FPS}};

	froshProps[FroshType::slow]= { {"tam", 1}, {"health", 60}, {"damage", 3}, {"speed", 2}};
	froshProps[FroshType::regular]= { {"tam", 2}, {"health", 30}, {"damage", 2}, {"speed", 3.6}};
	froshProps[FroshType::fast]= { {"tam", 3}, {"health", 15}, {"damage", 1}, {"speed", 5}};
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
void GameState::updateHealthBy(int update) {
	this->health += update;
	dirtyBit = true;
}

// Update Player Currency
void GameState::updateTamBy(int update) {
	this->tams += update;
	dirtyBit = true;
}

FrecType GameState::getPurchaseFrec() {
	return this->purchaseFrec;
}

void GameState::setPurchaseFrec(FrecType frecType) {
	this->purchaseFrec = frecType;
}

Frec* GameState::getBoardFrec() {
	return this->boardFrec;
}
void GameState::setBoardFrec(Frec* frec) {
	this->boardFrec = frec;
}

void GameState::setCurrentWave(int wave) {
	this->currentWave = wave;
}

std::map<string, int> GameState::getFrecProps(FrecType type) {
	return this->frecProps[type];
}

std::map<string, int> GameState::getFroshProps(FroshType type) {
	return this->froshProps[type];
}

void GameState::startGame() {
}

void GameState::endGame() {
}

void GameState::toggleHelpScreen() {
	this->helperState = !helperState;
}

GameState::~GameState() {
}

