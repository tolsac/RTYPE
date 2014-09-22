#include	"Scroller.h"
#include	"Graphic.h"

Scroller::Scroller()
{
}

Scroller::Scroller(sf::RenderWindow *Window)
{
	this->_window = Window;
}

Scroller::~Scroller()
{
}

void	Scroller::init()
{
	//TODO: Check si sf::Clolor::Black fonctionne ailleurs.
	// Sinon, le remplacer par sf::Color(0,0,0).
	if (!bgImage1.LoadFromFile("assets/sprites/bg.jpg"))
		this->_bgSprite1.SetColor(sf::Color::Black);
	this->_bgSprite1.SetImage(bgImage1);
	this->_bgSprite1.Resize(WIDTH, HEIGHT);
	if (!bgImage2.LoadFromFile("assets/sprites/bg2.jpg"))
		this->_bgSprite2.SetColor(sf::Color::Black);
	this->_bgSprite2.SetImage(bgImage2);
	this->_bgSprite2.Resize(WIDTH, HEIGHT);
	this->_bgSprite2.Move(WIDTH, 0);

}

void	Scroller::Draw()
{
	this->_cam.update(this->_window);
	if (this->_cam.getXPos() >= this->_bgSprite1.GetPosition().x + WIDTH)
		this->_bgSprite1.Move(2*WIDTH, 0);
	if (this->_cam.getXPos() >= this->_bgSprite2.GetPosition().x + WIDTH)
		this->_bgSprite2.Move(2*WIDTH, 0);
	this->_cam.draw(this->_window);
	this->_window->Draw(this->_bgSprite1);
	this->_window->Draw(this->_bgSprite2);
}

void	Scroller::setWindow(sf::RenderWindow *Window)
{
	this->_window = Window;
}

void	Scroller::reset()
{
	this->_cam.reset();
	this->_bgSprite1.SetPosition(0, 0);
	this->_bgSprite2.SetPosition(WIDTH, 0);
}