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

public:
	GameController();

	void process();
	void update();
	void render();
};

// Game Board generates the map
class GameBoard {
public:
	GameBoard();

	void init();		// Create board
	void process(sf::Event event, sf::Vector2i mousePos);
	bool validatePos(int mouseX, int mouseY, int range);
	void render();		// Render board
	void renderHover(int mouseX, int mouseY, int range);
	void renderShadow(int mouseX, int mouseY, int ranger);
	int gridStatus[32][18] = { 0 };
};
