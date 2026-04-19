#include "Game.h"

using namespace sf;
using namespace std;

//Includes unicos para el .cpp
#include "MenuState.h"


/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Inits & Constructors <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void Game::initVar()
{
	this->window = nullptr;
}

void Game::initWin() //Creo la ventana
{
	this->video.width = 1280;
	this->video.height = 720;

	this->window = new RenderWindow(this->video, "Shapey's tales");
	//this->window->setFramerateLimit(60);
}

Game::Game() //Llama ambos inits y carga el primer estado del juego -> entra directo al menu
{
	this->initVar();
	this->initWin();

	this->pushState(make_unique<MenuState>(*this));
}

Game::~Game()
{

	delete this->window;
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Game Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void Game::run() 
{
	while (this->getWindowState())
	{
		eventPoll();
		update();
		render();
	}
}

void Game::eventPoll() //Loop de eventos
{

	while (this->window->pollEvent(e))
	{
		if (e.type == Event::Closed) 
		{
            this->window->close();
        }

        // Cada estado maneja sus eventos -> le dice vo loco ponete a laburar y el loco labura, el loco sabe que tiene que hacer
		if(!states.empty())
			states.top()->handleEvent(e);
	}
}

void Game::update() //llama al update del estado actual
{
	if (!states.empty())
		states.top()->update();
}

void Game::render() //Limpia, llama al render del estado actual, lo muestra
{ 
	this->window->clear();

	if (!states.empty())
		states.top()->render();

	this->window->display();
}

RenderWindow& Game::getWindow() //Devuelva la ventana
{
	return *this->window;
}

bool Game::getWindowState() const //Devuelve estado de la ventana
{
	return this->window->isOpen();
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Otras Funciones <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void Game::pushState(std::unique_ptr<State> newState) //Agrega un nuevo estado, va a ser el activo (top)
{
	states.push(move(newState));
	states.top()->onEnter();
}

void Game::replaceState(std::unique_ptr<State> newState)
{
	if (!states.empty()) {
		states.top()->onExit();
		states.pop();
	}
	states.push(move(newState));
	states.top()->onEnter();
}

void Game::popState() //Elimina el ultimo estado (top) -> el de debajo se vuelve el activo
{
	if (!states.empty())
	{
		states.top()->onExit();
		states.pop();
		if (!states.empty())
			states.top()->onEnter(); //aviso al estado ant que vuelve a ser activo
	}
}

State* Game::getCurrentTop()
{
	if (states.empty()){
		return nullptr;
	}

	return states.top().get();
}