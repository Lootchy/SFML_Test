#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "TextureManager.h"
#include "QuadTree.h"

class Manager;

class Entity
{
protected:
	Manager* mManager;

private:
	static uint32_t sNextId;
	bool IsDestroy = false;
	bool HasCollision = true;
	uint32_t mId;
	std::string mTag;

	const sf::Texture* mTexture;
	sf::Sprite mSprite;


public:
	Entity(Manager* manager, const std::string& filepath)
		: mManager(manager),
		mId(sNextId++),
		mTexture(TextureManager::getTexture("base")),
		mSprite(*mTexture)
	{
		SetTexture(filepath);
	}




	~Entity();

	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	virtual void OnCollision(Entity* collidedWith) {};

	void Destroy();
	bool IsEntityDestroy()const;
	bool IsColliding(Entity* entity)const;
	void CanCollide(bool coll) { HasCollision = coll; }

	void SetTexture(const std::string& name);
	void SetTexture(const sf::Texture& texture);
	void SetColor(const sf::Color& color);
	void SetPosition(float x, float y);
	void SetSize(float x, float y);
	void SetTag(const std::string& tag) { mTag = tag; }
	void SetManager(Manager* manager) { mManager = manager; }


	const sf::Texture& GetTexture() const { return *mTexture; }
	sf::Sprite& GetSprite() { return mSprite; }
	sf::Vector2f GetSize() const {
		return mSprite.getGlobalBounds().size;
	}
	sf::Vector2f GetPosition()const { return mSprite.getPosition(); }
	uint32_t GetEntityId()const { return mId; }
	const std::string& GetTag() { return mTag; }

	friend class Manager;
};



class Manager 
{
private:
	std::vector<Entity*> mEntities;
	Quadtree quadtree;
	const int numThreads = std::thread::hardware_concurrency();

public:
	Manager(float x, float y) : quadtree(0, 0, x, y) {}

	~Manager();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void Refresh();

	template<typename T>
	T* CreateEntity(const std::string name, sf::Vector2f size, Manager* manager) {

		T* newEntity = new T(manager, name);

		if (!newEntity) {
			std::cerr << "Erreur: newEntity est nullptr après allocation !" << std::endl;
			return nullptr;
		}
		Entity* entity = newEntity;
		entity->SetSize(size.x, size.y);
		entity->Init();

		mEntities.emplace_back(newEntity);
		return newEntity;
	}




	static void ProcessCollisions(std::vector<Entity*>& entities, Quadtree& quadtree, int start, int end);
	std::vector<Entity*>& GetEntity() { return mEntities; }
};

