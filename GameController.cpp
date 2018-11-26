#include <SFML/Graphics.hpp>

#include <chrono>
#include <ctime>
#include <cmath>
#include <string>		// String object
#include <vector>		// Vector object
#include <iostream>

#include "GameController.h"
#include "GameMenuController.h"
#include "FroshController.h"
#include "FrecController.h"
#include "FrecAndFroshController.h"
#include "Frec.h"
#include "GameState.h"
#include "Timer.h"

using sf::Vector2f;
using std::cout;
using std::endl;

sf::RectangleShape grassTile;
sf::RectangleShape groundTile;
sf::CircleShape hoverOutline;
sf::RectangleShape shadowTile;
sf::RectangleShape* _tamsCounter;
sf::RectangleShape* _livesCounter;
sf::RectangleShape* _wavesCounter;
sf::RectangleShape helpScreen;

sf::Text tamText, waveText, waveWord, healthText, text;

const std::vector<Vector2f> path = { Vector2f(15, 0), Vector2f(15, 4), Vector2f(
		20, 4), Vector2f(20, 1), Vector2f(24, 1), Vector2f(24, 8), Vector2f(10,
		8), Vector2f(10, 4), Vector2f(5, 4), Vector2f(5, 14), Vector2f(10, 14),
		Vector2f(10, 12), Vector2f(14, 12), Vector2f(14, 15), Vector2f(20, 15),
		Vector2f(20, 11), Vector2f(24, 11), Vector2f(24, 18) };
sf::RenderWindow* window;

bool debug;

GameBoard::GameBoard(GameState* _gameState, FrecController* _frecController,
		int _width) :
		gameState(_gameState), frecController(_frecController), width(_width) {
	sf::Texture* _menuTexture = new sf::Texture;
	if (!_menuTexture->loadFromFile("assets/menuButtons.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	_tamsCounter = new sf::RectangleShape(sf::Vector2f(416, 160));
	_tamsCounter->setPosition(36, 0);
	_tamsCounter->setTexture(_menuTexture);
	_tamsCounter->setTextureRect(sf::IntRect(0, 0, 416, 160));

	_livesCounter = new sf::RectangleShape(sf::Vector2f(416, 160));
	_livesCounter->setPosition(1104, 0);
	_livesCounter->setTexture(_menuTexture);
	_livesCounter->setTextureRect(sf::IntRect(416, 0, 416, 160));

	_wavesCounter = new sf::RectangleShape(sf::Vector2f(508, 153));
	_wavesCounter->setPosition(514, 10);
	_wavesCounter->setTexture(_menuTexture);
	_wavesCounter->setTextureRect(sf::IntRect(0, 192, 768, 224));

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
	waveWord.setString("Wave");
	tamText.setPosition(220, 60);
	tamText.setCharacterSize(58);
	waveText.setPosition(820, 70);
	waveText.setCharacterSize(58);
	healthText.setPosition(1250, 60);
	healthText.setCharacterSize(58);
	waveWord.setPosition(625, 85);
	waveWord.setCharacterSize(40);

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
	// Shadow Object
	shadowTile = sf::RectangleShape(sf::Vector2f(60, 60));
	shadowTile.setFillColor(sf::Color(255, 0, 0, 150));
}

bool GameBoard::gridSpaceAvailable(int gridX, int gridY) {
	if (gridStatus[gridX][gridY] == 0 && gridStatus[gridX + 1][gridY] == 0
			&& gridStatus[gridX][gridY + 1] == 0
			&& gridStatus[gridX + 1][gridY + 1] == 0) {
		return true;
	} else
		return false;
}

bool GameBoard::frecIsPurchasable(FrecType type) {
	if (type != FrecType::empty) {
		if (gameState->getTams() >= gameState->getFrecProps(type)["tam"]) {
			return true;
		}
	}
	return false;
}

// Determine if any action needs ton be taken by
// cliking on the game board
void GameBoard::process(sf::Event event, sf::Vector2i mousePos) {
	if (mousePos.x >= width) {
		return;
	}

	int gridX = ceil(mousePos.x / 60);
	int gridY = ceil(mousePos.y / 60);
	if ((event.type == sf::Event::MouseButtonPressed)
			&& (event.mouseButton.button == sf::Mouse::Left)) {
		FrecType type = gameState->getPurchaseFrec();
		// If an open space exists, fill the board with twos.
		if (gridSpaceAvailable(gridX, gridY) && frecIsPurchasable(type)) {
			gridStatus[gridX][gridY] = 2;
			gridStatus[gridX + 1][gridY] = 2;
			gridStatus[gridX][gridY + 1] = 2;
			gridStatus[gridX + 1][gridY + 1] = 2;
			sf::Vector2f spawnPos = sf::Vector2f(gridX * gameState->cubit,
					gridY * gameState->cubit);
			std::cout << "Spawn Pos: " << spawnPos.x << " " << spawnPos.y
					<< std::endl;
			frecController->spawnFrec(spawnPos, type);
			gameState->updateTamBy(-(gameState->getFrecProps(type)["tam"]));
		}
		//PRINT BOARD
		if (debug) {
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

bool GameBoard::validatePos(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / 60);
	int gridY = ceil(mouseY / 60);
	for (int x = 0; x < range; x++) {
		for (int y = 0; y < range; y++) {
			if (gridStatus[gridX + x][gridY + y] != 0)
				return false;
		}
	}
	return true;
}

// Draws Map with Ground and Grass Objects
void GameBoard::render() {
	sf::Vector2i mousePos = gameState->mousePos;

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
		sf::Vector2i curr = sf::Vector2i(path[i]);		// Current Vector2f
		sf::Vector2i next = sf::Vector2i(path[i + 1]);		// Next Vector2f
		if (curr.x == next.x) {			// If two Vector2fs vertical
			while (curr.y != next.y) {
				groundTile.setPosition(curr.x * 60, curr.y * 60);
				window->draw(groundTile);
				if (curr.y < next.y)
					curr.y++;		// Draw up or down until next Vector2f
				else
					curr.y--;
				gridStatus[curr.x][curr.y] = 1;
			}
		} else if (curr.y == next.y) {	// If two Vector2fs horizontal
			while (curr.x != next.x) {
				groundTile.setPosition(curr.x * 60, curr.y * 60);
				window->draw(groundTile);
				if (curr.x < next.x)
					curr.x++;		// Draw left or right until next Vector2f
				else
					curr.x--;
				gridStatus[curr.x][curr.y] = 1;
			}
		}
	}

	window->draw(*_tamsCounter);
	window->draw(*_livesCounter);
	window->draw(*_wavesCounter);
	window->draw(tamText);
	window->draw(waveText);
	window->draw(healthText);
	window->draw(waveWord);
	FrecType type = gameState->getPurchaseFrec();
	if (type != FrecType::empty) {
		renderRange(mousePos.x, mousePos.y,
				gameState->getFrecProps(type)["range"]);
		std::cout << "range is " << gameState->getFrecProps(type)["range"]
				<< std::endl;
		renderShadow(mousePos.x, mousePos.y, 2);
	}
}

// Draw Range
void GameBoard::renderRange(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / 60) * 60 + 60;
	int gridY = ceil(mouseY / 60) * 60 + 60;

	hoverOutline.setRadius(range);
	hoverOutline.setPosition(gridX - range, gridY - range);
	window->draw(hoverOutline);
}

// Draw Placement Shadow
void GameBoard::renderShadow(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / 60);
	int gridY = ceil(mouseY / 60);
	shadowTile.setSize(sf::Vector2f(range * 60, range * 60));
	shadowTile.setPosition(gridX * 60, gridY * 60);
	window->draw(shadowTile);
}

GameController::GameController() {
}

// Main
int main() {
// Initialization
	debug = false;
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Frosh Defence");
	window->setFramerateLimit(60);
	sf::Font font;
	if (!font.loadFromFile("assets/georgia.ttf")) {
	} else {
		tamText.setFont(font);
		waveText.setFont(font);
		healthText.setFont(font);
		waveWord.setFont(font);
	}

	Timer* clk = new Timer();
	GameState* gameState = new GameState(clk);
	GameMenuController* gameMenuController = new GameMenuController(window,
			gameState);
	FrecController* frecController = new FrecController(window, gameState);
	FroshController* froshController = new FroshController(window, gameState,
			path);
	GameBoard* gameBoard = new GameBoard(gameState, frecController,
			gameMenuController->getMenuPos().x);

	FrecAndFroshController* attackController = new FrecAndFroshController(
			window, gameState, froshController, frecController->getFrecVec(),
			froshController->getFroshVec());

// TODO: Remove this temp frosh creating code
	//froshController->spawnFrosh(sf::Vector2f(100, 100), FroshType::fast);
	//froshController->spawnFrosh(sf::Vector2f(500, 500), FroshType::regular);


	gameMenuController->setDebug(debug);
	sf::Event event;
// Main game loop
	while (window->isOpen()) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		gameState->mousePos = mousePos;

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
						return 0;
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
				gameMenuController->process(event, mousePos);
				gameBoard->process(event, mousePos);
			}
		}

		if (clk->newTick()) {
			//update
			froshController->update();
			attackController->update();
		}

		if (gameState->dirtyBit) {
			waveText.setString(std::to_string(gameState->getCurrentWave()));
			healthText.setString(std::to_string(gameState->getHealth()));
			tamText.setString(std::to_string(gameState->getTams()));
			gameState->dirtyBit = false;
		}
		// Render
		window->clear();
		gameBoard->render();
		froshController->render();
		frecController->render();
		gameMenuController->render();
		attackController->render();
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
