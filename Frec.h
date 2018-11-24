﻿#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include<math.h>
#include <string>
#include <vector>

using namespace std;
typedef sf::IntRect* srcArrayPtr;

class ThrowingFrec
{
public:
	ThrowingFrec(const std::vector<float>);
	ThrowingFrec(const ThrowingFrec&);
	~ThrowingFrec();
	ThrowingFrec& operator=(const ThrowingFrec&);

	// accessors for attributes on stack
	char getDirection() const;
	char getMode() const;
	sf::Sprite getFrecSprite() const;
	sf::Vector2f getfrecPosition() const;
	float getSpeed() const;
	float getRange()const;
	float getDamage() const; 

	// accessors for attributes on heap
	srcArrayPtr* getIntRects() const;
	
	// functionals
	void setMode(char);
	void setDirection(char);
	void froshDirection(sf::Vector2f froshPos); // find the direction of the frosh relative to the frec
	float froshDistance(sf::Vector2f frosh); // returns distance between two points
	bool froshCollides(sf::Vector2f frosh); // collision detection between two objects, using the distance function
	void Attack();
	void StopAttack();
	void upgrade();
	void flipSprite();
	void flipBack();

	// test function
	void setPosition(std::vector<float>);

	/*
	// controller oriented functions
	void addFrecToList(std::string str, sf::Vector2f pos, sf::RenderWindow &windo);
	void drawAllFrecsOnBoard(sf::RenderWindow &theWindow);
	void removeFrecFromContainer(std::vector<std::shared_ptr<Frec>>& container, Frec &aFrec);
	*/

private:
	// sprites
	sf::Sprite frecSprite;
	sf::Texture frecTexture;
	sf::IntRect currentSprite;
	srcArrayPtr* srcSprite; // on heap
	std::vector<float> coordinate; // the frec position on map
	sf::Vector2f frecPos;
	int numPers = 3;
	int numFrame = 3;

	// the attributes about attack and frec properties
	char mode; // a - attack; s - stop attack
	char direction; // udlr -> up, down, left, right

	// modifed by the upgrade function
	float frecSpeed;
	float frecRange;
	float frecDamage;

	sf::CircleShape range; // the attack range shape

	// the attribute that i have no idea what its doing but looks important
	//std::list<std::shared_ptr<Frec>> frecList;
	// but it's giving me errors so oh well whatever

	// probably not gonna need these attributes
	sf::Clock animationClock;
};


class SlammingFrec
{
public:
	SlammingFrec(const std::vector<float>);
	//SlammingFrec(const SlammingFrec&);
	//virtual ~ThrowingFrec();
	//SlammingFrec& operator=(const SlammingFrec&);

	// accessors for attributes on heap
	char getDirection() const;
	char getMode() const;
	sf::Sprite getFrecSprite() const;
	sf::Vector2f getfrecPosition() const;
	float getSpeed() const;
	float getRange()const;
	float getDamage() const;

	void setMode(char);
	void setDirection(char);
	void froshDirection(sf::Vector2f froshPos); // find the direction of the frosh relative to the frec
	float froshDistance(sf::Vector2f frosh); // returns distance between two points
	bool froshCollides(sf::Vector2f frosh); // collision detection between two objects, using the distance function
	void Attack();
	void StopAttack();
	void upgrade();
	void flipSprite();
	void flipBack();


private:
	// sprites
	sf::Sprite frecSprite;
	sf::Texture frecTexture;
	int numPers = 3;
	int numFrame = 2;
	sf::IntRect currentSprite;
	srcArrayPtr* srcSprite;
	std::vector<float> coordinate; // the frec position on map
	sf::Vector2f frecPos;

	// the attributes about attack and frec properties
	char mode; // a - attack; s - stop attack
	char direction; // udlr -> up, down, left, right

	// modifed by the upgrade function
	float* frecAttributes; // [0] = speed; [1] = range; [2] = damage

	sf::CircleShape range; // the attack range shape

	// probably not gonna need these attributes
	sf::Clock animationClock;
};
// =====================


class SwingingFrec
{
public:
	SwingingFrec(const std::vector<float>);
	//SwingingFrec(const SwingingFrec&);
	//virtual ~ThrowingFrec();
	//SwingingFrec& operator=(const SwingingFrec&);

	// accessors for attributes on heap
	char getDirection();
	char getMode();
	sf::Sprite getFrecSprite();
	sf::Vector2f getfrecPosition();
	float getSpeed() const;
	float getRange()const;
	float getDamage() const;

	void setMode(char);
	void setDirection(char);
	void froshDirection(sf::Vector2f froshPos); // find the direction of the frosh relative to the frec
	float froshDistance(sf::Vector2f frosh); // returns distance between two points
	bool froshCollides(sf::Vector2f frosh); // collision detection between two objects, using the distance function
	void Attack();
	void StopAttack();
	void upgrade();
	void flipSprite();
	void flipBack();

	/*
	// controller oriented functions
	void addFrecToList(std::string str, sf::Vector2f pos, sf::RenderWindow &windo);
	void drawAllFrecsOnBoard(sf::RenderWindow &theWindow);
	void removeFrecFromContainer(std::vector<std::shared_ptr<Frec>>& container, Frec &aFrec);
	*/

private:
	// sprites
	sf::Sprite frecSprite;
	sf::Texture frecTexture;
	int numPers = 3;
	int numFrame = 2;
	sf::IntRect currentSprite;
	srcArrayPtr* srcSprite;
	std::vector<float> coordinate; // the frec position on map
	sf::Vector2f frecPos;

	// the attributes about attack and frec properties
	char mode; // a - attack; s - stop attack
	char direction; // udlr -> up, down, left, right
	// modifed by the upgrade function
	float* frecAttributes; // [0] = speed; [1] = range; [2] = damage

	sf::CircleShape range; // the attack range shape

	// the attribute that i have no idea what its doing but looks important
	//std::list<std::shared_ptr<Frec>> frecList;
	// but it's giving me errors so oh well whatever

	// probably not gonna need these attributes
	sf::Clock animationClock;
};