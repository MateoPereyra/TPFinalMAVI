#include "GameState.h"

using namespace sf;
using namespace std;

#include "Game.h"
#include "OptionState.h"
#include "PauseState.h"
#include "LevelState.h"
#include "MenuState.h"

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Inits & Constructors <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void GameState::loadAssetsGame(int level)
{
	//Carga de fuente
	font.loadFromFile("assets//Lost in Wild.ttf");

	switch (level) {
	case 1:
		texBackground.loadFromFile("assets//cloudy.png");
		break;
	case 2:
		texBackground.loadFromFile("assets//daySky.png");
		break;
	case 3:
		texBackground.loadFromFile("assets//nightSky.png");
		break;
	}

	//Grounds
	texGrass.loadFromFile("assets//GrassMid.png");
	texDirt.loadFromFile("assets//Dirt.png");

	//Otros
	texFlag.loadFromFile("assets//bandera.png");
	texCoin.loadFromFile("assets//coin.png");

}

void GameState::initVisualsGame()
{
	/*
		1. Fondo
		2. Sprite del borde
		3. Botones (set + texture)

		4. abajo del todo, centrar los botones en el overlay
	*/

	texBackground.setRepeated(true);
	sBackground.setTexture(texBackground);

	sBackground.setOrigin(texBackground.getSize().x / 2.f, texBackground.getSize().y / 2.f); //Origen en 0,0
	sBackground.setScale(1.f, 1.5f);
	sBackground.setTextureRect(IntRect(0, 0, 5000, 5000));

	//Set botones (con texture)
	bReintentar.setSize(Vector2f(200.f, 60.f));
	bReintentar.setPosition(530.f, 250.f);

	bNiveles.setSize(Vector2f(200.f, 60.f));
	bNiveles.setPosition(530.f, 350.f);

	bSigN.setSize(Vector2f(200.f, 60.f));
	bSigN.setPosition(530.f, 350.f);

	bMenu.setSize(Vector2f(200.f, 60.f));
	bMenu.setPosition(530.f, 450.f);

	//Otros
	sFlag.setTexture(texFlag);
	sFlag.setScale(128.0f / 1024.0f, 128.0f / 1024.0f);

	sHUDCoin.setTexture(texCoin); //Coin del hud
	sHUDCoin.setScale(64.0f / 1024.0f, 64.0f / 1024.0f);
	sHUDCoin.setPosition(390.f, 25.0f);

	//Para el game over>>>>>>>>>>>>>>>>>>>>>>>>>>>>><

	//Fondo semitransparente
	overlay.setSize(Vector2f(wnd.getSize()));
	overlay.setFillColor(Color(0, 0, 0, 150));

	//Cuadro/panel central
	panel.setSize(Vector2f(600.f, 450.f));
	panel.setFillColor(Color(30, 30, 30, 230));
	panel.setOutlineColor(Color::White);
	panel.setOutlineThickness(2.f);
	panel.setOrigin(panel.getSize().x / 2.f, panel.getSize().y / 2.f);
	panel.setPosition(wnd.getSize().x / 2.f, wnd.getSize().y / 2.f);

}

void GameState::initTextsGame()
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
	tDerrota.setFont(font);
	tDerrota.setCharacterSize(35);
	tDerrota.setString("Has perdido!");
	tDerrota.setOutlineColor(Color::White);
	tDerrota.setFillColor(Color::Black);
	tDerrota.setOutlineThickness(2.5);
	tDerrota.setPosition(panel.getPosition().x - 125.f, 180.f);

	tVictoria.setFont(font);
	tVictoria.setCharacterSize(35);
	tVictoria.setString("Has ganado!");
	tVictoria.setOutlineColor(Color::White);
	tVictoria.setFillColor(Color::Black);
	tVictoria.setOutlineThickness(2.5);
	tVictoria.setPosition(panel.getPosition().x - 125.f, 180.f);

	tTiempo.setFont(font);
	tTiempo.setCharacterSize(15);
	tTiempo.setOutlineColor(Color::Black);
	tTiempo.setOutlineThickness(2.5);
	tTiempo.setPosition(300.f, 50.f);

	tMonedas.setFont(font);
	tMonedas.setCharacterSize(15);
	tMonedas.setString(": X" + to_string(monedas));
	tMonedas.setOutlineColor(Color::Black);
	tMonedas.setOutlineThickness(2.5);
	tMonedas.setPosition(450.f, 50);

	//Textos con boton
	tReintentar.setFont(font);
	tReintentar.setCharacterSize(20);
	tReintentar.setString("Reintentar");
	tReintentar.setOutlineColor(Color::Black);
	tReintentar.setOutlineThickness(5);

	tNiveles.setFont(font);
	tNiveles.setCharacterSize(20);
	tNiveles.setString("Niveles");
	tNiveles.setOutlineColor(Color::Black);
	tNiveles.setOutlineThickness(5);

	tSigN.setFont(font);
	tSigN.setCharacterSize(20);
	tSigN.setString("Siguiente Nivel");
	tSigN.setOutlineColor(Color::Black);
	tSigN.setOutlineThickness(5);

	tMenu.setFont(font);
	tMenu.setCharacterSize(20);
	tMenu.setString("Menu");
	tMenu.setOutlineColor(Color::Black);
	tMenu.setOutlineThickness(5);

	//Centro textos en botones
	FloatRect textBounds = tReintentar.getLocalBounds();

	tReintentar.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tReintentar.setPosition(bReintentar.getPosition() + bReintentar.getSize() / 2.f);

	textBounds = tNiveles.getLocalBounds();
	tNiveles.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tNiveles.setPosition(bNiveles.getPosition() + bNiveles.getSize() / 2.f);

	textBounds = tSigN.getLocalBounds();
	tSigN.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tSigN.setPosition(bSigN.getPosition() + bSigN.getSize() / 2.f);

	textBounds = tMenu.getLocalBounds();
	tMenu.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	tMenu.setPosition(bMenu.getPosition() + bMenu.getSize() / 2.f);
}

void GameState::loadLevel(int level) //Carga el nivel seleccionado
{
	switch (level) {
	case 1:
		this->loadLevel1();
		break;
	case 2:
		this->loadLevel2();
		break;
	case 3:
		this->loadLevel3();
		break;
	}
}

GameState::GameState(Game& g, int level) : State(g), level(level)
{
	this->loadAssetsGame(level);
	this->initVisualsGame(); 
	this->initTextsGame();
	this->loadLevel(level);

	dt = clock.restart().asSeconds(); //No se si va aca, vere depue
	gameDefeat = false;
	gameWin = false;
	pasTime = 0.f;
	monedas = 0;
}

void GameState::onEnter()
{
	clock.restart(); //evito un dt grande en pausa
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Game Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void GameState::handleEvent(Event& event) //eventos propios de la partida
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
			game.pushState(make_unique<PauseState>(game));
			break;

		default:
			break;
		}
		break;
	case Event::MouseButtonPressed: //Si se clickea
		if (event.mouseButton.button == Mouse::Left) { //Si es el izq

			if (gameDefeat) { //Si esta la pantalla de derrota
				//Chequeo si se clickeó sobre alguno de los botones
				if (bReintentar.getGlobalBounds().contains(mousePos)) { //reinicio el lvl
					game.replaceState(make_unique<GameState>(game, level));
				}

				if (bNiveles.getGlobalBounds().contains(mousePos)) { //Entro a los lvls
					//game.pushState(make_unique<LevelState>(game));
					game.popState();
				}

				if (bMenu.getGlobalBounds().contains(mousePos)) { //Voy al menu
					game.pushState(make_unique<MenuState>(game));
				}
			}

			if (gameWin) { //Si esta la pantalla de victoria
				//Chequeo si se clickeó sobre alguno de los botones
				if (bReintentar.getGlobalBounds().contains(mousePos)) { //reinicio el lvl
					game.replaceState(make_unique<GameState>(game, level));
				}

				if (bSigN.getGlobalBounds().contains(mousePos)) { //Siguiente lvl           CAMBIAR A REPLACE ALGUNOS DE ESTOS
					game.replaceState(make_unique<GameState>(game, level+1));
				}

				if (bMenu.getGlobalBounds().contains(mousePos)) { //Voy al menu
					game.pushState(make_unique<MenuState>(game));
				}
			}
		}
		break;
	default:
		break;
	}
}

void GameState::update() //Update propio
{
	mousePos = wnd.mapPixelToCoords(Mouse::getPosition(wnd));

	pasTime += dt; //guarda el tiempo
	if (isGameOver()) return; //si pierdo o gano, salgo
	dt = clock.restart().asSeconds(); //delta time para el mov

	//Char
	shapey.update(dt); //Movimiento de shapey
	cam.centerCam(shapey.getPos());

	//Tiempo
	int mins = (int)pasTime / 60;
	int sec = (int)pasTime % 60;

	string seg = to_string(sec);
	if (sec < 10) seg = "0" + seg; // agrega el 0 delante si hace falta

	tTiempo.setString(to_string(mins) + ":" + seg);

	//Deteccion de colision con terreno
	for (auto& t : grounds) {
		FloatRect sB = shapey.getBounds();
		FloatRect tB = t.getBounds();

		if (sB.intersects(tB)) {
			float overlapX = min(sB.left + sB.width, tB.left + tB.width) - max(sB.left, tB.left);
			float overlapY = min(sB.top + sB.height, tB.top + tB.height) - max(sB.top, tB.top);

			if (overlapY <= overlapX) { //Colisión vertical
				if (shapey.getVel().y >= 0.f) { //Cayendo
					shapey.setPos(sB.left, t.getTop() - sB.height);
					shapey.stopY();
					shapey.setOnGround(true);
				}
				else { //Saltando
					shapey.setPos(sB.left, t.getTop() + tB.height);
					shapey.stopY();
				}
			}
			else {
				bool goingRight = shapey.getVel().x > 0.f ||
					(shapey.getDashing() && shapey.getDir() > 0);
				bool goingLeft = shapey.getVel().x < 0.f ||
					(shapey.getDashing() && shapey.getDir() < 0);

				if (goingRight) {
					shapey.setPos(t.getLeft() - sB.width, sB.top);
				}
				else if (goingLeft) {
					shapey.setPos(t.getLeft() + tB.width, sB.top);
				}
				shapey.stopX();
				shapey.setDashing(false);
			}
		}
	}

	//Colision con enemigos, for al reves
	for (int i = enemies.size() - 1; i >= 0; i--) {
		enemies[i]->update(dt);

		if (shapey.getBounds().intersects(enemies[i]->getBounds())) {
			if (shapey.getBlockFall() && shapey.getVel().y != 0.f) {
				enemies.erase(enemies.begin() + i); //seguro iterando al revés
			} else {
				gameDefeat = true;
			}
		}
	}

	//Con obstaculos
	for (auto& s : spears) {
		if (s->getBounds().intersects(shapey.getBounds()))
			gameDefeat = true;
	}

	//Con otros
	//con bandera
	if (shapey.getBounds().intersects(sFlag.getGlobalBounds())) {
		gameWin = true;
	}

	//Con monedas
	for (int i = sCoin.size() - 1; i >= 0; i--) { 
		if (shapey.getBounds().intersects(sCoin[i].getGlobalBounds())) {
			monedas++;
			sCoin.erase(sCoin.begin() + i);
			tMonedas.setString("X" + to_string(monedas));
		}
	}
}

void GameState::render() //render propio
{

	//Set camara
	cam.setCamera(wnd);

	//Dibujo
	wnd.draw(sBackground);

	for (auto& t : grounds) {
		t.render(wnd);
	}
	for (auto& m : sCoin) {
		wnd.draw(m);
	}
	wnd.draw(sFlag);
	for (auto& e : enemies) {
		e->render(wnd);
	}
	for (auto& s : spears) {
		s->render(wnd);
	}
	shapey.render(wnd);

	//HUD
	wnd.setView(wnd.getDefaultView());
	wnd.draw(tTiempo);
	wnd.draw(sHUDCoin);
	wnd.draw(tMonedas);

	//Render de final
	if (gameDefeat) renderDefeat();
	else if (gameWin)  renderWin();

}

void GameState::renderDefeat()
{
	wnd.setView(wnd.getDefaultView());
	wnd.draw(overlay);
	wnd.draw(panel);
	
	wnd.draw(tDerrota);
	wnd.draw(tReintentar);
	wnd.draw(tNiveles);
	wnd.draw(tMenu);
}

void GameState::renderWin()
{
	wnd.setView(wnd.getDefaultView());
	wnd.draw(overlay);
	wnd.draw(panel);

	wnd.draw(tVictoria);
	wnd.draw(tReintentar);
	wnd.draw(tSigN);
	wnd.draw(tMenu);
}

/*
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  Niveles  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

void GameState::loadLevel1()
{
	enemies.clear();
	grounds.clear();
	sCoin.clear();

	//Posicion de Shapey
	shapey.setPos(0, 0);

	//Terreno
	grounds.push_back(Terrain(-125.f, -450.f, 50.f, 450.f, texGrass, texDirt));
	grounds.push_back(Terrain(-125.f, 0.f, 675.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(-25.f, -125.f, 150.f, 25.f, texGrass, texDirt));
	grounds.push_back(Terrain(350.f, -225.f, 100.f, 25.f, texGrass, texDirt));
	grounds.push_back(Terrain(450.f, -75.f, 250.f, 125.f, texGrass, texDirt));
	grounds.push_back(Terrain(700.f, 0.f, 50.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(750.f, 50.f, 50.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(800.f, 100.f, 250.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(900.f, -75.f, 150.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(1050.f, -150.f, 100.f, 250.f, texGrass, texDirt));
	grounds.push_back(Terrain(1150.f, -150.f, 900.f, 100.f, texGrass, texDirt));
	grounds.push_back(Terrain(1250.f, -275.f, 100.f, 25.f, texGrass, texDirt));
	grounds.push_back(Terrain(1550.f, -275.f, 100.f, 25.f, texGrass, texDirt));
	grounds.push_back(Terrain(2050.f, -200.f, 150.f, 150.f, texGrass, texDirt));
	grounds.push_back(Terrain(2200.f, -150.f, 350.f, 100.f, texGrass, texDirt));
	grounds.push_back(Terrain(2350.f, -325.f, 150.f, 25.f, texGrass, texDirt));
	grounds.push_back(Terrain(2500.f, -325.f, 50.f, 250.f, texGrass, texDirt));
	grounds.push_back(Terrain(2500.f, -425.f, 100.f, 100.f, texGrass, texDirt));
	grounds.push_back(Terrain(2600.f, -525.f, 100.f, 100.f, texGrass, texDirt));
	grounds.push_back(Terrain(2700.f, -825.f, 50.f, 400.f, texGrass, texDirt));
	grounds.push_back(Terrain(2100.f, -625.f, 300.f, 25.f, texGrass, texDirt));
	grounds.push_back(Terrain(1600.f, -625.f, 150.f, 25.f, texGrass, texDirt));

	//Otros
	sFlag.setPosition(1625.f, -625.f - 128.f); //bandera
	//Ajusto el bounds
	Vector2f pos = sFlag.getPosition();
	Vector2f scale = sFlag.getScale();
	float offsetX = 80.f * scale.x;
	float offsetY = 30.f * scale.y;
	float w = 900.f * scale.x;
	float h = 950.f * scale.y;
	flagBounds = FloatRect(pos.x + offsetX, pos.y + offsetY, w, h);
	 
	Sprite m1, m2, m3; //monedas
	m1.setTexture(texCoin);
	m1.setScale(64.0f / 1024.0f, 64.0f / 1024.0f);
	m2.setTexture(texCoin);
	m2.setScale(64.0f / 1024.0f, 64.0f / 1024.0f);
	m3.setTexture(texCoin);
	m3.setScale(64.0f / 1024.0f, 64.0f / 1024.0f);
	m1.setPosition(375.f, -275.f);
	m2.setPosition(1575.f, -325.f);
	m3.setPosition(1625.f, -600.f);
	sCoin.push_back(m1);
	sCoin.push_back(m2);
	sCoin.push_back(m3);

	//Enemigos
	enemies.push_back(make_unique<BaseEnemy>(1400.f, -200.f, 200.f));
	enemies.push_back(make_unique<BaseEnemy>(1600.f, -200.f, 200.f));


}

void GameState::loadLevel2()
{
	enemies.clear();
	grounds.clear();
	spears.clear();
	sCoin.clear();

	//Posicion de Shapey
	shapey.setPos(0, 0);

	//Terreno
	grounds.push_back(Terrain(-400.f, -450.f, 50.f, 500.f, texGrass, texDirt));
	grounds.push_back(Terrain(-400.f, 50.f, 1600.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(800.f, -75.f, 200.f, 25.f, texGrass, texDirt));
	grounds.push_back(Terrain(1200.f, -200.f, 300.f, 300.f, texGrass, texDirt));
	grounds.push_back(Terrain(1500.f, -150.f, 1200.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(1700.f, -200.f, 100.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(2000.f, -200.f, 50.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(2200.f, -200.f, 50.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(2700.f, -250.f, 50.f, 150.f, texGrass, texDirt));
	grounds.push_back(Terrain(2750.f, -250.f, 1800.f, 50.f, texGrass, texDirt));
	grounds.push_back(Terrain(3000.f, -325.f, 50, 75.f, texGrass, texDirt));
	grounds.push_back(Terrain(3300.f, -325.f, 50, 75.f, texGrass, texDirt));
	grounds.push_back(Terrain(3700.f, -325.f, 50, 75.f, texGrass, texDirt));
	grounds.push_back(Terrain(4550.f, -650, 50.f, 450.f, texGrass, texDirt));

	//Otros
	sFlag.setPosition(4250.f, -250.f - 128.f); //bandera
	//Ajusto el bounds
	Vector2f pos = sFlag.getPosition();
	Vector2f scale = sFlag.getScale();
	float offsetX = 80.f * scale.x;
	float offsetY = 70.f * scale.y;
	float w = 900.f * scale.x;
	float h = 850.f * scale.y;
	flagBounds = FloatRect(pos.x + offsetX, pos.y + offsetY, w, h);

	Sprite m1, m2, m3; //monedas
	m1.setTexture(texCoin);
	m1.setScale(64.0f / 1024.0f, 64.0f / 1024.0f);
	m2.setTexture(texCoin);
	m2.setScale(64.0f / 1024.0f, 64.0f / 1024.0f);
	m3.setTexture(texCoin);
	m3.setScale(64.0f / 1024.0f, 64.0f / 1024.0f);
	m1.setPosition(200.f, -250.f);
	m2.setPosition(2200.f, -500.f);
	m3.setPosition(4250.f, -475.f);
	sCoin.push_back(m1);
	sCoin.push_back(m2);
	sCoin.push_back(m3);

	spears.push_back(make_unique<Spear>(1475.f, -200.f));
	spears.push_back(make_unique<Spear>(1525.f, -200.f));
	spears.push_back(make_unique<Spear>(1575.f, -200.f));
	spears.push_back(make_unique<Spear>(1625.f, -200.f));//
	spears.push_back(make_unique<Spear>(1775.f, -200.f));
	spears.push_back(make_unique<Spear>(1825.f, -200.f));
	spears.push_back(make_unique<Spear>(1875.f, -200.f));
	spears.push_back(make_unique<Spear>(1925.f, -200.f));//
	spears.push_back(make_unique<Spear>(2025.f, -200.f));
	spears.push_back(make_unique<Spear>(2075.f, -200.f));
	spears.push_back(make_unique<Spear>(2125.f, -200.f));//
	spears.push_back(make_unique<Spear>(2225.f, -200.f));
	spears.push_back(make_unique<Spear>(2275.f, -200.f));
	spears.push_back(make_unique<Spear>(2325.f, -200.f));
	spears.push_back(make_unique<Spear>(2375.f, -200.f));
	spears.push_back(make_unique<Spear>(2425.f, -200.f));
	spears.push_back(make_unique<Spear>(2475.f, -200.f));
	spears.push_back(make_unique<Spear>(2525.f, -200.f));
	spears.push_back(make_unique<Spear>(2575.f, -200.f));
	spears.push_back(make_unique<Spear>(2625.f, -200.f));//

	//Enemigos
	//enemies.push_back(make_unique<BaseEnemy>(920.f, 0.f, 700.f));
	//enemies.push_back(make_unique<BaseEnemy>(620.f, 0.f, 700.f));
	//enemies.push_back(make_unique<BaseEnemy>(450.f, -325.f, 450.f));
}

void GameState::loadLevel3()
{
}

bool GameState::isGameOver() const //Para terminar el nivel
{
	return gameDefeat || gameWin;
}
