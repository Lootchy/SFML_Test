#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

class Entity
{
public:
	enum class ShapeType {
		RECTANGLE,
		CIRCLE
	};

private:
	static uint32_t sNextId;

	bool IsDestroy = false;
	uint32_t mId;

	sf::Texture mTexture;
	sf::Sprite mSprite;


public:
	Entity(sf::Shape* shape, ShapeType type, const sf::Texture& texture)
		: mId(sNextId++), mShapeGeometry(type), mSprite(texture)
	{
		if (type == ShapeType::RECTANGLE) {
			
			SetTexture(texture);
		}
	}

	Entity(ShapeType type, const sf::Texture& texture)
		: mId(sNextId++), mShapeGeometry(type), mSprite(texture)
	{
	}


	~Entity();

	ShapeType mShapeGeometry;
	virtual void Init() {}
	virtual void Update(float deltaTime) {}

	void Destroy();
	bool IsEntityDestroy()const;
	bool HasSprite() const { return mTexture.getSize().x > 0; }

	void SetTexture(const std::string& filepath);
	void SetTexture(const sf::Texture& texture);
	void SetColor(const sf::Color& color);
	void SetPosition(float x, float y);
	void SetSize(float x, float y);
	void SetSize(float size);


	sf::Texture& GetTexture() { return mTexture; }
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

	template <typename T, typename... Args>
	Entity* CreateEntity(Entity::ShapeType type, const sf::Texture& texture, Args&&... args) {
		static_assert(std::is_base_of_v<sf::Shape, T> || std::is_same_v<T, sf::Sprite>,
			"T doit être une sous-classe de sf::Shape ou un sf::Sprite");

		Entity* entity = nullptr;

		if constexpr (std::is_base_of_v<sf::Shape, T>) {
			entity = new Entity(new T(std::forward<Args>(args)...), type, texture);
	
		}
		else if constexpr (std::is_same_v<T, sf::Sprite>) {
			entity = new Entity(type, texture); // Utilisation du bon constructeur
		}

		if (entity) {
			entity->Init();
			mEntities.emplace_back(entity);
		}

		return entity;
	}




	std::vector<Entity*>& GetEntity() { return mEntities; }
};

