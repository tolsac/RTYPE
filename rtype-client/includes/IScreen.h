#ifndef __ISCREEN_H__
#define __ISCREEN_H__

namespace sf
{
class Event;
};

class IScreen
{
public:
	virtual void init() = 0;
	virtual void Draw(sf::RenderWindow *Window) = 0;
	virtual void Clear() = 0;
	virtual void updateEvent(sf::Event &) = 0;
};

#endif /*__ISCREEN_H__*/
