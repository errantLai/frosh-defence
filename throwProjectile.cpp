#include "throwProjectile.h"
#include <math.h>

//creates a throwProjectile object
throwProjectile::throwProjectile(int ind, int _damage,
		sf::Vector2f frecPosition, weak_ptr<Frosh> froshToFireAt) :
		index(ind), damage(_damage), projectilePosition(frecPosition), froshTarget(
				froshToFireAt) {
	speed = 8.0f;
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
	cout << "Projectile Deleted" << endl;
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

//draws the projectile to the window
void throwProjectile::moveObjectTowardsFrosh(sf::Vector2f froshPos) {
	sf::Vector2f movePos = normalize(froshPos - projectilePosition);
	projectileShape.move(movePos * getSpeed()); //using the x,y positions, moves at a percentage towards the frosh object
	projectilePosition = projectilePosition + movePos * getSpeed();
	projectileCenter = projectileCenter + movePos * getSpeed();
}

// returns distance between two points
float throwProjectile::DistanceFromFrosh(sf::Vector2f frosh) {
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

//Accessors:
weak_ptr<Frosh> throwProjectile::getFroshTarget() {
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
