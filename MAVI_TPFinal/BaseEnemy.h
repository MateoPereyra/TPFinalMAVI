#ifndef BASEENEMY_H
#define BASEENEMY_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class BaseEnemy {

private:
	sf::Texture texEnemy;
	sf::Sprite enemy;
	float multiplier = 60.f;
	bool direction;
	sf::Vector2f spawn;
	float leftLimit;
	float rightLimit;

public:
	BaseEnemy(float x, float y, float max); 
	void update(float delta);
	void render(sf::RenderWindow& wnd);
	sf::FloatRect getBounds() const;
};

#endif 


