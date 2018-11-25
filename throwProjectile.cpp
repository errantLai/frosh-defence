#include "throwProjectile.h"
#include <math.h>

//creates a throwProjectile object
throwProjectile::throwProjectile(int ind, sf::Vector2f frecPosition,
		Frosh* froshToFireAt) :
		index(ind), projectilePosition(frecPosition), froshTarget(froshToFireAt) {
	damage = 10;
	speed = 4.0f;
	projectileShape = sf::RectangleShape(sf::Vector2f(30.0f, 30.0f));
	projectileShape.setSize(sf::Vector2f(30.0f, 30.0f)); //size of projectile

	projectileShape.setPosition(frecPosition);
	if (!projectileTexture.loadFromFile(throwProjImage)) {
		std::cerr << "Error finding image\n";
	} else {
		projectileTexture.loadFromFile(throwProjImage);
		projectileShape.setTexture(&projectileTexture);
	}
	projectileCenter = sf::Vector2f(frecPosition.x + 30.0f / 2,
			frecPosition.y + 30.0f / 2);
}
throwProjectile::~throwProjectile() {
}

void throwProjectile::drawProjectile(sf::RenderWindow* _window) {
	_window->draw(projectileShape);
}

//gets a vector of length 1, to be multipled by a speed
sf::Vector2f throwProjectile::normalize(sf::Vector2f v) {
	float len = float(sqrt((v.x * v.x) + (v.y * v.y)));
	if (len != 0) {
		v.x = v.x / len;
		v.y = v.y / len;
	}
	return v;
}

void throwProjectile::moveObjectTowardsFrosh(sf::Vector2f frosh) //draws the projectile to the window
		{
	sf::Vector2f movePos = normalize(frosh - projectilePosition);
	projectileShape.move(movePos * getSpeed()); //using the x,y positions, moves at a percentage towards the frosh object
	projectilePosition = projectilePosition + movePos * getSpeed();
	projectileCenter = projectileCenter + movePos * getSpeed();
}
float throwProjectile::DistanceFromFrosh(sf::Vector2f frosh) // returns distance between two points
		{
	//use abs to prevent a negative distance
	float x = abs(
			(frosh.x - projectilePosition.x)
					* (frosh.x - projectilePosition.x));
	float y = abs(
			(frosh.y - projectilePosition.y)
					* (frosh.y - projectilePosition.y));
	return (int) (powf(x + y, 0.5)); //square root ( x^2+y^2 )
}
bool throwProjectile::projectileFroshCollision(sf::Vector2f frosh) // simple collision detection between two circles
		{
	return DistanceFromFrosh(frosh) < 3;
	//return DistanceFromFrosh(frosh) < projectileShape.getSize().x || DistanceFromFrosh(frosh) < projectileShape.getSize().y;// if dist < frec range we have a collision
} //will always do for < 10

void throwProjectile::dealDamage() {
	int dmg = getDamage();
	std::cout << "Damage Dealt" << std::endl;
	//find out how to deal damage, talk to the frosh lads about a controller implementation
} //deals the damage associated with the projectile

//Accessors:

Frosh* throwProjectile::getFroshTarget() {
	return froshTarget;
}
string throwProjectile::getThrowProjImage() {
	return throwProjImage;
}
sf::Vector2f throwProjectile::getThrowProjectilePosition() {
	return projectilePosition;
}
float throwProjectile::getSpeed() {
	return speed;
}
int throwProjectile::getDamage() {
	return damage;
}
sf::Vector2f throwProjectile::getProjectileCenter() {
	return projectileCenter;
}
