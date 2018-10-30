/*
 * Game.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: Taffy
 *
 *  CONNOR WAS HERE!
 */

#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"

// Define an event that is checked by the event poller
sf::Event event;
sf::Texture background_texture;
sf::Texture zergling_texture;
sf::Sprite background;
//sf::Sprite zergling;
sf::CircleShape zergling;
sf::Font font;
sf::Text text;

Game::Game() : _window(sf::VideoMode(1650, 1250), "Frosh Defence"){
	_window.setFramerateLimit(60); //set the frame limit to 60
	// ------------------------------
	// Define textures and sprites
	// ------------------------------
	// Define the background image covering the entire canvas (at 0, 0)
	if (!background_texture.loadFromFile("assets/test_board.jpg")){
		std::cerr << "The texture does not exist" << std::endl;
	}
	background.setTexture(background_texture);

	// Define a shape mapped by a texture
	if (!zergling_texture.loadFromFile("assets/zergling.png")){
			std::cerr << "The texture does not exist" << std::endl;
		}
    zergling = sf::CircleShape(200);
	zergling.setTexture(&zergling_texture);
	zergling.setPosition(100, 100);

	// ------------------------------
	// Font Things
	// ------------------------------
	// Create a font object and load it from file relative
	if (!font.loadFromFile("assets/georgia.ttf")){
		std::cerr << "The font does not exist" << std::endl;
	}
	//Create Hello World text objecct using our font and size 128pt
	text = sf::Text("Hello World", font, 90);
	//Set the text color to red
	text.setFillColor(sf::Color::Red);
}

void Game::process() {
// Handle window events
	while (_window.pollEvent(event)){
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window); // window is a sf::Window
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			// Event driven input handling
			// Check zergling sprite
			if (zergling.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				std::cout << "boom" << std::endl;
				zergling.setPosition(mousePos.x - 200, mousePos.y - 200);
			} else {
				std::cout << "Mouse" << mousePos.x << " " << mousePos.y << std::endl;
				sf::FloatRect zerg_bound = zergling.getGlobalBounds();
				std::cout << "Zerg x-axis" << zerg_bound.left << " "<< zerg_bound.left + zerg_bound.width << std::endl;
				std::cout << "Zerg y-axis" << zerg_bound.top << " "<< zerg_bound.top + zerg_bound.height << std::endl;

				// Check text sprite
				// Get the text object's physical dimensions and use them to center the text to our render window
				// By default things are drawn relative to their top left corner and can be changed by calling setOrigin()
				sf::FloatRect bounds(text.getLocalBounds());
				text.setPosition(mousePos.x - (bounds.left + bounds.width/2),
						mousePos.y - (bounds.top + bounds.height/2));
			}
      }
      if (event.type == sf::Event::EventType::Closed ||
          (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        _window.close();
		}
	}
}

void Game::update() {
	// for each frosh { frosh.update() }
	// for each tower { tower.update() }
}

void Game::render() {
    _window.clear(sf::Color::White);
    _window.draw(background);
    _window.draw(text);
    _window.draw(zergling);
    _window.display();
}

void Game::run() {
  while (_window.isOpen()){
	  process();
	  update();
	  render();
	  // Update the clock
  }
}

int main(int argc, char** argv){
  Game game;
  game.run();
}
