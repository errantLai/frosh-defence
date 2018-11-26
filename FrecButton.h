/*
 * FrecButton.h
 *
 *  Created on: Nov 10, 2018
 *      Author: Taffy
 */

#ifndef FRECBUTTON_H_
#define FRECBUTTON_H_
#include "Clickable.h"
#include "GameState.h"
#include <string>

class FrecButton: public Clickable {
public:
	FrecButton(sf::Vector2f _position, int _radius, sf::Texture* _texture,
			std::string inText, std::string in, FrecType _type, GameState* _gameState);
	void setTextureRect(const sf::IntRect& rect);
	virtual ~FrecButton();
	FrecType getFrecType();
	void setTransparency(const int transparency);

	void update() override;
	// Draw the button, relying on textures/shapes defined
	// by the class that implements this interface.
	void render(sf::RenderWindow& _window) override;

private:
	FrecType frecType;
	GameState* gameState;

	void onClick() override;
	void onMouseEnter() override;
	void onMousePressed() override;
	void onMouseLeave() override;
	sf::CircleShape graphic;
	bool displayText;
	sf::Text frecButtonText;
	sf::Text frecButtonText2;
	sf::RectangleShape frecTextBack;
};

#endif /* FRECBUTTON_H_ */
