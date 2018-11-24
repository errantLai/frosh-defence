// VisualStudioHelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Frec.h"
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
typedef sf::IntRect* srcArrayPtr;
/*

Notes
- still need to do:
	- work on the heap related functions [URGENT]
		- Put the attributes in array on heap [DONE]
		- write accessor return ptr to them
		- copy constructor
		- destructor
		- operator=
	- fill in the upgrade function [not very urgent]
	- draw the upgrade button [DONE]
	- in the constructor of each class, set their initial damage, range, attackspeed - [Work on this on Thursday]
	- use the tick for timing [not very urgent right now]
	- need to define sf::circleshape range [when displaying range]

- upgrades:
	- Throw:
		- damage *= 1.25; // up 25%
		- range += 1;
		- speed *= 1.25; // up 25%
	- Slam:
		- damage *= 1.5; // up 50%
		- speed *= 1.25; // up 25%
	- Swing:
		- damage *= 1.4; // up 40%
		- range += 1;
		- speed *= 1.2; // up 20%

*/


ThrowingFrec::ThrowingFrec(const std::vector<float> coordinateV) {
   // these can be changed to adapt to whichever frec spritesheet we are using
   // and to their sizes, as well as the coordinate
   frecTexture.loadFromFile("C:\\VisualStudioWork\\TryAnimation\\ThrowingFrecSprite.png");

   // set coordinate
   coordinate = coordinateV;

   // construct current sprite on the given position
   srcSprite = new srcArrayPtr[numPers];
   int x = 0;
   int y = 0;
   for (int i = 0; i < numPers; i++) {
	   srcSprite[i] = new sf::IntRect[numFrame];
	   for (int j = 0; j < numFrame; j++) {
		   srcSprite[i][j] = sf::IntRect(x, y, 128, 128);
		   x += 128;
	   }
	   y += 128;
	   x = 0;
   }

    currentSprite = srcSprite[0][0];
    frecSprite.setTexture(frecTexture);
    frecSprite.setTextureRect(currentSprite);
    frecSprite.setPosition(coordinate[0], coordinate[1]);

    // set initial attributes
	frecSpeed = 0.166667f; // speed
	frecRange = 2.0; // range
    frecDamage = 1.0; // damage
	frecPos = sf::Vector2f(coordinate[0], coordinate[1]);
}


ThrowingFrec::ThrowingFrec(const ThrowingFrec& right) {
	frecTexture.loadFromFile("C:\\VisualStudioWork\\TryAnimation\\ThrowingFrecSprite.png");
	frecPos = right.getfrecPosition();
	coordinate.push_back(frecPos.x);
	coordinate.push_back(frecPos.y);
	srcSprite = new srcArrayPtr[numPers];
	for (int i = 0; i < numPers; i++) {
		srcSprite[i] = new sf::IntRect[numFrame];
		for (int j = 0; j < numFrame; j++) {
			srcSprite[i][j] = right.getIntRects()[i][j];
		}
	}
	currentSprite = srcSprite[0][0];
	frecSprite.setTexture(frecTexture);
	frecSprite.setTextureRect(currentSprite);
	frecSprite.setPosition(coordinate[0], coordinate[1]);

	frecSpeed = right.getSpeed();
	frecRange = right.getRange();
	frecDamage = right.getDamage();
}

ThrowingFrec::~ThrowingFrec() {
	for (int i = 0; i < numPers; i++) { 
		delete[] srcSprite[i];
		srcSprite[i] = nullptr;
	}
	delete[] srcSprite;
	srcSprite = nullptr;
}

ThrowingFrec& ThrowingFrec::operator=(const ThrowingFrec& right) {
	if (this != &right) {
		for (int i = 0; i < numPers; i++) {
			delete[] srcSprite[i];
			srcSprite[i] = nullptr;
		}
		delete[] srcSprite;
		frecTexture.loadFromFile("C:\\VisualStudioWork\\TryAnimation\\ThrowingFrecSprite.png");
		frecPos = right.getfrecPosition();
		coordinate[0] = frecPos.x;
		coordinate[1] = frecPos.y;
		srcSprite = new srcArrayPtr[numPers];
		for (int i = 0; i < numPers; i++) {
			srcSprite[i] = new sf::IntRect[numFrame];
			for (int j = 0; j < numFrame; j++) {
				srcSprite[i][j] = right.getIntRects()[i][j];
			}
		}
		currentSprite = srcSprite[0][0];
		frecSprite.setTexture(frecTexture);
		frecSprite.setTextureRect(currentSprite);
		frecSprite.setPosition(coordinate[0], coordinate[1]);
		
		frecSpeed = right.getSpeed();
		frecRange = right.getRange();
		frecDamage = right.getDamage();
	}
	return *this;
}

// test heap functions
void ThrowingFrec::setPosition(std::vector<float> CV) {
	coordinate = CV;
	frecSprite.setPosition(coordinate[0], coordinate[1]);
}

void ThrowingFrec::Attack() {
	// (myClock.getElapsedClick() > attackSpeeck) or whatever, 
	// waiting for the "click" done by the controller class
	if (animationClock.getElapsedTime().asSeconds() > frecSpeed) {
		// use another layer of conditional to determine which direction is facing
		// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
		// where "sth" is using the logic bellow to loop through its sprites


		switch (direction) {
		case 'u':
			if (currentSprite == srcSprite[1][0]) {
				currentSprite = srcSprite[1][1];
				frecSprite.setTextureRect(currentSprite);
			}
			else if (currentSprite == srcSprite[1][1]) {
				currentSprite = srcSprite[1][2];
				frecSprite.setTextureRect(currentSprite);
			}
			else {
				currentSprite = srcSprite[1][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'd':
			if (currentSprite == srcSprite[0][0]) {
				currentSprite = srcSprite[0][1];
				frecSprite.setTextureRect(currentSprite);
			}
			else if (currentSprite == srcSprite[0][1]) {
				currentSprite = srcSprite[0][2];
				frecSprite.setTextureRect(currentSprite);
			}
			else {
				currentSprite = srcSprite[0][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'l':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(-1.0,1.0);
			}
			else if (currentSprite == srcSprite[2][1]) {
				currentSprite = srcSprite[2][2];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(-1.0, 1.0);
			}
			else {
				currentSprite = srcSprite[2][0];
				frecSprite.setTextureRect(currentSprite);
				flipSprite();
			} // end if else
			break;
		case 'r':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(1.0, 1.0);
			}
			else if (currentSprite == srcSprite[2][1]) {
				currentSprite = srcSprite[2][2];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(1.0, 1.0);
			}
			else {
				currentSprite = srcSprite[2][0];
				frecSprite.setTextureRect(currentSprite);
				flipBack();
			}
			break;
		} // end switch
		animationClock.restart();
	} // end switching figuresprite
}

void ThrowingFrec::StopAttack() {
	currentSprite = srcSprite[0][0];;
	frecSprite.setTextureRect(currentSprite);
}

void ThrowingFrec::setMode(char AorS) {
	mode = AorS;
}

char ThrowingFrec::getMode() const {
	return mode;
}

void ThrowingFrec::setDirection(char UDLR) {
	direction = UDLR;
}

char ThrowingFrec::getDirection() const {
	return direction;
}

void ThrowingFrec::froshDirection(sf::Vector2f froshPos) {
	float dx = frecPos.x - froshPos.x;
	float dy = frecPos.y - froshPos.y;
	if (dy > 0 && dy > dx && dx < -dy)
		setDirection('u');
	else if (dx < 0 && -dx > dy && dy >= dx)
		setDirection('r');
	else if (dy < 0 && dy < dx && -dy >= dx)
		setDirection('d');
	else
		setDirection('l');
}


sf::Sprite ThrowingFrec::getFrecSprite() const {
	return frecSprite;
}

void ThrowingFrec::flipSprite() {
	frecSprite.setScale(-1.0, 1.0);
	frecSprite.setPosition(coordinate[0]+128, coordinate[1]);
}
void ThrowingFrec::flipBack() {
	frecSprite.setScale(1.0, 1.0);
	frecSprite.setPosition(coordinate[0], coordinate[1]);
}

// new
sf::Vector2f ThrowingFrec::getfrecPosition() const {
	return frecPos;
}


// new
float ThrowingFrec::froshDistance(sf::Vector2f frosh) // returns distance between two points
{
	float x = (frecPos.x - frosh.x) * (frecPos.x - frosh.x);
	float y = (frecPos.y - frosh.y) * (frecPos.y - frosh.y);
	float xPlusY = x + y;
	return (float)(powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
}

// new
bool ThrowingFrec::froshCollides(sf::Vector2f frosh) // simple collision detection between two circles
{
	float dist = froshDistance(frosh); // gets distance between circles
	return dist < frecRange; // if dist < frec range we have a collision
}

// new
void ThrowingFrec::upgrade() {

}

float ThrowingFrec::getSpeed() const {
	return frecSpeed;
}

float ThrowingFrec::getRange() const {
	return frecRange;
}

float ThrowingFrec::getDamage() const {
	return frecDamage;
}

srcArrayPtr* ThrowingFrec::getIntRects() const {
	srcArrayPtr* newArr = new srcArrayPtr[numPers];
	for (int i = 0; i < numPers; i++) {
		newArr[i] = new sf::IntRect[numFrame];
		for (int j = 0; j < numFrame; j++) {
			newArr[i][j] = srcSprite[i][j];
		}
	}
	return newArr;
}


/*

DONE THROWING FREC
==================
Start Slamming Frec

*/

SlammingFrec::SlammingFrec(const std::vector<float> coordinateV) {
	/* These should all go into the three child classes
   // for each of the child classes:
   - set position from parameter -DONE
   - set texture of the file from its path -DONE
   - define the IntRect for each sprite from the spritesheet -DONE
   - define the IntRect for the default sprite (when not attacking) -DONE
   - define attack speed (to "tick")

   # Note: the sf::Clock thing should probably be gone
   # since we are matching the time to a "tick"
   */

   // these can be changed to adapt to whichever frec spritesheet we are using
   // and to their sizes, as well as the coordinate
	frecTexture.loadFromFile("C:\\VisualStudioWork\\TryAnimation\\SlammingFrecSprite.png");

	// set coordinate
	coordinate = coordinateV;

	// construct current sprite on the given position
	srcSprite = new srcArrayPtr[numPers];
	int x = 0;
	int y = 0;
	for (int i = 0; i < numPers; i++) {
		srcSprite[i] = new sf::IntRect[numFrame];
		for (int j = 0; j < numFrame; j++) {
			srcSprite[i][j] = sf::IntRect(x, y, 128, 128);
			x += 128;
		}
		y += 128;
		x = 0;
	}
	currentSprite = srcSprite[0][0];
	// direction = 'd';
	// mode = 'S';
	frecSprite.setTexture(frecTexture);
	frecSprite.setTextureRect(currentSprite);
	frecSprite.setPosition(coordinate[0], coordinate[1]);
	frecAttributes = new float[3];
	frecAttributes[0] = 0.25f; // speed
	frecAttributes[1] = 2.0; // range
	frecAttributes[2] = 1.0; // damage
}


void SlammingFrec::Attack() {
	// (myClock.getElapsedClick() > attackSpeeck) or whatever, 
	// waiting for the "click" done by the controller class
	if (animationClock.getElapsedTime().asSeconds() > frecAttributes[0]) {
		// use another layer of conditional to determine which direction is facing
		// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
		// where "sth" is using the logic bellow to loop through its sprites

		switch (direction) {
		case 'u':
			if (currentSprite == srcSprite[1][0]) {
				currentSprite = srcSprite[1][1];
				frecSprite.setTextureRect(currentSprite);
			}
			else {
				currentSprite = srcSprite[1][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'd':
			if (currentSprite == srcSprite[0][0]) {
				currentSprite = srcSprite[0][1];
				frecSprite.setTextureRect(currentSprite);
			}
			else {
				currentSprite = srcSprite[0][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'l':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(-1.0,1.0);
			}
			else { 
				currentSprite = srcSprite[2][0];
				frecSprite.setTextureRect(currentSprite);
				flipSprite();
			} // end if else
			break;
		case 'r':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(1.0, 1.0);
			}
			else {
				currentSprite = srcSprite[2][0];
				frecSprite.setTextureRect(currentSprite);
				flipBack();
			}
			break;
		} // end switch
		animationClock.restart();
	} // end switching figuresprite
}

void SlammingFrec::StopAttack() {
	currentSprite = srcSprite[0][0];
	frecSprite.setTextureRect(currentSprite);
}

void SlammingFrec::setMode(char AorS) {
	mode = AorS;
}

char SlammingFrec::getMode() {
	return mode;
}

void SlammingFrec::setDirection(char UDLR) {
	direction = UDLR;
}

char SlammingFrec::getDirection() {
	return direction;
}

void SlammingFrec::froshDirection(sf::Vector2f froshPos) {
	float dx = frecPos.x - froshPos.x;
	float dy = frecPos.y - froshPos.y;
	if (dy > 0 && dy > dx && dx < -dy)
		setDirection('u');
	else if (dx < 0 && -dx > dy && dy >= dx)
		setDirection('r');
	else if (dy < 0 && dy < dx && -dy >= dx)
		setDirection('d');
	else
		setDirection('l');
}


sf::Sprite SlammingFrec::getFrecSprite() {
	return frecSprite;
}
void SlammingFrec::flipSprite() {
	frecSprite.setScale(-1.0, 1.0);
	frecSprite.setPosition(coordinate[0] + 128, coordinate[1]);
}
void SlammingFrec::flipBack() {
	frecSprite.setScale(1.0, 1.0);
	frecSprite.setPosition(coordinate[0], coordinate[1]);
}

// new
sf::Vector2f SlammingFrec::getfrecPosition() {
	return frecPos;
}

// new
float SlammingFrec::getDamage() {
	return frecAttributes[2];
}

// new
float SlammingFrec::froshDistance(sf::Vector2f frosh) // returns distance between two points
{
	float x = (frecPos.x - frosh.x) * (frecPos.x - frosh.x);
	float y = (frecPos.y - frosh.y) * (frecPos.y - frosh.y);
	float xPlusY = x + y;
	return (float)(powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
}

// new
bool SlammingFrec::froshCollides(sf::Vector2f frosh) // simple collision detection between two circles
{
	float dist = froshDistance(frosh); // gets distance between circles
	return dist < frecAttributes[1]; // if dist < frec range we have a collision
}

// new
void SlammingFrec::upgrade() {

}

/*

DONE THROWING FREC
==================
Start Slamming Frec

*/

SwingingFrec::SwingingFrec(const std::vector<float> coordinateV) {
	/* These should all go into the three child classes
   // for each of the child classes:
   - set position from parameter -DONE
   - set texture of the file from its path -DONE
   - define the IntRect for each sprite from the spritesheet -DONE
   - define the IntRect for the default sprite (when not attacking) -DONE
   - define attack speed (to "tick")

   # Note: the sf::Clock thing should probably be gone
   # since we are matching the time to a "tick"
   */

   // these can be changed to adapt to whichever frec spritesheet we are using
   // and to their sizes, as well as the coordinate
	frecTexture.loadFromFile("C:\\VisualStudioWork\\TryAnimation\\SwingFrecSprite.png");

	// set coordinate
	coordinate = coordinateV;

	// construct current sprite on the given position
	srcSprite = new srcArrayPtr[numPers];
	int x = 0;
	int y = 0;
	for (int i = 0; i < numPers; i++) {
		srcSprite[i] = new sf::IntRect[numFrame];
		for (int j = 0; j < numFrame; j++) {
			srcSprite[i][j] = sf::IntRect(x, y, 128, 128);
			x += 128;
		}
		y += 128;
		x = 0;
	}
	currentSprite = srcSprite[0][0];
	// direction = 'd';
	// mode = 'S';
	frecSprite.setTexture(frecTexture);
	frecSprite.setTextureRect(currentSprite);
	frecSprite.setPosition(coordinate[0], coordinate[1]);
	frecAttributes = new float[3];
	frecAttributes[0] = 0.25f; // speed
	frecAttributes[1] = 2.0; // range
	frecAttributes[2] = 1.0; // damage
}


void SwingingFrec::Attack() {
	// (myClock.getElapsedClick() > attackSpeeck) or whatever, 
	// waiting for the "click" done by the controller class
	if (animationClock.getElapsedTime().asSeconds() > frecAttributes[0]) {
		// use another layer of conditional to determine which direction is facing
		// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
		// where "sth" is using the logic bellow to loop through its sprites

		switch (direction) {
		case 'u':
			if (currentSprite == srcSprite[1][0]) {
				currentSprite = srcSprite[1][1];
				frecSprite.setTextureRect(currentSprite);
			}
			else {
				currentSprite = srcSprite[1][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'd':
			if (currentSprite == srcSprite[0][0]) {
				currentSprite = srcSprite[0][1];
				frecSprite.setTextureRect(currentSprite);
			}
			else {
				currentSprite = srcSprite[0][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'l':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(-1.0,1.0);
			}
			else {
				currentSprite = srcSprite[2][0];
				frecSprite.setTextureRect(currentSprite);
				flipSprite();
			} // end if else
			break;
		case 'r':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(1.0, 1.0);
			}
			else {
				currentSprite = srcSprite[2][0];
				frecSprite.setTextureRect(currentSprite);
				flipBack();
			}
			break;
		} // end switch condition
		animationClock.restart();
	} // end switching figuresprite
}

void SwingingFrec::StopAttack() {
	currentSprite = srcSprite[0][0];
	frecSprite.setTextureRect(currentSprite);
}

void SwingingFrec::setMode(char AorS) {
	mode = AorS;
}

char SwingingFrec::getMode() {
	return mode;
}

void SwingingFrec::setDirection(char UDLR) {
	direction = UDLR;
}

char SwingingFrec::getDirection() {
	return direction;
}

void SwingingFrec::froshDirection(sf::Vector2f froshPos) {
	float dx = frecPos.x - froshPos.x;
	float dy = frecPos.y - froshPos.y;
	if (dy > 0 && dy > dx && dx < -dy)
		setDirection('u');
	else if (dx < 0 && -dx > dy && dy >= dx)
		setDirection('r');
	else if (dy < 0 && dy < dx && -dy >= dx)
		setDirection('d');
	else
		setDirection('l');
}


sf::Sprite SwingingFrec::getFrecSprite() {
	return frecSprite;
}

void SwingingFrec::flipSprite() {
	frecSprite.setScale(-1.0, 1.0);
	frecSprite.setPosition(coordinate[0] + 128, coordinate[1]);
}

void SwingingFrec::flipBack() {
	frecSprite.setScale(1.0, 1.0);
	frecSprite.setPosition(coordinate[0], coordinate[1]);
}

// new
sf::Vector2f SwingingFrec::getfrecPosition() {
	return frecPos;
}

// new
float SwingingFrec::getDamage() {
	return frecAttributes[2];
}

// new
float SwingingFrec::froshDistance(sf::Vector2f frosh) // returns distance between two points
{
	float x = (frecPos.x - frosh.x) * (frecPos.x - frosh.x);
	float y = (frecPos.y - frosh.y) * (frecPos.y - frosh.y);
	float xPlusY = x + y;
	return (float)(powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
}

// new
bool SwingingFrec::froshCollides(sf::Vector2f frosh) // simple collision detection between two circles
{
	float dist = froshDistance(frosh); // gets distance between circles
	return dist < frecAttributes[1]; // if dist < frec range we have a collision
}

// new
void SwingingFrec::upgrade() {

}







// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
