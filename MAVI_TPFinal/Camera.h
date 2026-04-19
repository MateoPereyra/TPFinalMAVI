#ifndef CAMERA_H
#define CAMERA_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class Camera {

private:
	sf::View mainView;

	//O-at
	float limitX = mainView.getSize().x / 2.f; //Por ahora sin uso
	float limitY = mainView.getSize().y / 2.f; //

	//Private functions
	void initView(); //crea la cam
public:
	Camera();
	~Camera();
	void centerCam(sf::Vector2f targetPos); // Centro en el personaje (por ahora)
	void setCamera(sf::RenderWindow& wnd); //Settear como default

};

#endif