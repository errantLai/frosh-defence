/*
 * GameMenuController.h
 *
 *  Created on: Nov 9, 2018
 *      Author: Taffy
 */

#ifndef GAMEMENUCONTROLLER_H_
#define GAMEMENUCONTROLLER_H_
#include "Clickable.h"
#include "GameState.h"
#include <SFML/Audio.hpp>
#include <vector>

class GameMenuController {
public:
	GameMenuController(sf::RenderWindow* windowPointer, GameState* gameState);
	virtual ~GameMenuController();

	void setDebug(bool mode);
	void initialize();
	void run();
	void process(sf::Event event, sf::Vector2i mousePos);
	void update();
	void render();

private:
	std::vector<sf::Drawable*> drawVec;
	std::vector<Clickable*> clickVec;
	std::vector<sf::Texture*> texturesVector;
	sf::RenderWindow* windowPointer;
	sf::Music* music;
	GameState* gameState;
};

#endif /* GAMEMENUCONTROLLER_H_ */
