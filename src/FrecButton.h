/*
 * FrecButton.h
 *
 *  Created on: Nov 10, 2018
 *      Author: Taffy
 */

#ifndef FRECBUTTON_H_
#define FRECBUTTON_H_
#include "Clickable.h"

class FrecButton: public Clickable {
public:
	FrecButton(sf::Vector2f _position, int _radius, sf::Texture* _texture);
	void setTextureRect(const sf::IntRect& rect);
	virtual ~FrecButton();

	void update() override;
	// Draw the button, relying on textures/shapes defined
	// by the class that implements this interface.
	void render(sf::RenderWindow& _window) override;

private:
	void onClick() override;
	void onMouseEnter() override;
	void onMousePressed() override;
	void onMouseLeave() override;
	sf::CircleShape graphic;
};

#endif /* FRECBUTTON_H_ */
