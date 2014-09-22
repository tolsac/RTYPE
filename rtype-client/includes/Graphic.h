#ifndef __GRAPHICS__
#define __GRAPHICS__

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ScreenManager.h>
#include <Singleton.hpp>
#include "ICallback.hh"

#define WIDTH	800
#define HEIGHT	600

class Graphics : public ICallback
{
private:
  sf::RenderWindow		*window;
  ScreenManager			*sManager;

public:
  Graphics();
  ~Graphics();

  void setWindow(sf::RenderWindow*);
  void init();
  void run();
  void operator()();
  
  ScreenManager		*getScreenManager();
};

#endif
