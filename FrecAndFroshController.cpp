#include "FrecAndFroshController.h"
#include <math.h>
#include <memory>

using std::weak_ptr;
using std::shared_ptr;

FrecAndFroshController::FrecAndFroshController(sf::RenderWindow* _window,
		GameState* _gameState, FroshController* _froshController,
		vector<Frec*>* _allFrecs, vector<shared_ptr<Frosh>>* _allFrosh) :
		window(_window), gameState(_gameState), froshController(
				_froshController), allThrowFrecs(_allFrecs), allFrosh(_allFrosh) {
}
FrecAndFroshController::~FrecAndFroshController() {
}

/*___________________________________________OBJECT BEING THROWN_________________________________________________*/

void FrecAndFroshController::addThrowObjectToList(int index, int damage,
		sf::Vector2f frecPosition, weak_ptr<Frosh> froshPtr) {
	allThrowObjects.push_back(
			new throwProjectile(index, damage, frecPosition, froshPtr));
}

void FrecAndFroshController::deleteProjectile(throwProjectile* projectile) {
	// This is an acceptable computational cost due to rarity of action.
	// O(N) for each deletion
	for (int i = 0, size = allThrowObjects.size(); i < size; i++) {
		if ((allThrowObjects)[i] == projectile) {
			projectile = nullptr;
			allThrowObjects.erase(allThrowObjects.begin() + i);
			break;
		}
	}
}

void FrecAndFroshController::deleteThrowObjectAtIndex(int index) {
	delete allThrowObjects[index];
	allThrowObjects[index] = nullptr;
	allThrowObjects.erase(allThrowObjects.begin() + index);
	//delete image? I dont think you'll need to explicitly do this
	//delete &allThrowObjects[index];
}
void FrecAndFroshController::drawAllThrowObjectsOnGrid(
		sf::RenderWindow* _window) {	//draws the frec onto the grid
	for (auto& projectile : allThrowObjects) {
		projectile->drawProjectile(_window);
	}
}
/*__________________________________________OBJECT BEING THROWN_________________________________________________*/

/*___________________________________________Attack Logic_________________________________________________*/

//if missile to frosh collision occurs, delete throwObject, else, move towards frosh
void FrecAndFroshController::updateProjectiles() { //this parameter will be replaced by allFrosh[j]->getPosition() in each if statement
	int i = 0;
	while(i<allThrowObjects.size()){
	//for (int i = 0, projectileSize = allThrowObjects.size(); i < projectileSize;
	//		i++) { //for each throw object
		//if there's a collision, delete object and deal damage
		//cout<< "Projectile Positions:" << allThrowObjects[i]->getThrowProjectilePosition().x << " and y " << allThrowObjects[i]->getThrowProjectilePosition().y << endl;

		if (auto frosh = allThrowObjects[i]->getFroshTarget().lock()) {
			if (allThrowObjects[i]->projectileFroshCollision(
					frosh->getCenterPosition())) {
				//deal damage to frosh
				froshController->dealDamage(frosh,
						allThrowObjects[i]->getDamage());
				//delete throw object
				deleteProjectile(allThrowObjects[i]);
				i--;
			} else { //if the projectile assigned to a frosh hasnt hit yet, move towards frosh
				allThrowObjects[i]->moveObjectTowardsFrosh(
						frosh->getCenterPosition());
			}
		} else {
			deleteProjectile(allThrowObjects[i]);
			i--;
		}
		i++;
	}
}

//FREC AND FROSH COLLISION
// Uses Pythagorean to detect a point collision with a circle
bool FrecAndFroshController::collisionDetected(Frec* frec,
		weak_ptr<Frosh> _frosh) {
	if (auto frosh = _frosh.lock()) {
		float distX = frosh->getCenterPosition().x
				- frec->getCenterPosition().x;
		float distY = frosh->getCenterPosition().y
				- frec->getCenterPosition().y;
		float distance = sqrt((distX * distX) + (distY * distY));
//	cout << "DistX: " << distX << " DistY: " << distY << endl;
//	cout << "Distance detected: " << distance << " for a range: "
//			<< frec->getRange() << endl;
		if (distance <= frec->getRange())
			return true;
	}
	return false;
}

//ascocitate each frec with a frosh within range, each with a vector of pointers (eg. frec index 0 will fire at frosh index 0)
void FrecAndFroshController::updateFrecFroshRange() {
	//clear contents of allThrowFrecsInRangeOfFrosh
	if (allThrowFrecsInRangeOfFrosh.size() > 0)
		allThrowFrecsInRangeOfFrosh.erase(allThrowFrecsInRangeOfFrosh.begin(),
				allThrowFrecsInRangeOfFrosh.end());
	allFroshInRangeOfFrecs.erase(allFroshInRangeOfFrecs.begin(),
			allFroshInRangeOfFrecs.end());

	for (int i = 0, allFrecSize = allThrowFrecs->size(); i < allFrecSize; i++) { //for each frec object
		for (int j = 0, allFroshSize = allFrosh->size(); j < allFroshSize;
				j++) { //for each frosh object
			if (collisionDetected((*allThrowFrecs)[i], (*allFrosh)[j])) {
				// cout << "Frec Frosh Collision" << endl;		
				weak_ptr<Frosh> frosh = (*allFrosh)[j];
				allFroshInRangeOfFrecs.push_back(frosh);
				allThrowFrecsInRangeOfFrosh.push_back((*allThrowFrecs)[i]);
			}
		}
	}
}

//below creates two unique pointer vectors assigning each throw frec with a frosh target assigned to it
//cooldown, a generation of projectiles
//if frosh is in range of a frec, generate a projectile as long as the frec is not on cooldown
//assign that projectile to a frosh object

void FrecAndFroshController::update() { //essentially do every attack related function in a small time tick within process
	//for each frec, decrease its cooldown by one tick, when at 0 it can fire
	for (int i = 0, frecSize = allThrowFrecs->size(); i < frecSize; i++) {
		if ((*allThrowFrecs)[i]->getCooldown() >= 1) {
			(*allThrowFrecs)[i]->decreaseCooldown();
		}
	}
	//ascocitate each frec with a frosh within range, each with a vector of pointers (eg. frec index 0 will fire at frosh index 0)
	updateFrecFroshRange();
	//if the frec is not on cooldown, create a throwProjectile object that is assigned to a frosh object
	for (int i = 0, availableFrosh = allThrowFrecsInRangeOfFrosh.size();
			i < availableFrosh; i++) { //frecs and frosh will have same index i
		if (allThrowFrecsInRangeOfFrosh[i]->getCooldown() <= 0) { //if the frec is not on cooldown fire a new projectile, else do nothing
			//cout << "Firing Projectile" << endl;
			allThrowFrecsInRangeOfFrosh[i]->resetCooldown();
			auto frosh = allFroshInRangeOfFrecs[i].lock();
			(allThrowFrecsInRangeOfFrosh)[i]->froshDirection(frosh->getPosition());
			(allThrowFrecsInRangeOfFrosh)[i]->Attack(); //sets directioon
			addThrowObjectToList(allThrowObjects.size() - 1,
					allThrowFrecsInRangeOfFrosh[i]->getDamage(),
					allThrowFrecsInRangeOfFrosh[i]->getPosition(),
					allFroshInRangeOfFrecs[i]); //append a throw object to the end of the vector
			//allThrowObjects[allThrowObjects.size() - 1]->setFroshTarget(allFroshInRangeOfFrecs[i]); //assign a frosh target
		}
	}
	//move each projectile towards its assigned frosh target, delete and deal damage if hit
	updateProjectiles();
}

void FrecAndFroshController::render() {
	drawAllThrowObjectsOnGrid(window);
}

