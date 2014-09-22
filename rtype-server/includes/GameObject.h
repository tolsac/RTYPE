#ifndef		__GAMEOBJECT_H__
#define		__GAMEOBJECT_H__

#include	<list>

#include	"Rect.hpp"
#include	"Vector.hpp"

#include	"ABehaviour.h"

class Game;
class ABehaviour;

class GameObject
{
public: //public methods

	GameObject();
	~GameObject();

	void		initialize();
	void		onMessageReceived(GameObject* from, const std::string& message);
	void		onCollision(GameObject* other);
	void		sendMessage(GameObject* target, const std::string& message);
	void		attachBehaviour(ABehaviour* behaviour);
	void		destroy();
	void		update();
	void		move(const epi::Vector2f& movement);

	template<typename T>
	T*	getAttachedBehaviour();

	bool					isAlive() const;
	int						getId() const;
	int						getTypeid() const;
	int						getRemainingLife() const;
	int						getMaximumLife() const;
	const epi::Vector2f&	getPosition() const;
	const epi::Rect4f&		getBoundingBox() const;
	GameObject*				getParent() const;
	Game*					getGame() const;
	const std::string&		getTag() const;

	void		setId(int id);
	void		setTypeId(int ptypeid);
	void		setRemainingLife(int premainingLife);
	void		setMaximumLife(int maximumLife);
	void		setParent(GameObject* parent);
	void		setPosition(const epi::Vector2f& pposition);
	void		setBoundingBox(const epi::Rect4f& boundingBox);
	void		setGame(Game* game);
	void		setAlive(bool alive);
	void		setTag(const std::string& tag);

protected: //protected attributes

	int				_id;
	int				_typeid;
	int				_remainingLife;
	int				_maxLife;
	epi::Vector2f	_position;
	epi::Rect4f		_boundingBox;
	GameObject*		_parent;
	bool			_alive;
	Game*			_game;
	std::string		_tag;

	std::list<ABehaviour*>	_behaviours;
};

template<typename T>
T*		GameObject::getAttachedBehaviour()
{
	for (auto it = this->_behaviours.begin(); it != this->_behaviours.end(); ++it)
	{
		T*	bh = dynamic_cast<T*>((*it));
		if (bh)
		{
			return bh;
		}
	}
	return 0;
}

#endif //__GAMEOBJECT_H__
