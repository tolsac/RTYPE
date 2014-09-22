#ifndef		__CAMERA_H__
#define		__CAMERA_H__

#include <SFML/Graphics.hpp>
//#include	"Graphic.h"

class	Camera
{
public:
	Camera();
	~Camera();
	void update(sf::RenderWindow *Window);
	void draw(sf::RenderWindow *Window);
	void reset();
	void setPosX(float x);
	void setPosY(float y);
	float getXPos() const;
	float getYPos() const;
private:
	sf::View	_cameraPos;
	float		_x;
	float		_y;
};

#endif		//__CAMERA_H__
