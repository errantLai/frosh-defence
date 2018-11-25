#include "FrecAndFroshController.h"

FrecAndFroshController::FrecAndFroshController(int notUsed) {
	unused = notUsed; //must have private members to make an object
}
FrecAndFroshController::~FrecAndFroshController() {
	allThrowFrecs.erase(allThrowFrecs.begin(), allThrowFrecs.end());
}

/*___________________________________________OBJECT BEING THROWN_________________________________________________*/

void FrecAndFroshController::addThrowObjectToList(int index,
		sf::Vector2f frecPosition, shared_ptr<Frosh> froshPtr) {
	allThrowObjects.push_back(
			make_unique<throwProjectile>(index, frecPosition, froshPtr));
}
void FrecAndFroshController::deleteThrowObjectAtIndex(int index) {
	allThrowObjects[index].reset();
	allThrowObjects.erase(allThrowObjects.begin() + index,
			allThrowObjects.begin() + index + 1);
	//delete image? I dont think you'll need to explicitly do this
	//delete &allThrowObjects[index];
}
void FrecAndFroshController::drawAllThrowObjectsOnGrid(
		sf::RenderWindow &theWindow) {	//draws the frec onto the grid
	for (auto& projectile : allThrowObjects) {
		projectile->drawProjectile(theWindow);
	}
}
/*__________________________________________OBJECT BEING THROWN_________________________________________________*/

/*___________________________________________Attack Logic_________________________________________________*/

//if missile to frosh collision occurs, delete throwObject, else, move towards frosh
void FrecAndFroshController::moveAllThrowObjectTowardsFroshAndDelete() { //this parameter will be replaced by allFrosh[j]->getPosition() in each if statement
	for (int i = 0, projectileSize = allThrowObjects.size(); i < projectileSize;
			i++) { //for each throw object
		//if there's a collision, delete object and deal damage
		//cout<< "Projectile Positions:" << allThrowObjects[i]->getThrowProjectilePosition().x << " and y " << allThrowObjects[i]->getThrowProjectilePosition().y << endl;

		if (allThrowObjects[i]->projectileFroshCollision(
				allThrowObjects[i]->getFroshTarget()->getCenterPosition())) {
			//deal damage to frosh
			allThrowObjects[i]->getFroshTarget()->reduceHealth(
					allThrowObjects[i]->getFroshTarget()->getHealth());
			//getTams as well similar logic ^
			cout << "DAMAGE DEALT, projectile deleted" << endl;

			//delete throw object
			deleteThrowObjectAtIndex(i);
		} else { //if the projectile assigned to a frosh hasnt hit yet, move towards frosh
			allThrowObjects[i]->moveObjectTowardsFrosh(
					allThrowObjects[i]->getFroshTarget()->getCenterPosition());
		}
	}
}

bool FrecAndFroshController::collisionDetected(shared_ptr<Frec>,
		shared_ptr<Frosh>) {
	return false;
}

//ascocitate each frec with a frosh within range, each with a vector of pointers (eg. frec index 0 will fire at frosh index 0)
void FrecAndFroshController::updateFrecFroshRange() {
	//clear contents of allThrowFrecsInRangeOfFrosh
	if (allThrowFrecsInRangeOfFrosh.size() > 0)
		allThrowFrecsInRangeOfFrosh.erase(allThrowFrecsInRangeOfFrosh.begin(),
				allThrowFrecsInRangeOfFrosh.end());
	//clear contents of
	if (allFroshInRangeOfFrecs.size() > 0)
		allFroshInRangeOfFrecs.erase(allFroshInRangeOfFrecs.begin(),
				allFroshInRangeOfFrecs.end());

	for (int i = 0, allFrecSize = allThrowFrecs.size(); i < allFrecSize; i++) { //for each frec object
		for (int j = 0, allFroshSize = allFrosh.size(); j < allFroshSize; j++) { //for each frosh object
			if (collisionDetected(allThrowFrecs[i], allFrosh[j])) {
				//cout << "Frec Frosh Collision" << endl;
				allFroshInRangeOfFrecs.push_back(allFrosh[j]); //the indices will line up for each frec sticking to one frosh target
				allThrowFrecsInRangeOfFrosh.push_back(allThrowFrecs[i]);
			}
		}
	}
}

//below creates two unique pointer vectors assigning each throw frec with a frosh target assigned to it
//cooldown, a generation of projectiles
//if frosh is in range of a frec, generate a projectile as long as the frec is not on cooldown
//assign that projectile to a frosh object

void FrecAndFroshController::process() { //essentially do every attack related function in a small time tick within process
	//for each frec, decrease its cooldown by one tick, when at 0 it can fire
	for (int i = 0, frecSize = allThrowFrecs.size(); i < frecSize; i++) {
		if (allThrowFrecs[i]->getCooldown() > 1)
			allThrowFrecs[i]->decreaseCooldown();
	}
	//ascocitate each frec with a frosh within range, each with a vector of pointers (eg. frec index 0 will fire at frosh index 0)
	updateFrecFroshRange();
	//if the frec is not on cooldown, create a throwProjectile object that is assigned to a frosh object
	for (int i = 0, availableFrosh = allThrowFrecsInRangeOfFrosh.size();
			i < availableFrosh; i++) { //frecs and frosh will have same index i
		if (allThrowFrecsInRangeOfFrosh[i]->getCooldown() == 0) { //if the frec is not on cooldown fire a new projectile, else do nothing
			cout << "Firing Projectile" << endl;
			allThrowFrecsInRangeOfFrosh[i]->resetCooldown();
			addThrowObjectToList(allThrowObjects.size() - 1,
					allThrowFrecsInRangeOfFrosh[i]->getPosition(),
					allFroshInRangeOfFrecs[i]); //append a throw object to the end of the vector
			//allThrowObjects[allThrowObjects.size() - 1]->setFroshTarget(allFroshInRangeOfFrecs[i]); //assign a frosh target
		}
	}
	//move each projectile towards its assigned frosh target, delete and deal damage if hit
	moveAllThrowObjectTowardsFroshAndDelete();
}

void FrecAndFroshController::render(sf::RenderWindow &_window) {
	drawAllThrowObjectsOnGrid(_window);
}

