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
	std::vector<Frec*>* frecVec;

public:
	FrecController() = delete;
	FrecController(sf::RenderWindow* window, GameState* gameState);
	// This destroys all the frecs that it contains
	virtual ~FrecController();

	Frec* spawnFrec(sf::Vector2f position, FrecType type);
	// Game functions

	void process(const sf::Event& event, const sf::Vector2i& mousePos);
	void update();
	// Displays all the contained frec on the board
	void render();

	// Accessors
	std::vector<Frec*>* getFrecVec();

};

#endif /* FRECCONTROLLER_H_ */
