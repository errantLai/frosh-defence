/*
 * GameController.h
 *
 *  Created on: Nov 6, 2018
 *      Author: Connor
 */
#pragma once
#include "GameState.h"
#include "Frec.h"
#include "FrecController.h"

// Game Controller keeps all Game State Variables Running and Updated
class GameController {
private:

public:
	GameController();

	void process();
	void update();
	void render();
};

// Game Board generates the map, and handles interactions
// for any entities sitting on the map
class GameBoard {
private:
	GameState* gameState;
	FrecController* frecController;
	int width;

	// Helper functions
	bool gridSpaceAvailable(int gridX, int gridY);
	bool frecIsPurchasable(FrecType type);

public:
	GameBoard(GameState* gameState, FrecController* frecController,
			int widthInPixels);

	bool validatePos(int mouseX, int mouseY, int range);
	void process(sf::Event event, sf::Vector2i mousePos);
	void update();
	void render();		// Render board
	void renderRange(int mouseX, int mouseY, int range);
	void renderShadow(int mouseX, int mouseY, int range);
	int gridStatus[32][18] = { 0 };
};
