#ifndef SHAPEY_H
#define SHAPEY_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class Shapey {

private:
	//Shapey
	/*sf::Texture texCir;
	sf::Texture texCuad;            ESTO TIENE QUE SER UN SOLO TEXTURE O ALGO ASI, TODOS LOS FRAMES VAN A ESTAR EN UN MISMO SPRITESHEET
	sf::Texture texTri;*/
	sf::RectangleShape shape;

	//Atributos de movimiento dinamico
	float multiplier = 60.f; //multiplicador del dt
	float maxVelocity = 10.f;
	float acceleration = 1.f;            //ESTO TIENE QUE SER VALOR DE GRAVEDAD
	float drag = 0.5f;
	sf::Vector2f velocity;
	sf::Vector2f direction;
	float gravity = 0.9f;
	float jumpF = 16.f; 
	bool onGround;
	bool canJump;

	//Para los "poderes"
	bool qPressed;
	bool blockFall;
	bool ePressed;
	bool dashing;
	float dashSpeed = 50.f;
	float dashTime = 0.1f;   //duración del dash
	float dashTimer = 0.f;
	int dashDir = 0;

public:
	Shapey();
	~Shapey();

	//Movimiento
	void movementAcc(float delta);
	void movementDrag(float delta);
	void fall(float delta); 

	void stopX();                  
	void stopY();

	//otros
	void change();
	void die();

	//Manejo del char
	void update(float delta); //mueve a shapey
	void render(sf::RenderWindow& wnd);

	//Setters 
	void setOnGround(bool val);
	void setPos(float x, float y);
	void setDashing(bool val); //Para evitar penetrar paredes

	//Getters
	sf::Vector2f getPos() const;
	sf::Vector2f getVel() const;
	sf::FloatRect getBounds() const;
	float getTop() const;
	float getBottom() const;
	float getLeft() const;
	float getRight() const;
	bool getOnGround() const;
	bool getBlockFall() const;
	bool getDashing() const;
	float getDir() const;

};

#endif 