#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Manager;
class Window
{
private:
	sf::RenderWindow* mWindow = nullptr;
	sf::Clock mClock;

	float mWidth;
	float mHeight;

	float mDeltaTime;
	int mFPS;

	Manager* mManager;

public:
	Window(Manager* manager);
	~Window();

	void CreateWindow(int x, int y, const std::string& windowName);

	void Draw(const sf::Drawable& drawable);
	void Update();
	void UpdateDeltaTime();

	bool IsOpen() { return mWindow->isOpen(); }
	bool HasFocus() { return mWindow->hasFocus(); }

	const float& GetDeltaTime() { return mDeltaTime; }
	const int& GetFPS();
	sf::RenderWindow& GetWindow() { return *mWindow; }

	void Clear();
	void SetVSync(bool enable){ mWindow->setVerticalSyncEnabled(enable); }
	void SetFPS(int fps){ mWindow->setFramerateLimit(fps); }

	void RunLoop();

};

