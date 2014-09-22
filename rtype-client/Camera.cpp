#include	"Camera.h"
#include	"Graphic.h"

Camera::Camera()
{
	this->_x = 0;
	this->_y = 0;
}

Camera::~Camera()
{
}

void	Camera::update(sf::RenderWindow *Window)
{
	this->_x += 25 * Window->GetFrameTime();
	this->_cameraPos.SetFromRect(sf::FloatRect(this->_x, this->_y, this->_x + WIDTH, this->_y + HEIGHT));
}

void	Camera::draw(sf::RenderWindow *Window)
{
	Window->SetView(this->_cameraPos);
}

void	Camera::reset()
{
	this->_x = 0;
	this->_y = 0;
}

void	Camera::setPosX(float x)
{
	this->_x = x;
}

void	Camera::setPosY(float y)
{
	this->_y = y;
}

float	Camera::getXPos() const
{
	return this->_x;
}

float	Camera::getYPos() const
{
	return this->_y;
}