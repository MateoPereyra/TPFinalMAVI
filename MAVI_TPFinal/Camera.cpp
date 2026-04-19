#include "Camera.h"

using namespace sf;
using namespace std;

void Camera::initView()//inicio la camara
{
	mainView.setSize(640, 360);
	mainView.zoom(2.f);
}

Camera::Camera() 
{
	this->initView();
}

Camera::~Camera()
{
}

void Camera::centerCam(Vector2f targetPos) //A revisar, no me gusta como quedó la otra versión, ahora dejo la mas simple
{
	//Vector2f camCenter = this->mainView.getCenter(); //Primero consigo el centro del view

	////Calculo las distancias en X e Y entre Shapey y view
	//float dX = targetPos.x - camCenter.x;
	//float dY = targetPos.y - camCenter.y;

	////Chequeo si pasa el limite
	//if (dX > limitX)
	//	camCenter.x += 1.f;
	//else if (dX < -limitX)
	//	camCenter.x -= 1.f;

	//if (dY > limitY)
	//	camCenter.y += 1.f;
	//else if (dY < -limitY)
	//	camCenter.y -= 1.f;

	this->mainView.setCenter(targetPos);
}

void Camera::setCamera(RenderWindow& wnd) 
{
	wnd.setView(this->mainView);
}

