#ifndef __GAME_H__
#define __GAME_H__

#include "EntityManager.h"
#include "FileManager.h"
#include "IScreen.h"
#include "SoundManager.h"

class Game : public IScreen
{
public:
  Game();
  ~Game();

  bool			LoadRessources();
  bool			LoadRessources(SoundManager& soundmanager);
  virtual void	init();
  virtual void	init(SoundManager& _soundmanager);
  virtual void	Draw(sf::RenderWindow *Window);
  virtual void	Clear();
  virtual void	updateEvent(sf::Event&);
  virtual void	updateEvent(sf::Event&, SoundManager&);

  EntityManager &						getEntityManager();
  std::map<int, sf::Image *> &	getRessources();
private:
  EntityManager myEntities;
  std::map<int, sf::Image *> myRessources;
  std::map<int, sf::SoundBuffer*> mySounds;
  std::vector<std::vector<std::string> > attributes;
  std::vector<std::vector<std::string> > contents;
  FileManager file;
  sf::Sprite sprite;
  sf::Image  image;
};

#endif /*__GAME_H__*/
