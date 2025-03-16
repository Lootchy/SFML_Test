#include "Player.h"

void Player::Init()
{
	mPlayer = mManager->CreateEntity("base", sf::Vector2f(50.0f, 50.0f));
	mPlayer->CanCollide(false);
}

void Player::Update(float deltaTime)
{
	mPlayer->SetPosition(mPlayer->GetPosition().x + 100 * deltaTime, mPlayer->GetPosition().y);
}
