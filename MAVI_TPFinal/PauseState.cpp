#include "PauseState.h"

using namespace sf;
using namespace std;

#include "Game.h"
#include "GameState.h" 
#include "OptionState.h"
#include "MenuState.h"

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Inits & Constructors <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void PauseState::loadAssetsPause()
{
	//Carga de fuente
	font.loadFromFile("assets//Lost in Wild.ttf");

	//Carga de fondo
	texBackground.loadFromFile("assets//cloudy.png");

	//Carga botones
	texButton.loadFromFile("assets//boton_madera.png");
	texBorder.loadFromFile("assets//cursorTarget.png");
}

void PauseState::initVisualsPause()
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
	bContinuar.setSize(Vector2f(200.f, 60.f));
	bContinuar.setPosition(90.f, 195.f);
	bContinuar.setTexture(&texButton);

	bOpciones.setSize(Vector2f(200.f, 60.f));
	bOpciones.setPosition(90.f, 295.f);
	bOpciones.setTexture(&texButton);

	bMenu.setSize(Vector2f(200.f, 60.f));
	bMenu.setPosition(90.f, 395.f);
	bMenu.setTexture(&texButton);

	bSalir.setSize(Vector2f(200.f, 60.f));
	bSalir.setPosition(90.f, 495.f);
	bSalir.setTexture(&texButton);
}

void PauseState::initTextsPause()
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

   //Textos sin boton
	tPausa.setFont(font);
	tPausa.setCharacterSize(30);
	tPausa.setString("Juego Pausado");
	tPausa.setOutlineColor(Color::Black);
	tPausa.setOutlineThickness(5);
	tPausa.setPosition(game.getWindow().getSize().x / 4, 50);
	
	//Textos con boton
	tContinuar.setFont(font);
	tContinuar.setCharacterSize(20);
	tContinuar.setString("Jugar");
	tContinuar.setOutlineColor(Color::Black);
	tContinuar.setOutlineThickness(5);

	tOpciones.setFont(font);
	tOpciones.setCharacterSize(20);
	tOpciones.setString("Opciones");
	tOpciones.setOutlineColor(Color::Black);
	tOpciones.setOutlineThickness(5);

	tMenu.setFont(font);
	tMenu.setCharacterSize(20);
	tMenu.setString("Menu");
	tMenu.setOutlineColor(Color::Black);
	tMenu.setOutlineThickness(5);

	tSalir.setFont(font);
	tSalir.setCharacterSize(20);
	tSalir.setString("Salir");
	tSalir.setOutlineColor(Color::Black);
	tSalir.setOutlineThickness(5);

	//Center texts
	FloatRect textBounds = tContinuar.getLocalBounds();

	tContinuar.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tContinuar.setPosition(bContinuar.getPosition() + bContinuar.getSize() / 2.f);

	textBounds = tOpciones.getLocalBounds();
	tOpciones.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tOpciones.setPosition(bOpciones.getPosition() + bOpciones.getSize() / 2.f);

	textBounds = tMenu.getLocalBounds();
	tMenu.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tMenu.setPosition(bMenu.getPosition() + bMenu.getSize() / 2.f);

	textBounds = tSalir.getLocalBounds();
	tSalir.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tSalir.setPosition(bSalir.getPosition() + bSalir.getSize() / 2.f);
}

PauseState::PauseState(Game& g) : State(g)
{
	loadAssetsPause();
	initVisualsPause();
	initTextsPause();

	bLevel = 0;
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Game Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void PauseState::handleEvent(sf::Event& event)
{

	switch (event.type) {
	case Event::Closed:
		wnd.close();
		break;

	case Event::Resized:
		//cam.updateViewport        ESTE HAY QUE TERMINARLO CHEM PERO EN OTRO MOMENTO CHEMMMMMMM
		break;

	case Event::KeyPressed: //Si es evento de teclado
		switch (event.key.code) {
		case Keyboard::Escape:
			game.popState();
			break;

		case Keyboard::Up:
			if (bLevel > 1) {
				bLevel -= 1;
			}
			else {
				bLevel = 4;
			}
			break;
		case Keyboard::W:
			if (bLevel > 1) {
				bLevel -= 1;
			}
			else {
				bLevel = 4;
			}
			break;

		case Keyboard::Down:
			if (bLevel < 4) {
				bLevel += 1;
			}
			else {
				bLevel = 1;
			}
			break;

		case Keyboard::S:
			if (bLevel < 4) {
				bLevel += 1;
			}
			else {
				bLevel = 1;
			}
			break;

		case Keyboard::Enter: //Chequeo que boton esta seleccionado
			switch (bLevel) {
			case 1:
				game.popState();
				break;
			case 2:
				game.pushState(make_unique<OptionState>(game));
				break;
			case 3:
				game.pushState(make_unique<MenuState>(game));
				break;
			case 4:
				wnd.close();
				break;
			}
			break;

		default:
			break;
		}
		break;

	case Event::MouseButtonPressed: //Si se clickea
		if (event.mouseButton.button == Mouse::Left) { //Si es el izq

			//Chequeo si se clickeó sobre alguno de los botones
			if (bContinuar.getGlobalBounds().contains(mousePos)) { //Vuelvo a la partida
				game.popState();
			}

			if (bOpciones.getGlobalBounds().contains(mousePos)) { //Entro a las opciones
				game.pushState(make_unique<OptionState>(game));
			}

			if (bMenu.getGlobalBounds().contains(mousePos)) { //Al menu             
				game.pushState(make_unique<MenuState>(game));
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

void PauseState::update()
{
	mousePos = wnd.mapPixelToCoords(Mouse::getPosition(wnd));

	if (bContinuar.getGlobalBounds().contains(mousePos))
		bLevel = 1;

	if (bOpciones.getGlobalBounds().contains(mousePos))
		bLevel = 2;

	if (bMenu.getGlobalBounds().contains(mousePos))
		bLevel = 3;

	if (bSalir.getGlobalBounds().contains(mousePos))
		bLevel = 4;

	switch (bLevel) {
	case 1:
		sBorder.setPosition(bContinuar.getPosition().x, bContinuar.getPosition().y);
		break;
	case 2:
		sBorder.setPosition(bOpciones.getPosition().x, bOpciones.getPosition().y);
		break;
	case 3:
		sBorder.setPosition(bMenu.getPosition().x, bMenu.getPosition().y);
		break;
	case 4:
		sBorder.setPosition(bSalir.getPosition().x, bSalir.getPosition().y);
		break;
	}
}

void PauseState::render()
{
	//Set View Default
	wnd.setView(wnd.getDefaultView());

	//Dibujo
	wnd.draw(sBackground);

	wnd.draw(bContinuar);
	wnd.draw(bOpciones);
	wnd.draw(bMenu);
	wnd.draw(bSalir);
	//Borde de los botones
	if (bLevel != 0) {
		wnd.draw(sBorder);
	}

	wnd.draw(tPausa);
	wnd.draw(tContinuar);
	wnd.draw(tOpciones);
	wnd.draw(tMenu);
	wnd.draw(tSalir);
}
