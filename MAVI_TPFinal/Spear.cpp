#include "Spear.h"

using namespace sf;
using namespace std;

Spear::Spear(float x, float y)
{
	texSpear.loadFromFile("assets//pincho.png");
	sSpear.setTexture(texSpear);

	sSpear.setScale(96.f / 128.f, 64.f / 128.f);
	sSpear.setPosition(Vector2f(x, y));
}

void Spear::render(RenderWindow& wnd)
{
	wnd.draw(sSpear);
}

FloatRect Spear::getBounds()
{
	Vector2f pos = sSpear.getPosition();
	Vector2f scale = sSpear.getScale();

	float offsetX = 40.f * scale.x; 
	float offsetY = 5.f * scale.y; 
	float w = 48.f * scale.x; 
	float h = 118.f * scale.y;  

	return FloatRect(pos.x + offsetX, pos.y + offsetY, w, h);
}