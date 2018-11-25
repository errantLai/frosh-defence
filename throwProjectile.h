#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Frec.h"
#include "Frosh.h"
#include <vector>
#include <memory>

using std::shared_ptr;
using std::unique_ptr;

class throwProjectile { //must extend frec class to access its position easiest/ most efficently 
public:
	throwProjectile(int ind, sf::Vector2f frecPosition,
			shared_ptr<Frosh> froshToFireAt);
	~throwProjectile();
	void drawProjectile(sf::RenderWindow &theWindow);
	void moveObjectTowardsFrosh(sf::Vector2f frosh); //using frosh position, heatseeks towards the frosh until collision occurs
	float DistanceFromFrosh(sf::Vector2f frosh); // returns distance between two points
	bool projectileFroshCollision(sf::Vector2f frosh); // collision detection between two objects, using the distance function
	void dealDamage(); //deals the damage associated with the projectile
	sf::Vector2f normalize(sf::Vector2f v);

	//Accessors:
	string getThrowProjImage();
	sf::Vector2f getThrowProjectilePosition();
	float getSpeed();
	shared_ptr<Frosh> getFroshTarget();
	int getDamage();
	sf::Vector2f getProjectileCenter();

private:
	sf::Texture projectileTexture;
	sf::RectangleShape projectileShape;
	sf::Vector2f projectilePosition;
	sf::Vector2f projectileCenter;
	float speed;
	int index;
	int damage;
	string throwProjImage = "assets/jacket.jpg";
	shared_ptr<Frosh> froshTarget;
};
