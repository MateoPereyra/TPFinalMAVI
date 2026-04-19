#include "Shapey.h"

using namespace sf;
using namespace std;

Shapey::Shapey()
{
	//Objeto temporal, reemplazar por sprite y texture mas adelante
	shape.setFillColor(Color::White);
	shape.setSize(Vector2f(50.f, 50.f));

	this->setOnGround(false);
	canJump = true;
	blockFall = false;
	dashing = false;
}

Shapey::~Shapey()
{

}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Movimiento <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void Shapey::movementAcc(float delta) //Movimiento dinamico framerate independiente
{
	direction = Vector2f(0.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction.x = -1.f;

		if (velocity.x > -maxVelocity)
			velocity.x += direction.x * acceleration * delta * multiplier;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction.x = 1.f;

		if (velocity.x < maxVelocity)
			velocity.x += direction.x * acceleration * delta * multiplier;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))  //Salto
	{
		direction.y = -1.f;

		if (canJump && onGround && !blockFall) {
			velocity.y = jumpF * direction.y;
			onGround = false;
			canJump = false;
			dashing = false;
		}
	} else {
		canJump = true;
	}
}

void Shapey::movementDrag(float delta) //Frena el movimiento, "arrastre"
{
	if (velocity.x > 0.f) //Si va a la der
	{
		velocity.x -= drag * delta * multiplier;

		if (velocity.x < 0.f) //Para evitar que se pase
			velocity.x = 0.f;
	}
	else if (velocity.x < 0.f) { //Si va a la izq
		velocity.x += drag * delta * multiplier;

		if (velocity.x > 0.f)
			velocity.x = 0.f;
	}
}

void Shapey::fall(float delta) 
{
	//caida
	if (!onGround) {
		if (blockFall) {
			this->stopX();
			velocity.y += gravity * 3.f * delta * multiplier; // cae más fuerte
		}
		else {
			velocity.y += gravity * delta * multiplier;
		}
	}
}


void Shapey::stopX()
{
	velocity.x = 0.f;
}

void Shapey::stopY()
{
	velocity.y = 0.f;
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Otros del char <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void Shapey::change() //"Poderes"
{
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		if (!qPressed) {
			blockFall = !blockFall; //toggle
			qPressed = true;
		}

	} else {
		qPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::E)) {
		if (!ePressed && !dashing && !blockFall) {
			dashing = true;
			dashTimer = dashTime;
			ePressed = true;
			dashDir = direction.x;

			if (dashDir == 1) {
				direction.x = 1;
			} else if (dashDir == -1) {
				direction.x = -1;
			}
		}
	} else {
		if (onGround)
			ePressed = false;
	}
}

void Shapey::die()
{
	
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Game Functions  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void Shapey::update(float delta) 
{
	this->change();

	//Calculos de movimiento (Solo si esta en normal)
	if (!dashing) {
		this->movementAcc(delta);
		this->movementDrag(delta);
		this->fall(delta);
	}

	//Movimiento en dash
	if (dashing) {
		this->stopY();
		shape.move(dashDir * dashSpeed * delta * multiplier, 0.f);
		dashTimer -= delta;

		if (dashTimer <= 0.f) {
			dashing = false;
		}
	}

	this->setOnGround(false); //antes estaba abajo

	//Movimiento final
	if (!dashing) {
		shape.move(this->velocity.x * delta * this->multiplier, this->velocity.y * delta * this->multiplier);
	}
}

void Shapey::render(RenderWindow& wnd) 
{
	wnd.draw(shape);
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Setters <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void Shapey::setOnGround(bool val)
{
	onGround = val;
}

void Shapey::setPos(float x, float y)
{
	shape.setPosition(x, y);
}

void Shapey::setDashing(bool val) {
	dashing = val;
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Getters <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

Vector2f Shapey::getPos() const
{
	return shape.getPosition();
}

sf::Vector2f Shapey::getVel() const
{
	return velocity;
}

FloatRect Shapey::getBounds() const
{
	return shape.getGlobalBounds();
}

float Shapey::getTop() const
{
	return shape.getGlobalBounds().top;
}

float Shapey::getBottom() const
{
	return shape.getGlobalBounds().top + shape.getGlobalBounds().height;
}

float Shapey::getLeft() const
{
	return shape.getGlobalBounds().left;
}

float Shapey::getRight() const
{
	return shape.getGlobalBounds().left + shape.getGlobalBounds().width;
}

bool Shapey::getOnGround() const
{
	return onGround;
}

bool Shapey::getBlockFall() const
{
	return blockFall;
}

bool Shapey::getDashing() const
{
	return dashing;
}

float Shapey::getDir() const
{
	return dashDir;
}
