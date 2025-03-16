#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Window
{
private:
	sf::RenderWindow* mWindow = nullptr;
	sf::Clock mClock;

	float mDeltaTime;
	int mFPS;

public:
	Window();
	~Window();

	void CreateWindow(int x, int y, const std::string& windowName);
	sf::RenderWindow& GetWindow() { return *mWindow; }
	void Clear();
	void Draw(const sf::Drawable& drawable);
	void Display();
	bool IsOpen() { return mWindow->isOpen(); }

	const float& GetDeltaTime() { return mDeltaTime; }
	const int& GetFPS();
	void SetDeltaTime();
};

