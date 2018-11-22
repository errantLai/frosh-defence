/*
 * FroshController.h
 *
 *  Created on: Nov 22, 2018
 *      Author: Chris
 */

#ifndef FROSHCONTROLLER_H_
#define FROSHCONTROLLER_H_
#include "Frosh.h"
#include "GameState.h"
#include "GameController.h"
#include <SFML/Graphics.hpp>

class FroshController {
private:
	sf::Texture* froshSprite1, froshSprite2, froshSprite3;
	sf::RenderWindow* window;
	GameState* gameState;
	// This is a difficulty modifer that affects the stats
	// of generated frosh. This is modified when waves change
	float modifier;

	std::vector<Frosh*> froshVec;
	std::vector<Point> pathToFollow;
	// Create references to textures
	void initialize();

public:
	FroshController(sf::RenderWindow* windowPointer, GameState* gameState);
	// This destroys all the frosh that it contains
	virtual ~FroshController();
	// This creates a frosh and puts it into the froshVec
	Frosh* createFrosh(sf::Vector2f _position, sf::Vector2f _size,
			sf::Texture* _texture, int _tam, int _health, int _damage);
	// This removes a frosh from the vector, deleting it.
	void removeFrosh(Frosh* targetFrosh);
	// Used by the attackController to deal damage. This function
	// is responsible for updating the state of the frosh, as well
	// as increasing the Tam value when a frosh is defeated
	void dealDamage(Frosh* frosh, int damage);

	// Game functions
	void update();
	// Displays all the contained frosh on the board
	void render();

	// Accessors
	float getModifier();
	float setModifier();
	std::vector<Frosh*> getFroshVec();
};

#endif /* FROSHCONTROLLER_H_ */
