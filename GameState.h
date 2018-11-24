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

enum class FrecType {
	empty, slammer, swinger, thrower
};

class GameState {
private:
	int health = 20;
	int tams = 100;
	int currentWave = 1;
	int froshRemaining = -1;
	int froshEliminated = 0;
	bool helperState = true;
	// This is the pixel length of a cubit
	int cubit = 60;
	FrecType purchaseFrec = FrecType::empty;
	// This is used by the upgrade button
	Frec* boardFrec = nullptr;

public:
	GameState(Timer* timer);
	virtual ~GameState();
	bool dirtyBit = true;
	Timer* timer;

	//Accessors
	int getHealth();
	int getTams();
	int getCurrentWave();
	int getFroshRemaining();
	int getFroshEliminated();
	bool getHelperState();
	int getCubitLength();
	// This is used by the GameMenuController to determine opacity
	FrecType getPurchaseFrec();
	void setPurchaseFrec(FrecType frecType);

	void startGame();				// Starts game
	void endGame();					// Ends game
	void startWave();				// Starts wave
	void displayHelpScreen();		// Display help
	void updateHealthBy(int update);	// Update player lives
	void updateTamBy(int update);		// Update player currency
	void toggleHelpScreen();

};

#endif /* GAMESTATE_H_ */
