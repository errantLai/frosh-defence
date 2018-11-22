/*
 * GameState.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Chris
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include "Timer.h"

class GameState {
private:
	int health = 20;
	int tams = 100;
	int currentWave = 1;
	int froshRemaining = -1;
	int froshEliminated = 0;
	bool helperState = true;

public:
	GameState(Timer* timer);
	virtual ~GameState();
	bool dirtyBit = true;
	//Accessors
	int getHealth();
	int getTams();
	int getCurrentWave();
	int getFroshRemaining();
	int getFroshEliminated();
	bool getHelperState();
	Timer* timer;

	void startGame();				// Starts game
	void endGame();					// Ends game
	void startWave();				// Starts wave
	void displayHelpScreen();		// Display help
	void updateHealth(int update);	// Update player lives
	void updateTam(int update);		// Update player currency
	void toggleHelpScreen();

};

#endif /* GAMESTATE_H_ */
