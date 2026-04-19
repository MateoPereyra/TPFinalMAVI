#ifndef STATE_H
#define STATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "Game.h"

class State {

protected:
    Game& game; //referencia al juego
    sf::RenderWindow& wnd; //Referencia a la ventana, me ahorro repetir codigo

public:
    State(Game& g) : game(g), wnd(g.getWindow()) {}
    virtual ~State() {}

    virtual void onEnter() {}
    virtual void onExit() {}

    virtual void handleEvent(sf::Event& event) = 0;

    virtual void update() = 0;
    virtual void render() = 0;

};

#endif 