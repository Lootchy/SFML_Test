#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

class Entity
{
private:
	static uint32_t sNextId;
	bool IsDestroy = false;
	uint32_t mId;
	std::string mTag;

	const sf::Texture* mTexture;
	sf::Sprite mSprite;


public:
	Entity(const std::string& filepath)
		: mId(sNextId++),
		mTexture(TextureManager::getTexture("base")),
		mSprite(*mTexture)
	{
		SetTexture(filepath);
	}




	~Entity();

	virtual void Init() {}
	virtual void Update(float deltaTime) {}
	virtual void OnCollision() {}

	void Destroy();
	bool IsEntityDestroy()const;
	bool IsColliding(Entity* entity)const;

	void SetTexture(const std::string& name);
	void SetTexture(const sf::Texture& texture);
	void SetColor(const sf::Color& color);
	void SetPosition(float x, float y);
	void SetSize(float x, float y);
	void SetTag(const std::string& tag) { mTag = tag; }


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

public:

	~Manager();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void Refresh();

	
	Entity* CreateEntity(const std::string name, sf::Vector2f size) {
		

		Entity* entity = nullptr;

		
		entity = new Entity(name);

		if (entity) {
			entity->SetSize(size.x, size.y);
			entity->Init();
			mEntities.emplace_back(entity);
		}

		return entity;
	}




	std::vector<Entity*>& GetEntity() { return mEntities; }
};

