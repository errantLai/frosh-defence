#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>

#include "Frec.h"
#include "throwProjectile.h"
#include "Frosh.h"

using namespace std;

class FrecAndFroshController {
public:
	FrecAndFroshController(vector<Frec*> allFrecs, vector<Frosh*> allFrosh);
	~FrecAndFroshController();
	//throwFrec Object
	void addThrowFrecToList(sf::Vector2f position, int index); //using string
	void deleteThrowFrecAtIndex(int index);
	//Throw Objects
	void addThrowObjectToList(int index, sf::Vector2f frecPosition,
			Frosh* froshPtr);
	void drawAllThrowObjectsOnGrid(sf::RenderWindow &theWindow);
	void deleteThrowObjectAtIndex(int index);
	void moveAllThrowObjectTowardsFroshAndDelete();
	void updateFrecFroshRange();

	//used for testing
	void addFroshObjectToList(sf::Vector2f _position, sf::Vector2f _size,
			sf::Texture* _texture, int type, double modifier);

	void process();
	void render(sf::RenderWindow &_window);
private:
	vector<throwProjectile*> allThrowObjects;

	vector<Frec*> allThrowFrecs;
	vector<Frec*> allThrowFrecsInRangeOfFrosh;

	vector<Frosh*> allFroshInRangeOfFrecs;
	vector<Frosh*> allFrosh;

	bool collisionDetected(Frec*, Frosh*);

	//vector<unique_ptr<Frec>> allTSlamFrecs;
//vector<unique_ptr<Frec>> allSkipFrecs;
	//vector<unique_ptr<Frec>> allSlamObjects;
//vector<unique_ptr<Frec>> allSkipObjects;
};

