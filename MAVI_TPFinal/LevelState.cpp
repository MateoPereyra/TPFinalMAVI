#include "LevelState.h"

using namespace sf;
using namespace std;

#include "Game.h"
#include "GameState.h"
#include "MenuState.h"

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Inits & Constructors <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void LevelState::loadAssetsLevel()
{
    //Carga de fuente
    font.loadFromFile("assets//Lost in Wild.ttf");

    //Carga de fondo
    texBackground.loadFromFile("assets//cloudy.png");

    //Carga botones
    texButton.loadFromFile("assets//boton_madera.png");
}

void LevelState::initVisualsLevel()
{
    /*
        1. Fondo
        2. Sprite del borde
        3. Botones (set + texture)
    */

    //Set y ajustar el fondo
    sBackground.setTexture(texBackground);
    Vector2u windowSize = game.getWindow().getSize();
    Vector2u textureSize = texBackground.getSize();

    sBackground.setScale(
        (float)windowSize.x / textureSize.x,
        (float)windowSize.y / textureSize.y
    );

    //Sprites
    //sBorder.setTexture(texBorder); //setpos en update     AUN NO TENGO EL HOVER

    //Set botones (con su texture)
    n1.setSize(Vector2f(80.f, 90.f));
    n1.setPosition(100, 200);
    n1.setTexture(&texButton);

    n2.setSize(Vector2f(80.f, 90.f));
    n2.setPosition(200, 200);
    n2.setTexture(&texButton);

    n3.setSize(Vector2f(80.f, 90.f));
    n3.setPosition(300, 200);
    n3.setTexture(&texButton);
}

void LevelState::initTextsLevel()
{
    /*
        En cada texto:
        1.fuente
        2.tamaño
        3.string
        4.color de borde
        5.grosor de borde

        6.Abajo del todo, centrar en los botones
    */

    //Textos con boton
    t1.setFont(font);
    t1.setCharacterSize(35);
    t1.setString("1");
    t1.setOutlineColor(Color::Black);
    t1.setOutlineThickness(5);

    t2.setFont(font);
    t2.setCharacterSize(35);
    t2.setString("2");
    t2.setOutlineColor(Color::Black);
    t2.setOutlineThickness(5);

    t3.setFont(font);
    t3.setCharacterSize(35);
    t3.setString("3");
    t3.setOutlineColor(Color::Black);
    t3.setOutlineThickness(5);

    //Center texts
    FloatRect textBounds = t1.getLocalBounds();

    t1.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    t1.setPosition(n1.getPosition() + n2.getSize() / 2.f);

    textBounds = t2.getLocalBounds();
    t2.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    t2.setPosition(n2.getPosition() + n2.getSize() / 2.f);

    textBounds = t3.getLocalBounds();
    t3.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    t3.setPosition(n3.getPosition() + n3.getSize() / 2.f);
}

LevelState::LevelState(Game& g) : State(g)
{
    loadAssetsLevel();
    initVisualsLevel();
    initTextsLevel();

    bLevel = 0;
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Game Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void LevelState::handleEvent(sf::Event& event)
{
    switch (event.type) { //Switch gral

    case Event::KeyPressed:
        switch (event.key.code) { //Switch keyboard

        case Keyboard::Escape:
            //game.pushState(make_unique<MenuState>(game));
            game.popState();
            break;

        case Keyboard::Left:
            if (bLevel > 1) {
                bLevel -= 1;
            }
            else {
                bLevel = 3;
            }
            break;

        case Keyboard::A:
            if (bLevel > 1) {
                bLevel -= 1;
            }
            else {
                bLevel = 3;
            }
            break;

        case Keyboard::Right:
            if (bLevel < 3) {
                bLevel += 1;
            }
            else {
                bLevel = 1;
            }
            break;

        case Keyboard::D:
            if (bLevel < 3) {
                bLevel += 1;
            }
            else {
                bLevel = 1;
            }
            break;

        case Keyboard::Enter:               //ACA TENGO QEU VER COMO HACER PARA QUE ENTRE EN UNO U OTRO NIVEL
            switch (bLevel) {
            case 1:
                game.pushState(make_unique<GameState>(game, 1));
                break;

            case 2:
                game.pushState(make_unique<GameState>(game, 2));
                break;

            case 3:
                game.pushState(make_unique<GameState>(game, 3));
                break;
            }
            break;

        default: //Switch teclado
            break;
        }

    case Event::MouseButtonPressed:
        if (event.mouseButton.button == Mouse::Left) { //Si es el izq

            // Convertir pos del mouse a coord
            Vector2f mousePos = wnd.mapPixelToCoords(Mouse::getPosition(wnd));

            //Chequeo si se clickeó sobre alguno de los botones
            if (n1.getGlobalBounds().contains(mousePos)) { //Entro al primer lvl
                game.pushState(make_unique<GameState>(game, 1));
            }

            if (n2.getGlobalBounds().contains(mousePos)) { //Entro al primer lvl
                game.pushState(make_unique<GameState>(game, 2));
            }

            if (n3.getGlobalBounds().contains(mousePos)) { //Entro al primer lvl
                game.pushState(make_unique<GameState>(game, 3));
            }
        }
    default: //Switch ppal
        break;
    }
    
}

void LevelState::update()
{
    mousePos = wnd.mapPixelToCoords(Mouse::getPosition(wnd));

    if (n1.getGlobalBounds().contains(mousePos))
        bLevel = 1;

    if (n2.getGlobalBounds().contains(mousePos))
        bLevel = 2;

    if (n3.getGlobalBounds().contains(mousePos))
        bLevel = 3;
}

void LevelState::render()
{
    //Set View Default
    wnd.setView(wnd.getDefaultView());

    //Dibujo
    wnd.draw(sBackground);

    //Botones
    wnd.draw(n1);
    wnd.draw(n2);
    wnd.draw(n3);
    //Borde de los botones
    //Textos
    wnd.draw(t1);
    wnd.draw(t2);
    wnd.draw(t3);
}

