#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


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
	sf::Shape* mShape = nullptr;
	sf::RectangleShape* mRectShape = nullptr;

public:
	Entity(sf::Shape* shape, ShapeType type)
		: mId(sNextId++), mShape(shape), mShapeGeometry(type) {
		if (type == ShapeType::RECTANGLE) {
			mRectShape = static_cast<sf::RectangleShape*>(shape);
		}
	}

	~Entity();

	ShapeType mShapeGeometry;
	virtual void Init() {}
	virtual void Update(float deltaTime){}

	void Destroy();
	bool IsEntityDestroy()const;


	void SetColor(const sf::Color& color);
	void SetPosition(float x, float y);
	void SetSize(float x, float y);
	void SetSize(float size);

	sf::Shape& GetShape() { return *mShape; }
	sf::RectangleShape* GetRectangleShape() { return mRectShape; }
	sf::Vector2f GetPosition()const { return mShape->getPosition(); }

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
	Entity* CreateEntity(Entity::ShapeType type, Args&&... args) {
		static_assert(std::is_base_of_v<sf::Shape, T>, "T doit être une sous-classe de sf::Shape");

		Entity* entity = new Entity(new T(std::forward<Args>(args)...), type);
		entity->Init();
		mEntities.emplace_back(entity);

		return entity;
	}


	std::vector<Entity*>& GetEntity() { return mEntities; }
};

