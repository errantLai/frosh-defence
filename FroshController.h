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
#include <string>
#include <SFML/Graphics.hpp>

using std::string;

enum class FroshType {
	slow, regular, fast
};

class FroshController {
private:
	sf::Texture* froshSprites;
	sf::RenderWindow* window;
	GameState* gameState;

	sf::Vector2f froshBaseSize = sf::Vector2f(120, 120);
	std::map<string, std::map<string, int>> froshProps;
	// This is a difficulty modifer that affects the stats
	// of generated frosh. This is modified when waves change
	float modifier;
	std::vector<Frosh*> froshVec;
	const std::vector<sf::Vector2f> pathInCubits;

public:
	FroshController() = delete;
	FroshController(sf::RenderWindow* window, GameState* gameState,
			const std::vector<sf::Vector2f> pathToFollow);
	// This destroys all the frosh that it contains
	virtual ~FroshController();

	Frosh* spawnFrosh(sf::Vector2f position, FroshType type);
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
	void setModifier(float _modifier);
	std::vector<Frosh*> getFroshVec();
};

#endif /* FROSHCONTROLLER_H_ */
