#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

class Entity
{
private:
	static uint32_t sNextId;

	bool IsDestroy = false;
	uint32_t mId;

	const sf::Texture* mTexture = nullptr;
	sf::Sprite mSprite;


public:
	Entity(const sf::Texture& texture)
		: mId(sNextId++), mSprite(texture)
	{
		SetTexture(texture);
	}




	~Entity();

	virtual void Init() {}
	virtual void Update(float deltaTime) {}

	void Destroy();
	bool IsEntityDestroy()const;

	void SetTexture(const std::string& filepath);
	void SetTexture(const sf::Texture& texture);
	void SetColor(const sf::Color& color);
	void SetPosition(float x, float y);
	void SetSize(float x, float y);


	const sf::Texture& GetTexture() const { return *mTexture; }
	

	sf::Sprite& GetSprite() { return mSprite; }

	sf::Vector2f GetPosition()const { return mSprite.getPosition(); }

	uint32_t GetEntityId()const { return mId; }

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

	
	Entity* CreateEntity(const sf::Texture& texture, sf::Vector2f size) {
		

		Entity* entity = nullptr;

		
		entity = new Entity(texture); 

		if (entity) {
			entity->SetSize(size.x, size.y);
			entity->Init();
			mEntities.emplace_back(entity);
		}

		return entity;
	}




	std::vector<Entity*>& GetEntity() { return mEntities; }
};

