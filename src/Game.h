/*
 * Game.h
 *
 *  Created on: Oct 22, 2018
 *      Author: Taffy
 */

#ifndef GAME_H_
#define GAME_H_

#include "SFML/Graphics.hpp"


class Game {
public:
	// Class variables
	sf::RenderWindow _window;

	Game();
//	virtual ~Game();
	void process();
	void update();
	void render();
	void run();
};

#endif /* GAME_H_ */
