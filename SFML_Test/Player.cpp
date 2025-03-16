#include "Player.h"

void Player::Init()
{
	
	CanCollide(false);
}

void Player::Update(float deltaTime)
{
	SetPosition(GetPosition().x + 100 * deltaTime, GetPosition().y);
}
