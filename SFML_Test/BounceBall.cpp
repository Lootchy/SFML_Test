#include <iostream>
#include "BounceBall.h"

BounceBall::BounceBall()
{
	Init();
}

BounceBall::~BounceBall()
{
}

void BounceBall::Init()
{
	mSize = 10.0f;
	mVelocity = (std::rand() % 2 == 0) ? 1.0f : -1.0f;
	mGravity = 0.2;
	mBounciness = 0.5f;
	y = 300;
	x = 400;
	mShape.setPosition(sf::Vector2f(x, y));
	mShape.setSize(sf::Vector2f(mSize, mSize));
	mShape.setFillColor(sf::Color::Green);
}

void BounceBall::Draw(sf::RenderWindow& window)
{
	window.draw(mShape, sf::BlendAdd);
}

void BounceBall::Update(float deltaTime)
{
	mShape.setPosition(sf::Vector2f(x, y));
	
	if (y + mSize * 2 < 600) {
		y += dy * deltaTime;
		dy += mGravity;
	}
	else {
		dy *= -mBounciness;
		y += dy * 2 * deltaTime;
	}

	if (x + mSize * 0.5 < 0 || x > 800 - mSize * 2) {
		mVelocity *= -1;
	}
	x += 200 * mVelocity * deltaTime;
}

void BounceBall::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}


