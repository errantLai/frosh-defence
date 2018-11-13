/*
 * GameController.h
 *
 *  Created on: Nov 6, 2018
 *      Author: Connor
 */
#pragma once

class GameController{
private:
	int health;
	int tams;
	int currentWave;
	int froshRemaining;
	int froshEliminated;

public:
	GameController();

	int getHealth();
	int getTams();
	int getCurrentWave();
	int getFroshRemaining();
	int getFroshEliminated();

	void startGame();
	void endGame();
	void startWave();
	void displayHelpScreen();
	void updateHealth(int update);
	void updateTam(int update);
};

class GameBoard{
public:
	GameBoard();

	void initBoard();
	void renderBoard();
	void renderHover(int mouseX, int mouseY, int range);
};

class Point{
private:
	int x;
	int y;
public:
	Point(int xIn, int yIn);
	int getX();
	int getY();
};
