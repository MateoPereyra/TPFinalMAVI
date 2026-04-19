#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "State.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class LevelState : public State {

private:
    //Texts
    sf::Font font;
    sf::Text t1;
    sf::Text t2;
    sf::Text t3;

    //Buttons
    sf::RectangleShape n1; //Botones de Niveles
    sf::RectangleShape n2;
    sf::RectangleShape n3;
    sf::Texture texButton;
    int bLevel; //Para hover, borderline y teclas

    //Button borderlines

    //Fondo
    sf::Texture texBackground;
    sf::Sprite sBackground;

    //Mouse
    sf::Vector2f mousePos;

    //Inits
    void loadAssetsLevel();
    void initVisualsLevel();
    void initTextsLevel();

public:
    LevelState(Game& g);

    //void onEnter() override; Aun no se si los uso
    //void onExit() override;

    void handleEvent(sf::Event& event) override;

    void update() override;
    void render() override;
};

#endif
