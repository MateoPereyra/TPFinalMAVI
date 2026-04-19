#include "OptionState.h"

using namespace sf;
using namespace std;

#include "MenuState.h"
#include "Game.h"

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Inits & Constructors <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void OptionState::loadAssetsOption()
{
    //Carga de fuente
    font.loadFromFile("assets//Lost in Wild.ttf");

    //Carga de fondo
    texBackground.loadFromFile("assets//cloudy.png");

    //Carga botones
    texButton.loadFromFile("assets//boton_madera.png");
    texBorder.loadFromFile("assets//cursorTarget.png");
}

void OptionState::initVisualsOption()
{
    /*
        1. Fondo
        2. Sprite del borde
        3. Botones (set + texture)
    */

    //Fondo
    sBackground.setTexture(texBackground);
    Vector2u windowSize = game.getWindow().getSize();
    Vector2u textureSize = texBackground.getSize();

    sBackground.setScale(
        (float)windowSize.x / textureSize.x,
        (float)windowSize.y / textureSize.y
    );

    //Sprites
    sBorder.setTexture(texBorder);

    //Set botones
    bSalir.setSize(Vector2f(200.f, 60.f));
    bSalir.setPosition(250, 600);
    bSalir.setTexture(&texButton);
}

void OptionState::initTextsOption()
{
    //Textos sin boton
    tControls.setFont(font);
    tControls.setCharacterSize(20);
    tControls.setString("Controles: ");
    tControls.setOutlineColor(Color::Black);
    tControls.setOutlineThickness(5);
    tControls.setPosition(300, 300);

    tSaltar.setFont(font);
    tSaltar.setCharacterSize(20);
    tSaltar.setString("Saltar: W");
    tSaltar.setOutlineColor(Color::Black);
    tSaltar.setOutlineThickness(5);
    tSaltar.setPosition(450, 300);

    tIzq.setFont(font);
    tIzq.setCharacterSize(20);
    tIzq.setString("Izquierda: A");
    tIzq.setOutlineColor(Color::Black);
    tIzq.setOutlineThickness(5);
    tIzq.setPosition(450, 365);

    tDer.setFont(font);
    tDer.setCharacterSize(20);
    tDer.setString("Derecha: D");
    tDer.setOutlineColor(Color::Black);
    tDer.setOutlineThickness(5);
    tDer.setPosition(450, 430);

    //Textos con boton
    tSalir.setFont(font);
    tSalir.setCharacterSize(20);
    tSalir.setString("Salir");
    tSalir.setOutlineColor(Color::Black);
    tSalir.setOutlineThickness(5);

    //Center texts
    FloatRect textBounds = tSalir.getLocalBounds();

    tSalir.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    tSalir.setPosition(bSalir.getPosition() + bSalir.getSize() / 2.f);
}

OptionState::OptionState(Game& g) : State(g)
{
    loadAssetsOption();
    initVisualsOption();
    initTextsOption();
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Game Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void OptionState::handleEvent(sf::Event& event)
{
    RenderWindow& wnd = game.getWindow(); //Referencia a la ventana

    switch (event.type) //Switch general
    {
    case Event::KeyPressed: //Si es de tipo teclado, entra a este switch
        switch (event.key.code) {

        case Keyboard::Escape:
            game.popState();
            break;

        default:
            break;
        }
        break;

    case Event::MouseButtonPressed: //Si se clickea
        if (event.mouseButton.button == Mouse::Left) { //Si es el izq

            // Convertir pos del mouse a coord
            Vector2f mousePos = wnd.mapPixelToCoords(Mouse::getPosition(wnd));

            //Chequeo si se clickeó sobre alguno de los botones
            if (bSalir.getGlobalBounds().contains(mousePos)) { //Cierro el juego
                game.popState();
            }
        }

        break;

    default:
        break;
    }
}

void OptionState::update()
{
}

void OptionState::render()
{
    RenderWindow& wnd = game.getWindow();

    //Set View Default
    wnd.setView(wnd.getDefaultView());

    //Dibujo
    wnd.draw(sBackground);

    wnd.draw(bSalir);

    wnd.draw(tControls);
    wnd.draw(tSaltar);
    wnd.draw(tIzq);
    wnd.draw(tDer);
    wnd.draw(tSalir);
}
