#ifndef GAME_H
#define GAME_H

#include <memory>
#include <stack>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class State; //forward

class Game
{

private:
	//Objetos pantalla
	sf::RenderWindow* window;
	sf::VideoMode video;

	//Control del juego y estados
	sf::Event e;
	std::stack<std::unique_ptr<State>> states; //Pila de punteros unicos a State

	//Private Init Functions
	void initVar();
	void initWin();
public:
	//Constructores
	Game();
	~Game();

	//Funciones main
	void run();
	void eventPoll();
	void update();
	void render();
	bool getWindowState() const;
	sf::RenderWindow& getWindow(); //para obtener la ventana y poder manejarla desde fuera 

	//Funciones para estados
	void pushState(std::unique_ptr<State> newState);
	void replaceState(std::unique_ptr<State> newState);
	void popState();
	State* getCurrentTop();

};

#endif