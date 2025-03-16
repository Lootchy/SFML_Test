#pragma once
#include "Entity.h"

class Player : public Entity
{
private:

public:
	Player(Manager* manager, const std::string& name)
		: Entity(manager, name)
	{
	}
	void Init()override;
	void Update(float deltaTime)override;

};

