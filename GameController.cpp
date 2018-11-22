#include <SFML/Graphics.hpp>

#include <chrono>
#include <ctime>
#include <cmath>
#include <string>		// String object
#include <vector>		// Vector object
#include "GameController.h"
#include "GameMenuController.h"
#include "gameState.h"
#include "Timer.h"
#include <iostream>

sf::RectangleShape grassTile;
sf::RectangleShape groundTile;
sf::CircleShape hoverOutline;
sf::RectangleShape* _tamsCounter;
sf::RectangleShape* _livesCounter;
sf::RectangleShape* _wavesCounter;
sf::RectangleShape helpScreen;

sf::Text tamText, waveText, healthText, text;

std::vector<Point> path =
		{ Point(15, 0), Point(15, 4), Point(20, 4), Point(20, 1), Point(24, 1),
				Point(24, 8), Point(10, 8), Point(10, 4), Point(5, 4), Point(5,
						14), Point(10, 14), Point(10, 12), Point(14, 12), Point(
						14, 15), Point(20, 15), Point(20, 11), Point(24, 11),
				Point(24, 18) };
sf::RenderWindow* window;

bool debug;

GameBoard::GameBoard() {
	init();
}
void GameBoard::init() {
	sf::Texture* _menuTexture = new sf::Texture;
	if (!_menuTexture->loadFromFile("assets/menuInfo.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	_tamsCounter = new sf::RectangleShape(sf::Vector2f(398, 156));
	_tamsCounter->setPosition(36, 0);
	_tamsCounter->setTexture(_menuTexture);
	_tamsCounter->setTextureRect(sf::IntRect(0, 0, 398, 156));

	_livesCounter = new sf::RectangleShape(sf::Vector2f(408, 160));
	_livesCounter->setPosition(1104, 0);
	_livesCounter->setTexture(_menuTexture);
	_livesCounter->setTextureRect(sf::IntRect(438, 0, 408, 160));

	_wavesCounter = new sf::RectangleShape(sf::Vector2f(508, 153));
	_wavesCounter->setPosition(514, 10);
	_wavesCounter->setTexture(_menuTexture);
	_wavesCounter->setTextureRect(sf::IntRect(0, 191, 773, 233));

	sf::Texture* _helpTexture = new sf::Texture;
	if (!_helpTexture->loadFromFile("assets/help_screen.jpg")) {
		std::cerr << "Error loading the help screen" << std::endl;
	}

	helpScreen = sf::RectangleShape(sf::Vector2f(1920, 1080));
	helpScreen.setPosition(0, 0);
	helpScreen.setTexture(_helpTexture);

	tamText.setString(std::to_string(100));
	waveText.setString(std::to_string(0));
	healthText.setString(std::to_string(100));
	tamText.setPosition(220, 60);
	tamText.setCharacterSize(58);
	waveText.setPosition(810, 70);
	waveText.setCharacterSize(58);
	healthText.setPosition(1220, 60);
	healthText.setCharacterSize(58);

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

void GameBoard::process(sf::Event event, sf::Vector2i mousePos) {
	int gridX = ceil(mousePos.x / 60);
	int gridY = ceil(mousePos.y / 60);
	if ((event.type == sf::Event::MouseButtonPressed)
			&& (event.mouseButton.button == sf::Mouse::Left)) {
		// If an open space exists, fill the board with twos.
		if (gridStatus[gridX][gridY] == 0 && gridStatus[gridX + 1][gridY] == 0
				&& gridStatus[gridX][gridY + 1] == 0
				&& gridStatus[gridX + 1][gridY + 1] == 0) {
			gridStatus[gridX][gridY] = 2;
			gridStatus[gridX + 1][gridY] = 2;
			gridStatus[gridX][gridY + 1] = 2;
			gridStatus[gridX + 1][gridY + 1] = 2;
			// TODO: Create frec object via its controller
		}

		if (debug) {
			//PRINT BOARD
			for (int i = 0; i < 18; i++) {
				for (int j = 0; j < 32; j++) {
					std::cout << gridStatus[j][i] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;

		}
	}
}

// Draws Map with Ground and Grass Objects
void GameBoard::render() {
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
				gridStatus[mapX][mapY] = 1;
			}
		} else if (curr.getY() == next.getY()) {	// If two points horizontal
			while (mapX != next.getX()) {
				groundTile.setPosition(mapX * 60, mapY * 60);
				window->draw(groundTile);
				if (mapX < next.getX())
					mapX++;		// Draw left or right until next point
				else
					mapX--;
				gridStatus[mapX][mapY] = 1;
			}
		}

	}

	window->draw(*_tamsCounter);
	window->draw(*_livesCounter);
	window->draw(*_wavesCounter);
	window->draw(tamText);
	window->draw(waveText);
	window->draw(healthText);
}

// Draw Hover Object
void GameBoard::renderHover(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / 60);
	int gridY = ceil(mouseY / 60);
	int backSquares = 0;
	if (range % 2 == 1)
		backSquares = floor(range / 2);

	hoverOutline.setRadius(range * 60 / 2);
	hoverOutline.setPosition((gridX - backSquares) * 60,
			(gridY - backSquares) * 60);
	window->draw(hoverOutline);
}

GameController::GameController() {
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
	// Initialization
	debug = false;
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Frosh Defence");
	window->setFramerateLimit(60);
	sf::Font font;
	if (!font.loadFromFile("assets/georgia.ttf")) {
	}

	Timer* clk = new Timer();
	GameState* gameState = new GameState(clk);
	GameController gameController;
	GameBoard gameBoard;
	GameMenuController gameMenuController = GameMenuController(window,
			gameState);
	gameMenuController.setDebug(debug);

	tamText.setFont(font);
	waveText.setFont(font);
	healthText.setFont(font);

	clk->start();
	sf::Event event;
	// Main game loop
	while (window->isOpen()) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

		// Display the help menu
		if (gameState->getHelperState()) {
			window->clear();
			window->draw(helpScreen);
			window->display();
			while (gameState->getHelperState()) {
				while (window->pollEvent(event)) {
					if (event.type == sf::Event::EventType::Closed
							|| (event.type == sf::Event::KeyPressed
									&& event.key.code == sf::Keyboard::Escape)) {
						window->close();
					} else if ((event.type == sf::Event::MouseButtonReleased)
							&& (event.mouseButton.button == sf::Mouse::Left)) {
						gameState->toggleHelpScreen();
					}
				}
			}
		}

		// Process
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed
					|| (event.type == sf::Event::KeyPressed
							&& event.key.code == sf::Keyboard::Escape)) {
				window->close();
			} else {
				gameMenuController.process(event, mousePos);
				gameBoard.process(event, mousePos);
			}
		}

		// Update
		if (gameState->dirtyBit) {
			waveText.setString(std::to_string(gameState->getCurrentWave()));
			healthText.setString(std::to_string(gameState->getHealth()));
			tamText.setString(std::to_string(gameState->getTams()));
			gameState->dirtyBit = false;
		}

		// Render
		window->clear();
		gameBoard.render();
		gameBoard.renderHover(mousePos.x, mousePos.y, 5);
		gameMenuController.render();
		if (debug) {
			//text.setString(std::to_string(gridX) + "," + std::to_string(gridY));
			text.setString(std::to_string(clk->elapsedTicks()));
			text.setFont(font);
			text.setPosition(float(mousePos.x), float(mousePos.y));
			window->draw(text);
		}
		window->display();
	} // End of main game loop
	return 0;
}
