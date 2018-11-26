/*
 * GameState.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Chris
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include "Timer.h"
#include "Frec.h"

enum class FroshType {
	slow, regular, fast
};

class GameState {
private:
	// This contains info about frec pricing, damage, etc
	std::map<FrecType, std::map<string, int>> frecProps;
	std::map<FroshType, std::map<string, int>> froshProps;

	// Should the help menu be active
	bool helperState = true;

	int health = 20;
	int tams = 100;
	int currentWave = 1;
	int froshRemaining = -1;
	int froshEliminated = 0;

	FrecType purchaseFrec = FrecType::empty;
	// This is used by the upgrade button
	Frec* boardFrec = nullptr;

public:
	GameState(Timer* timer);
	virtual ~GameState();
	// This is the pixel length of a cubit
	const int cubit = 60;
	bool dirtyBit = true;
	Timer* timer;
	sf::Vector2i mousePos;

	//Accessors
	int getHealth();
	int getTams();
	int getCurrentWave();
	int getFroshRemaining();
	int getFroshEliminated();
	bool getHelperState();
	// This is used by the GameMenuController to determine opacity
	FrecType getPurchaseFrec();
	void setPurchaseFrec(FrecType frecType);

	std::map<string, int> getFrecProps(FrecType type);
	std::map<string, int> getFroshProps(FroshType type);

	void startGame();				// Starts game
	void endGame();					// Ends game
	void startWave();				// Starts wave
	void updateHealthBy(int update);	// Update player lives
	void updateTamBy(int update);		// Update player currency
	void toggleHelpScreen();

};

#endif /* GAMESTATE_H_ */
