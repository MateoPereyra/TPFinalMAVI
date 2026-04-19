#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "Camera.h"
#include "Shapey.h"
#include "BaseEnemy.h"
#include "Terrain.h"
#include "Spear.h"

class GameState : public State {

private:
    //Para niveles
    int level;
    int monedas;
    float pasTime;
    bool gameDefeat;
    bool gameWin;
    sf::Font font;
    sf::Text tTiempo;
    sf::Text tMonedas;
    sf::Texture texFlag;
    sf::Sprite sFlag;
    sf::FloatRect flagBounds;
    sf::Texture texCoin;
    sf::Sprite sHUDCoin;
    std::vector<sf::Sprite> sCoin;
    sf::Texture texGrass;
    sf::Texture texDirt;

    //Objetos
    Camera cam;
    Shapey shapey;
    std::vector<std::unique_ptr<BaseEnemy>> enemies;
    std::vector<Terrain> grounds;
    std::vector<std::unique_ptr<Spear>> spears;

    //Delta time
    sf::Clock clock;
    float dt; //dt en 60fps ~= 0.016s

    //Fondo
    sf::Texture texBackground;
    sf::Sprite sBackground;

    //SOLO PARA CUANDO GANO/PIERDO
    //Texts
    sf::Text tReintentar;
    sf::Text tNiveles;
    sf::Text tSigN;
    sf::Text tMenu;
    sf::Text tDerrota;
    sf::Text tVictoria;
    sf::RectangleShape panel;
    sf::RectangleShape overlay;

    //Buttons
    sf::RectangleShape bReintentar;
    sf::RectangleShape bNiveles;
    sf::RectangleShape bSigN;
    sf::RectangleShape bMenu;
    //sf::Texture texButton; //Cada boton usa esta textura, sin sprite
    int bLevel; //Para hover, borderline y teclas

    //Mouse
    sf::Vector2f mousePos;

    //Init
    void loadAssetsGame(int level);
    void initVisualsGame(); //ESTE Y EL DE ARRIBA TENDRIAN QUE SALIR DE ACA
    void initTextsGame();
    void loadLevel(int level);
public:
    GameState(Game& g, int level);

    void onEnter() override;
    //void onExit() override;

    void handleEvent(sf::Event& event) override;

    void update() override;
    void render() override;

    void renderDefeat();
    void renderWin();

    //Para niveles
    void loadLevel1();
    void loadLevel2();
    void loadLevel3();
    bool isGameOver() const;

};

#endif