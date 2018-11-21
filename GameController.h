/*
 * GameController.h
 *
 *  Created on: Nov 6, 2018
 *      Author: Connor
 */
#pragma once

// Game Controller keeps all Game State Variables Running and Updated
class GameController {
private:
	int health;
	int tams;
	int currentWave;
	int froshRemaining;
	int froshEliminated;

public:
	GameController();

	//Accessors
	int getHealth();
	int getTams();
	int getCurrentWave();
	int getFroshRemaining();
	int getFroshEliminated();

	void startGame();				// Starts game
	void endGame();					// Ends game
	void startWave();				// Starts wave
	void displayHelpScreen();		// Display help
	void updateHealth(int update);	// Update player lives
	void updateTam(int update);		// Update player currency

	void process();
	void update();
	void render();
};

// Game Board generates the map
class GameBoard {
public:
	GameBoard();

	void initBoard();		// Create board
	void renderBoard();		// Render board
	void renderHover(int mouseX, int mouseY, int range);
};

// Point Class is a simple point to help with Map Dynamics
class Point {
private:
	int x;
	int y;
public:
	Point(int xIn, int yIn);
	// Accessors
	int getX();
	int getY();
};
