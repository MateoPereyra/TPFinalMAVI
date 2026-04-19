#include "BaseEnemy.h"

using namespace sf;
using namespace std;

BaseEnemy::BaseEnemy(float x, float y, float max)
{
	texEnemy.loadFromFile("assets//baseenemy.png");
	enemy.setTexture(texEnemy);
	enemy.setScale(96.0f / 1024.0f, 96.0f / 1024.0f);

	enemy.setPosition(x, y - 32.0f);
	direction = false;
	spawn = enemy.getPosition();
	leftLimit = spawn.x - max;
	rightLimit = spawn.x + max;
}

void BaseEnemy::update(float delta) 
{
	//Segun cuanto se mueva, va a un lado o al otro
	if (enemy.getPosition().x >= rightLimit) {
		direction = false; 
	} else if (enemy.getPosition().x <= leftLimit) {
		direction = true;
	}

	if (direction) {
		enemy.move(2.5f * delta * multiplier, 0.f);
	} else {
		enemy.move(-2.5f * delta * multiplier, 0.f);
	}

}

void BaseEnemy::render(RenderWindow& wnd)
{
	wnd.draw(enemy);
}

FloatRect BaseEnemy::getBounds() const
{
	//return enemy.getGlobalBounds();
	Vector2f pos = enemy.getPosition();
	Vector2f scale = enemy.getScale();

	float offsetX = 50.f * scale.x;
	float offsetY = 80.f * scale.y;
	float w = 900.f * scale.x;
	float h = 870.f * scale.y;

	return FloatRect(pos.x + offsetX, pos.y + offsetY, w, h);
}
