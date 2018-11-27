#include "Frec.h"
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
typedef sf::IntRect* srcArrayPtr;

Frec::Frec(const sf::Vector2f position, sf::Texture* _texture, FrecType _type,
		int damage, int range, int cooldown) :
		Clickable(position, sf::Vector2f(120, 120)), coordinate(position), frecPos(position), texture(
				_texture), type(_type), frecDamage(damage), frecRange(range), baseCooldown(
				cooldown) {
	// these can be changed to adapt to whichever frec spritesheet we are using
	// and to their sizes, as well as the coordinate
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
	frecSprite = sf::Sprite(*texture, currentSprite);
	frecSprite.setPosition(frecPos.x, frecPos.y);

	// set initial attributes
	mode = 'a';
	direction = 'r';
	currentCooldown = 0;
	wasClicked = false;
	upgradeCost = 25;
}

Frec::~Frec() {
	for (int i = 0; i < numPers; i++) {
		delete[] srcSprite[i];
		srcSprite[i] = nullptr;
	}
	delete[] srcSprite;
	srcSprite = nullptr;
}

FrecType Frec::getFrecType() const {
	return this->type;
}

// test heap functions
void Frec::setPosition(sf::Vector2f newPosition) {
	frecSprite.setPosition(newPosition);
}

void Frec::setMode(char AorS) {
	mode = AorS;
}

char Frec::getDirection() const {
	return direction;
}

char Frec::getMode() const {
	return mode;
}

void Frec::setDirection(char UDLR) {
	direction = UDLR;
}

void Frec::decreaseCooldown() {
	this->currentCooldown--;
}
void Frec::resetCooldown() {
	this->currentCooldown = this->baseCooldown;
}

void Frec::update() {
}
void Frec::render(sf::RenderWindow& _window) {
	_window.draw(this->frecSprite);
}

void Frec::onClick() {
	this->wasClicked = true;
}

sf::Vector2f Frec::getPosition() const {
	return frecPos;
}

sf::Vector2f Frec::getCenterPosition() const {
	sf::Vector2f center = this->frecSprite.getPosition();
	center.x += 120 / 2;
	center.y += 120 / 2;
	return center;
}

float Frec::getDamage() const {
	return this->frecDamage;
}
float Frec::getRange() const {
	return this->frecRange;
}

int Frec::getCooldown() {
	return this->currentCooldown;
}

int Frec::getUpgradeCost() {
	return this->upgradeCost;
}

void Frec::froshDirection(sf::Vector2f froshPos) {
	float dx = coordinate.x - froshPos.x;
	float dy = coordinate.y - froshPos.y;
	if ((dy > 0 && (dx >= 0 && dx < dy)) || (dy > 0 && (dx < 0 && -dx <= dy))) {
		if (direction != 'u') {
			setDirection('u');
			//cout << "direction up" << endl;
		}
	}
	else if ((dy > 0 && (dx <= 0 && dx < dy)) || (dy > 0 && (dx < 0 && -dx <= dy))) {
		if (direction != 'r') {
			setDirection('r');
			//cout << "direction right" << endl;
		}
	}
	else if ((dy < 0 && (dx >= 0 && dx <= -dy)) || (dy < 0 && (dx < 0 && dx > dy))) {
		if (direction != 'd') {
			setDirection('d');
			//cout << "direction down" << endl;
		}
	}
	else if ((dx > 0 && (dy >= 0 && dx >= dy)) || (dx > 0 && (dy < 0 && dx > -dy))) {
		if (direction != 'l') {
			setDirection('l');
			//cout << "direction left" << endl;
		}
	}
	else {
		setDirection('d');
	}
}

sf::Sprite Frec::getFrecSprite() const {
	return frecSprite;
}

sf::Vector2f Frec::getOriginalFrecPosition()
{
	return coordinate;
}

void resetSpriteRange() {

}

void Frec::flipSprite() {
	frecSprite.setScale(-1.0, 1.0);
	frecSprite.setPosition(frecPos.x +128, frecPos.y);
}
void Frec::flipBack() {
	frecSprite.setScale(1.0, 1.0);
	frecSprite.setPosition(frecPos.x, frecPos.y);
}

float Frec::froshDistance(sf::Vector2f frosh) // returns distance between two points
		{
	float x = (coordinate.x - frosh.x) * (coordinate.x - frosh.x);
	float y = (coordinate.y - frosh.y) * (coordinate.y - frosh.y);
	float xPlusY = x + y;
	return (float) (powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
}

bool Frec::froshCollides(sf::Vector2f frosh) // simple collision detection between two circles
{
	float dist = froshDistance(frosh); // gets distance between circles
	return dist < frecRange; // if dist < frec range we have a collision
}

void Frec::Attack() {
	// (myClock.getElapsedClick() > attackSpeeck) or whatever,
	// waiting for the "click" done by the controller class
	// use another layer of conditional to determine which direction is facing
	// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
	// where "sth" is using the logic bellow to loop through its sprites
	//spriteCooldownSwitch starts at 15, each tick represents one cycle
	switch (direction) {
	case 'u':
		if (spriteFrame){
			frecSprite.setTextureRect(srcSprite[1][0]);
			spriteFrame = false;
		}
		else {
			frecSprite.setTextureRect(srcSprite[1][1]);
			spriteFrame = true;
		}
		break;
	case 'd':
		if (spriteFrame) {
			frecSprite.setTextureRect(srcSprite[0][0]);
			spriteFrame = false;
		}
		else{
			frecSprite.setTextureRect(srcSprite[0][1]);
			spriteFrame = true;
		}
		break;
	case 'l':
		if (spriteFrame) {
			frecSprite.setTextureRect(srcSprite[2][0]);
			spriteFrame = false;
			flipSprite();
		}
		else {
			frecSprite.setTextureRect(srcSprite[2][1]);
			spriteFrame = true;
			flipSprite();
		}
		break;
	case 'r':
		if (spriteFrame) {
			frecSprite.setTextureRect(srcSprite[2][0]);
			spriteFrame = false;
			flipBack();
		}
		else{
			frecSprite.setTextureRect(srcSprite[2][1]);
			spriteFrame = true;
			flipBack();
		}
		break;
	} // end switch
}

//void Frec::Attack() {
//	// (myClock.getElapsedClick() > attackSpeeck) or whatever,
//	// waiting for the "click" done by the controller class
//	// use another layer of conditional to determine which direction is facing
//	// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
//	// where "sth" is using the logic bellow to loop through its sprites
//	//spriteCooldownSwitch starts at 15, each tick represents one cycle
//	spriteCooldownSwitch= spriteCooldownSwitch-3;
//	if (spriteCooldownSwitch < 0)
//		spriteCooldownSwitch = 30;
//	switch (direction) {
//	case 'u':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15)
//			frecSprite.setTextureRect(srcSprite[1][0]);
//		else if (spriteCooldownSwitch < 15)
//			frecSprite.setTextureRect(srcSprite[1][1]);
//		break;
//	case 'd':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15)
//			frecSprite.setTextureRect(srcSprite[0][0]);
//		else if (spriteCooldownSwitch < 15)
//			frecSprite.setTextureRect(srcSprite[0][1]);
//		break;
//	case 'l':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15) {
//			frecSprite.setTextureRect(srcSprite[2][0]);
//			//if (spriteCooldownSwitch == 15)
//			flipSprite();
//		}
//		else if (spriteCooldownSwitch < 15) {
//			frecSprite.setTextureRect(srcSprite[2][1]);
//			//if ()
//			flipSprite();
//		}
//		break;
//	case 'r':
//		if (spriteCooldownSwitch <= 30 && spriteCooldownSwitch > 15) {
//			frecSprite.setTextureRect(srcSprite[2][0]);
//			flipBack();
//		}	
//		else if (spriteCooldownSwitch < 15) {
//			frecSprite.setTextureRect(srcSprite[2][1]);
//			flipBack();
//		}
//			
//		break;
//	} // end switch
//}

void Frec::StopAttack() {
	currentSprite = srcSprite[0][0];
	frecSprite.setTextureRect(currentSprite);
}

void Frec::upgrade() {
	this->frecDamage *= 1.2;
	this->frecRange *= 1.2;
	this->currentCooldown *= 1.2;
	this->upgradeCost*= 1.8;
}

srcArrayPtr* Frec::getIntRects() const {
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
	frecTexture.loadFromFile(
			"C:\\VisualStudioWork\\TryAnimation\\SlammingFrecSprite.png");

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
	frecAttributes[0] = 10.25f; // speed
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
			} else {
				currentSprite = srcSprite[1][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'd':
			if (currentSprite == srcSprite[0][0]) {
				currentSprite = srcSprite[0][1];
				frecSprite.setTextureRect(currentSprite);
			} else {
				currentSprite = srcSprite[0][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'l':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(-1.0,1.0);
			} else {
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
			} else {
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

char SlammingFrec::getMode() const {
	return mode;
}

void SlammingFrec::setDirection(char UDLR) {
	direction = UDLR;
}

char SlammingFrec::getDirection() const {
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

sf::Sprite SlammingFrec::getFrecSprite() const {
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
sf::Vector2f SlammingFrec::getfrecPosition() const {
	return frecPos;
}

// new
float SlammingFrec::getDamage() const {
	return frecAttributes[2];
}

// new
float SlammingFrec::froshDistance(sf::Vector2f frosh) // returns distance between two points
		{
	float x = (frecPos.x - frosh.x) * (frecPos.x - frosh.x);
	float y = (frecPos.y - frosh.y) * (frecPos.y - frosh.y);
	float xPlusY = x + y;
	return (float) (powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
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
	frecTexture.loadFromFile(
			"C:\\VisualStudioWork\\TryAnimation\\SwingFrecSprite.png");

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
	//if (animationClock.getElapsedTime().asSeconds() > frecAttributes[0]) {
		// use another layer of conditional to determine which direction is facing
		// i.e. switch (direction) {case 'l': //sth; case 'r': //sth; ...}
		// where "sth" is using the logic bellow to loop through its sprites

		switch (direction) {
		case 'u':
			if (currentSprite == srcSprite[1][0]) {
				currentSprite = srcSprite[1][1];
				frecSprite.setTextureRect(currentSprite);
			} else {
				currentSprite = srcSprite[1][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'd':
			if (currentSprite == srcSprite[0][0]) {
				currentSprite = srcSprite[0][1];
				frecSprite.setTextureRect(currentSprite);
			} else {
				currentSprite = srcSprite[0][0];
				frecSprite.setTextureRect(currentSprite);
			} // end if else
			break;
		case 'l':
			if (currentSprite == srcSprite[2][0]) {
				currentSprite = srcSprite[2][1];
				frecSprite.setTextureRect(currentSprite);
				//frecSprite.setScale(-1.0,1.0);
			} else {
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
			} else {
				currentSprite = srcSprite[2][0];
				frecSprite.setTextureRect(currentSprite);
				flipBack();
			}
			break;
		} // end switch condition
		//animationClock.restart();
	//} // end switching figuresprite
}

void SwingingFrec::StopAttack() {
	currentSprite = srcSprite[0][0];
	frecSprite.setTextureRect(currentSprite);
	mode = 'S';
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
float SwingingFrec::getDamage() const {
	return frecAttributes[2];
}

// new
float SwingingFrec::froshDistance(sf::Vector2f frosh) // returns distance between two points
		{
	float x = (frecPos.x - frosh.x) * (frecPos.x - frosh.x);
	float y = (frecPos.y - frosh.y) * (frecPos.y - frosh.y);
	float xPlusY = x + y;
	return (float) (powf(xPlusY, 0.5)); //returns hypotenuse , ie. distance between points
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
