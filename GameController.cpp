#include <SFML/Graphics.hpp>

#include <chrono>
#include <ctime>
#include <cmath>
#include <string>		// String object
#include <vector>		// Vector object
#include "GameController.h"
#include "GameMenuController.h"
#include <iostream>

sf::RectangleShape grassTile;
sf::RectangleShape groundTile;
sf::CircleShape hoverOutline;
sf::RectangleShape* _tamsCounter;
sf::RectangleShape* _livesCounter;
sf::RectangleShape* _wavesCounter;

sf::Text text;
std::vector<Point> path =
		{ Point(15, 0), Point(15, 4), Point(20, 4), Point(20, 1), Point(24, 1),
				Point(24, 8), Point(10, 8), Point(10, 4), Point(5, 4), Point(5,
						14), Point(10, 14), Point(10, 12), Point(14, 12), Point(
						14, 15), Point(20, 15), Point(20, 11), Point(24, 11),
				Point(24, 18) };
sf::RenderWindow* window;
bool debug;

GameBoard::GameBoard() {
	initBoard();
}
void GameBoard::initBoard() {
	sf::Texture* _menuTexture = new sf::Texture;
		if(!_menuTexture->loadFromFile("assets/menuInfo.png")){
			std::cerr << "The texture does not exist" << std::endl;
		}
	_tamsCounter = new sf::RectangleShape(sf::Vector2f(398,156));
		_tamsCounter->setPosition(36,0);
		_tamsCounter->setTexture(_menuTexture);
		_tamsCounter->setTextureRect(sf::IntRect(0,0,398,156));
		//drawVec.push_back(_tamsCounter);
	_livesCounter = new sf::RectangleShape(sf::Vector2f(408,160));
		_livesCounter->setPosition(1104,0);
		_livesCounter->setTexture(_menuTexture);
		_livesCounter->setTextureRect(sf::IntRect(438,0,408,160));
		//drawVec.push_back(_livesCounter);
	_wavesCounter = new sf::RectangleShape(sf::Vector2f(508,153));
		_wavesCounter->setPosition(514,10);
		_wavesCounter->setTexture(_menuTexture);
		_wavesCounter->setTextureRect(sf::IntRect(0,191,773,233));
		//drawVec.push_back(_wavesCounter);

	// Grass Tile Objects
	grassTile = sf::RectangleShape(sf::Vector2f(60, 60));
	grassTile.setFillColor(sf::Color(100, 250, 50)); // green
	grassTile.setOutlineThickness(-1);
	grassTile.setOutlineColor(sf::Color(0, 0, 0, 50));
	// Ground Tile Objects
	groundTile = sf::RectangleShape(sf::Vector2f(60, 60));
	groundTile.setFillColor(sf::Color(153, 140, 85)); // brown
	groundTile.setOutlineThickness(-1);
	groundTile.setOutlineColor(sf::Color(0, 0, 0, 100));
	// Hover Object
	hoverOutline = sf::CircleShape(60);
	hoverOutline.setFillColor(sf::Color::Transparent);
	hoverOutline.setOutlineColor(sf::Color::Red);
	hoverOutline.setOutlineThickness(-3);
}

// Draws Map with Ground and Grass Objects
void GameBoard::renderBoard() {
	int mapX = 0, mapY = 0;
	// Each square is to be 60 pixels wide,
	// with an exact height of 18 tiles

	// Draw Grass Everywhere
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 18; y++) {
			grassTile.setPosition(x * 60, y * 60);
			window->draw(grassTile);
		}
	}
	// Draw Ground on Path Only
	for (unsigned int i = 0; i < path.size() - 1; i++) {
		Point curr = path[i];		// Current Point
		Point next = path[i + 1];		// Next Point
		mapX = curr.getX();
		mapY = curr.getY();
		if (curr.getX() == next.getX()) {			// If two points vertical
			while (mapY != next.getY()) {
				groundTile.setPosition(mapX * 60, mapY * 60);
				window->draw(groundTile);
				if (mapY < next.getY())
					mapY++;		// Draw up or down until next point
				else
					mapY--;
			}
		} else if (curr.getY() == next.getY()) {	// If two points horizontal
			while (mapX != next.getX()) {
				groundTile.setPosition(mapX * 60, mapY * 60);
				window->draw(groundTile);
				if (mapX < next.getX())
					mapX++;		// Draw left or right until next point
				else
					mapX--;
			}
		}
	}
	window->draw(*_tamsCounter);
	window->draw(*_livesCounter);
	window->draw(*_wavesCounter);
}

// Draw Hover Object
void GameBoard::renderHover(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / 60);
	int gridY = ceil(mouseY / 60);
	int backSquares = 0;
	if (range % 2 == 1)
		backSquares = floor(range / 2);

	hoverOutline.setRadius(range*60/2);
	hoverOutline.setPosition((gridX - backSquares) * 60,
			(gridY - backSquares) * 60);
	window->draw(hoverOutline);
}

GameController::GameController() {
	health = 100;
	tams = 100;
	currentWave = 0;
	froshRemaining = 100;
	froshEliminated = 0;
}

// Game State Accessors
int GameController::getHealth() {
	return this->health;
}
int GameController::getTams() {
	return this->tams;
}
int GameController::getCurrentWave() {
	return this->currentWave;
}
int GameController::getFroshRemaining() {
	return this->froshRemaining;
}
int GameController::getFroshEliminated() {
	return this->froshEliminated;
}

// Start the Game
void GameController::startGame() {

}

// End Current Game
void GameController::endGame() {

}

// Start Next Wave
void GameController::startWave() {
	this->currentWave++;
}

// Display Help Screen
void GameController::displayHelpScreen() {

}

// Update Player Lives
void GameController::updateHealth(int update) {
	this->health += update;
}

// Update Player Currency
void GameController::updateTam(int update) {
	this->tams += update;
}

// Point Class used for Map
Point::Point(int xIn, int yIn) {
	this->x = xIn;
	this->y = yIn;
}
// Accessors
int Point::getX() {
	return this->x;
}
int Point::getY() {
	return this->y;
}

// Main
int main() {
	debug = true;
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Frosh Defence");
	window->setFramerateLimit(60);
	sf::Font font;
	if (!font.loadFromFile("assets/georgia.ttf")) {
	}

	GameController gameController;
	GameBoard gameBoard;
	GameMenuController gameMenuController = GameMenuController(window);
	gameMenuController.setDebug(debug);
	sf::Event event;
	while (window->isOpen()) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed
					|| (event.type == sf::Event::KeyPressed
							&& event.key.code == sf::Keyboard::Escape)) {
				window->close();
			} else {
				gameMenuController.process(event, mousePos);
			}
		}

		int gridX = ceil(mousePos.x / 60);
		int gridY = ceil(mousePos.y / 60);
		if (debug) {
			text.setString(std::to_string(gridX) + "," + std::to_string(gridY));
			text.setFont(font);
			text.setPosition(float(mousePos.x), float(mousePos.y));
		}

		window->clear();
		gameBoard.renderBoard();
		gameBoard.renderHover(mousePos.x, mousePos.y, 5);
		gameMenuController.render();
		if (debug) {
			window->draw(text);
		}
		window->display();
	}
	return 0;
}
