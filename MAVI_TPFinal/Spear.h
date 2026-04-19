#ifndef SPEAR_H
#define SPEAR_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class Spear {
private:
	sf::Texture texSpear;
	sf::Sprite sSpear;

public:
	Spear(float x, float y);
	void render(sf::RenderWindow& wnd);

	sf::FloatRect getBounds();
};

#endif