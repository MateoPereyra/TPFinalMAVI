#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class MenuState : public State {
    
private:
    //Texts
    sf::Font font;

    sf::Text tTitle;
    sf::Text tJugar;
    sf::Text tOpciones;
    sf::Text tSalir;

    //Buttons
    sf::RectangleShape bJugar;
    sf::RectangleShape bOpciones;
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
    void loadAssetsMenu();
    void initVisualsMenu();
    void initTextsMenu();
public:
    MenuState(Game& g);

    //void onEnter() override; Aun no se si los uso
    //void onExit() override;

    void handleEvent(sf::Event& event) override;

    void update() override;
    void render() override;
};

#endif 