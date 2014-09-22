#ifndef		__SCROLLER_H__
#define		__SCROLLER_H__

#include	"Camera.h"

class Camera;

class	Scroller
{
public:
	Scroller();
	Scroller(sf::RenderWindow *Window);
	~Scroller();
	void	init();
	void	Draw();
	void	setWindow(sf::RenderWindow *Window);
	void	reset();

private:
	sf::RenderWindow	*_window;
	Camera				_cam;
	sf::Sprite			_bgSprite1;
	sf::Sprite			_bgSprite2;
	sf::Image			bgImage1;
	sf::Image			bgImage2;
};

#endif		//__SCROLLER_H__