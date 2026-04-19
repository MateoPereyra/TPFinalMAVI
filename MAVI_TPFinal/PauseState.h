#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class PauseState : public State {

private:
    //Texts
    sf::Font font;

    sf::Text tPausa;
    sf::Text tContinuar;
    sf::Text tOpciones;
    sf::Text tMenu;
    sf::Text tSalir;

    //Buttons
    sf::RectangleShape bContinuar;
    sf::RectangleShape bOpciones;
    sf::RectangleShape bMenu;
    sf::RectangleShape bSalir;
    sf::Texture texButton; //Cada boton usa esta textura, sin sprite
    int bLevel; //Para hover, borderline y teclas

    //Button borderlines
    sf::Texture texBorder; //                   A ESTE HAY QUE CAMBIAR POR UNO MEJOR
    sf::Sprite sBorder;

    //Fondo
    sf::Texture texBackground;
    sf::Sprite sBackground;

    //Mouse
    sf::Vector2f mousePos;

    //Inits
    void loadAssetsPause();
    void initVisualsPause();
    void initTextsPause();

public:
    PauseState(Game& g);

    //void onEnter() override; Aun no se si los uso
    //void onExit() override;

    void handleEvent(sf::Event& event) override;

    void update() override;
    void render() override;

};

#endif