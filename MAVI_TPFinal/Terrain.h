#ifndef TERRAIN_H
#define TERRAIN_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"


class Terrain {

private:
	std::vector<sf::Sprite> parts;
	sf::FloatRect tBounds;

public:
	Terrain(float x, float y, float w, float h, sf::Texture& grassTex, sf::Texture& dirtTex);
	void render(sf::RenderWindow& wnd);

	sf::FloatRect getBounds();
	float getTop();
	float getBottom();
	float getLeft();
	float getRight();
};

#endif