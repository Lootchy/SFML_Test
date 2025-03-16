#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	Entity* mPlayer;

public:
	Player(Manager* manager)
		: Entity(manager, "base")
	{
	}
	void Init()override;
	void Update(float deltaTime)override;

};

