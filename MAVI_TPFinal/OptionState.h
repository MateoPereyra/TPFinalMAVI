#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include "State.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class OptionState : public State {

private:
    //Texts
    sf::Font font;
    sf::Text tControls;
    sf::Text tSaltar;
    sf::Text tIzq;
    sf::Text tDer;
    sf::Text tSalir;
    
    //Botones
    sf::RectangleShape bSalir;
    sf::Texture texButton;

    //Button borderlines
    sf::Texture texBorder;
    sf::Sprite sBorder;
    
    //Fondo
    sf::Texture texBackground;
    sf::Sprite sBackground;

    //Inits
    void loadAssetsOption();
    void initVisualsOption();
    void initTextsOption();
public:
    OptionState(Game& g); 

    //void onEnter() override; Aun no se si los uso
    //void onExit() override;

    void handleEvent(sf::Event& event) override;

    void update() override;
    void render() override;
};

#endif