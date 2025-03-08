#pragma once
#include <SFML/Graphics.hpp>

class BounceBall
{
private:
	float mSize;
	sf::RectangleShape mShape;

	float x, y = 0;
	float dy = 0;

	float mBounciness;
	float mGravity;
	float mVelocity;

public:
	BounceBall();
	~BounceBall();

	void Init();
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

	sf::RectangleShape GetShape() { return mShape; }
	float GetBounciness() { return mBounciness; }
	float GetGravity() { return mGravity; }

	void SetBounciness(float bounce) { mBounciness = bounce; }
	void SetGravity(float gravity) { mGravity = gravity; }

	void SetPosition(float x, float y);
	void SetColor(sf::Color color) { mShape.setFillColor(color); }

};

