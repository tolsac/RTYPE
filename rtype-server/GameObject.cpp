#include	"GameObject.h"
#include	"Game.h"

#include	"Logger.h"

GameObject::GameObject()
	:	_id(0),
		_typeid(0),
		_remainingLife(1),
		_maxLife(1),
		_position(0, 0),
		_boundingBox(0, 0, 0, 0),
		_parent(0),
		_alive(false),
		_tag("")
{
}

GameObject::~GameObject()
{
	if (this->isAlive())
		this->destroy();
}

void		GameObject::initialize()
{
	this->_alive = true;
	for (auto it = this->_behaviours.begin(); it != this->_behaviours.end(); ++it)
	{
		(*it)->initialize();
	}
}

void		GameObject::destroy()
{
	for (auto it = this->_behaviours.begin(); it != this->_behaviours.end(); ++it)
	{
		(*it)->onDestroy();
	}
	this->_alive = false;
}

void		GameObject::update()
{
	if (!this->_alive)
	{
		return;
	}
	for (auto it = this->_behaviours.begin(); it != this->_behaviours.end(); ++it)
	{
		(*it)->update();
	}
	//something cool here
}

void		GameObject::move(const epi::Vector2f& movement)
{
	this->setPosition(this->getPosition() + movement);
	this->_game->refreshEntity(this, true);
}


bool		GameObject::isAlive() const
{
	return this->_alive;
}

int						GameObject::getId() const
{
	return this->_id;
}

int						GameObject::getTypeid() const
{
	return this->_typeid;
}

int						GameObject::getRemainingLife() const
{
	return this->_remainingLife;
}

int						GameObject::getMaximumLife() const
{
	return this->_maxLife;
}

const epi::Vector2f&	GameObject::getPosition() const
{
	return this->_position;
}

const epi::Rect4f&		GameObject::getBoundingBox() const
{
	return this->_boundingBox;
}

GameObject*				GameObject::getParent() const
{
	return this->_parent;
}

Game*					GameObject::getGame() const
{
	return this->_game;
}

const std::string&		GameObject::getTag() const
{
	return this->_tag;
}

void		GameObject::setId(int id)
{
	this->_id = id;
}

void		GameObject::setTypeId(int ptypeid)
{
	this->_typeid = ptypeid;
}

void		GameObject::setRemainingLife(int premainingLife)
{
	this->_remainingLife = premainingLife;
}

void		GameObject::setMaximumLife(int maximumLife)
{
	this->_maxLife = maximumLife;
}

void		GameObject::setParent(GameObject* parent)
{
	this->_parent = parent;
}

void		GameObject::setPosition(const epi::Vector2f& pposition)
{
	this->_position = pposition;
}

void		GameObject::setBoundingBox(const epi::Rect4f& boundingBox)
{
	this->_boundingBox = boundingBox;
}

void		GameObject::setGame(Game* game)
{
	this->_game = game;
}

void		GameObject::setAlive(bool alive)
{
	this->_alive = alive;
}

void		GameObject::setTag(const std::string& tag)
{
	this->_tag = tag;
}

void		GameObject::onMessageReceived(GameObject* from, const std::string& message)
{
	if (!this->_alive)
	{
		return;
	}

	for (auto it = this->_behaviours.begin(); it != this->_behaviours.end(); ++it)
	{
		(*it)->onMessage(from, message);
	}
}

void		GameObject::onCollision(GameObject* other)
{
	if (!this->_alive)
	{
		return;
	}
	for (auto it = this->_behaviours.begin(); it != this->_behaviours.end(); ++it)
	{
		(*it)->onCollision(other);
	}
}

void		GameObject::sendMessage(GameObject* target, const std::string& message)
{
	if (!this->_alive)
	{
		return;
	}
target->onMessageReceived(target, message);
}

void		GameObject::attachBehaviour(ABehaviour* behaviour)
{
	behaviour->setTarget(this);
	this->_behaviours.push_back(behaviour);
}
