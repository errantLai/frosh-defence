/*
 * MenuButton.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Connor
 */

#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_
#include "Clickable.h"

class MenuButton: public Clickable{
public:
	MenuButton(sf::Vector2f _position, int _sizex, int _sizey, sf::Texture* _texture, int type);
	void setTextureRect(const sf::IntRect& rect);
	void update() override;
	void render(sf::RenderWindow& _window) override;

private:
	void onClick() override;
	void onMouseEnter() override;
	void onMousePressed() override;
	void onMouseLeave() override;
	sf::RectangleShape graphic;
	int type;
	// 0 - sound
	// 1 - help
	// 2 - pause
};






#endif /* MENUBUTTON_H_ */
