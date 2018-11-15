/*
 * GameMenuController.h
 *
 *  Created on: Nov 9, 2018
 *      Author: Taffy
 */

#ifndef GAMEMENUCONTROLLER_H_
#define GAMEMENUCONTROLLER_H_
#include "Clickable.h"
#include <vector>

class GameMenuController {
public:
	GameMenuController(sf::RenderWindow* windowPointer);
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
};

#endif /* GAMEMENUCONTROLLER_H_ */
