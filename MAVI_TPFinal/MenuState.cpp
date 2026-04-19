#include "MenuState.h"

using namespace sf;
using namespace std;

#include "Game.h"
#include "LevelState.h"
#include "OptionState.h"

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Inits & Constructors <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void MenuState::loadAssetsMenu()
{
    //Carga de fuente
    font.loadFromFile("assets//Lost in Wild.ttf");

    //Carga de fondo
    texBackground.loadFromFile("assets//cloudy.png");

    //Carga botones
    texButton.loadFromFile("assets//boton_madera.png");
    texBorder.loadFromFile("assets//cursorTarget.png");
}

void MenuState::initVisualsMenu()
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
    sBorder.setTexture(texBorder); //setpos en update

    //Set botones (con su texture)
    bJugar.setSize(Vector2f(200.f, 60.f));
    bJugar.setPosition(90.f, 195.f);
    bJugar.setTexture(&texButton);

    bOpciones.setSize(Vector2f(200.f, 60.f));
    bOpciones.setPosition(90.f, 295.f);
    bOpciones.setTexture(&texButton);

    bSalir.setSize(Vector2f(200.f, 60.f));
    bSalir.setPosition(90.f, 395.f);
    bSalir.setTexture(&texButton);

}

void MenuState::initTextsMenu()
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

    //Textos sin boton (Titulo)
    tTitle.setFont(font);
    tTitle.setCharacterSize(50);
    tTitle.setString("Shapey's Tales");
    tTitle.setOutlineColor(Color::Black);
    tTitle.setOutlineThickness(5);
    tTitle.setPosition(game.getWindow().getSize().x / 4, 50);

    //Textos con boton
    tJugar.setFont(font);
    tJugar.setCharacterSize(20);
    tJugar.setString("Jugar");
    tJugar.setOutlineColor(Color::Black);
    tJugar.setOutlineThickness(5);

    tOpciones.setFont(font);
    tOpciones.setCharacterSize(20);
    tOpciones.setString("Opciones");
    tOpciones.setOutlineColor(Color::Black);
    tOpciones.setOutlineThickness(5);

    tSalir.setFont(font);
    tSalir.setCharacterSize(20);
    tSalir.setString("Salir");
    tSalir.setOutlineColor(Color::Black);
    tSalir.setOutlineThickness(5);

    //Center texts
    FloatRect textBounds = tJugar.getLocalBounds();

    tJugar.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    tJugar.setPosition(bJugar.getPosition() + bJugar.getSize() / 2.f);

    textBounds = tOpciones.getLocalBounds();
    tOpciones.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    tOpciones.setPosition(bOpciones.getPosition() + bOpciones.getSize() / 2.f);

    textBounds = tSalir.getLocalBounds();
    tSalir.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    tSalir.setPosition(bSalir.getPosition() + bSalir.getSize() / 2.f);
}

MenuState::MenuState(Game& g) : State(g)
{
    loadAssetsMenu();
    initVisualsMenu();
    initTextsMenu();

    bLevel = 0;
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Game Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void MenuState::handleEvent(Event& event) //Eventos propios del menu
{

    switch (event.type) //Switch general
    { 
    case Event::KeyPressed: //Si es de tipo teclado, entra a este switch 
        switch (event.key.code) {

        case Keyboard::Up:
            if (bLevel > 1) {
                bLevel -= 1;
            }
            else {
                bLevel = 3;
            }
            break;
        case Keyboard::W:
            if (bLevel > 1) {
                bLevel -= 1;
            }
            else {
                bLevel = 3;
            }
            break;

        case Keyboard::Down:
            if (bLevel < 3) {
                bLevel += 1;
            }
            else {
                bLevel = 1;
            }
            break;

        case Keyboard::S:
            if (bLevel < 3) {
                bLevel += 1;
            }
            else {
                bLevel = 1;
            }
            break;

        case Keyboard::Enter: //Chequeo que boton esta seleccionado
            switch (bLevel) {
            case 1:
                game.pushState(make_unique<LevelState>(game));
                break;
            case 2:
                game.pushState(make_unique<OptionState>(game));
                break;
            case 3:
                wnd.close();
                break;
            }
            break;

        case Keyboard::Escape:
            wnd.close();
            break;

        default:
            break;
        }
        break;

    case Event::MouseButtonPressed: //Si se clickea
        if (event.mouseButton.button == Mouse::Left) { //Si es el izq

            //Chequeo si se clickeó sobre alguno de los botones
            if (bJugar.getGlobalBounds().contains(mousePos)) { //Entro a la partida
                game.pushState(make_unique<LevelState>(game));
            }

            if (bOpciones.getGlobalBounds().contains(mousePos)) { //Entro a las opciones
                game.pushState(make_unique<OptionState>(game));
            }

            if (bSalir.getGlobalBounds().contains(mousePos)) { //Cierro el juego
                wnd.close();
            }
        }
        break;

    default:
        break;
    }
}

void MenuState::update() //Update propio del menu
{
    mousePos = wnd.mapPixelToCoords(Mouse::getPosition(wnd));

    if (bJugar.getGlobalBounds().contains(mousePos))
        bLevel = 1;

    if (bOpciones.getGlobalBounds().contains(mousePos))
        bLevel = 2;

    if (bSalir.getGlobalBounds().contains(mousePos)) 
        bLevel = 3;

    switch (bLevel) {
    case 1:
        sBorder.setPosition(bJugar.getPosition().x, bJugar.getPosition().y);
        break;
    case 2:
        sBorder.setPosition(bOpciones.getPosition().x, bOpciones.getPosition().y);
        break;
    case 3:
        sBorder.setPosition(bSalir.getPosition().x, bSalir.getPosition().y);
        break;
    }
}

void MenuState::render() //Render propio del menu
{

    //Set View Default
    wnd.setView(wnd.getDefaultView());
    
    //Dibujo
    wnd.draw(sBackground);

    wnd.draw(bJugar);
    wnd.draw(bOpciones);
    wnd.draw(bSalir);
    //Borde de los botones
    if (bLevel != 0) {
        wnd.draw(sBorder);
    }

    wnd.draw(tTitle);
    wnd.draw(tJugar);
    wnd.draw(tOpciones);
    wnd.draw(tSalir);
}
