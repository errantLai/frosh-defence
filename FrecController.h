/*
 * FrecController.h
 *
 *  Created on: Nov 24, 2018
 *      Author: Chris
 */

#ifndef FRECCONTROLLER_H_
#define FRECCONTROLLER_H_
#include "Frec.h"
#include "GameState.h"
#include <string>
#include <SFML/Graphics.hpp>

using std::string;

class FrecController {
public:
	sf::Texture* frecThrowTexture;
	sf::RenderWindow* window;
	GameState* gameState;

	sf::Vector2f frecBaseSize = sf::Vector2f(120, 120);
	// Contains all active frec pointers
	std::vector<Frec*> frecVec;
	// This contains info about frec pricing, damage, etc
	std::map<FrecType, std::map<string, int>> frecProps;

public:
	FrecController() = delete;
	FrecController(sf::RenderWindow* window, GameState* gameState);
	// This destroys all the frecs that it contains
	virtual ~FrecController();

	Frec* spawnFrec(sf::Vector2f position, FrecType type);
	// Game functions
	void update();
	// Displays all the contained frec on the board
	void render();

	// Accessors
	std::vector<Frec*> getFrecVec();
	std::map<string, int> getFrecProps(FrecType type);

};

#endif /* FRECCONTROLLER_H_ */
