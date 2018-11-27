#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Frec.h"
#include "Frosh.h"
#include <vector>
#include <memory>
#include <string>

using std::string;
using std::weak_ptr;

class throwProjectile {
public:
	throwProjectile(int ind, int damage, sf::Vector2f frecPosition,
			weak_ptr<Frosh> froshToFireAt);
	~throwProjectile();
	void drawProjectile(sf::RenderWindow* _window);
	//using frosh position, heatseeks towards the frosh until collision occurs
	void moveObjectTowardsFrosh(sf::Vector2f froshPos);
	float DistanceFromFrosh(sf::Vector2f frosh); // returns distance between two points
	bool projectileFroshCollision(sf::Vector2f frosh); // collision detection between two objects, using the distance function
	void dealDamage(); //deals the damage associated with the projectile
	sf::Vector2f normalize(sf::Vector2f v);

	//Accessors:
	string getThrowProjImage();
	sf::Vector2f getThrowProjectilePosition();
	float getSpeed();
	weak_ptr<Frosh> getFroshTarget();
	int getDamage();
	sf::Vector2f getProjectileCenter();

private:
	int index;
	int damage;
	sf::Texture projectileTexture;
	sf::RectangleShape projectileShape;
	sf::Vector2f projectilePosition;
	sf::Vector2f projectileCenter;
	float speed;
	string throwProjImage = "assets/jacket.png";
	weak_ptr<Frosh> froshTarget;
};
