#include "Entity.h"

// =================================================================================================
// Entity Section
// =================================================================================================
uint32_t Entity::sNextId = 1;

Entity::~Entity()
{
    delete mShape;
}

void Entity::Destroy()
{
	IsDestroy = true;
}

bool Entity::IsEntityDestroy() const
{
    return IsDestroy;
}

void Entity::SetColor(const sf::Color& color) {
    if (mShape)
        mShape->setFillColor(color);
}

void Entity::SetPosition(float x, float y)
{
    if (mShape) mShape->setPosition(sf::Vector2f(x, y));
}

void Entity::SetSize(float x, float y)
{
    if (auto* rect = dynamic_cast<sf::RectangleShape*>(mShape)) {
        rect->setSize({ x, y });
    }
}

void Entity::SetSize(float size)
{
    if (auto* circle = dynamic_cast<sf::CircleShape*>(mShape)) {
        circle->setRadius(size);
    }
}





// =================================================================================================
// Manager Section
// =================================================================================================

Manager::~Manager()
{
    for (Entity* entity : mEntities)
        delete entity;
    mEntities.clear();
}

void Manager::Update(float deltaTime)
{
	for (auto& e : mEntities) {
		e->Update(deltaTime);
	}

	Refresh();
}

void Manager::Draw(sf::RenderWindow& window)
{
    size_t rectangleCount = 0;
    for (auto& e : mEntities) {
        if (e->mShapeGeometry == Entity::ShapeType::RECTANGLE) {
            rectangleCount++;
        }
    }

    sf::VertexArray vertexArray(sf::PrimitiveType::Triangles, rectangleCount * 6);

    int i = 0;
    for (auto& e : mEntities) {
        if (e->mShapeGeometry == Entity::ShapeType::RECTANGLE) {
            const sf::RectangleShape* rect = e->GetRectangleShape();
            if (rect) {
                const sf::Vector2f& pos = rect->getPosition();
                const sf::Vector2f& size = rect->getSize();
                const sf::Color& color = rect->getFillColor();

                int baseIndex = i * 6;
                sf::Vertex* v = &vertexArray[baseIndex];

                v[0].position = pos;
                v[1].position = pos + sf::Vector2f(size.x, 0);
                v[2].position = pos + sf::Vector2f(size.x, size.y);

                v[3].position = pos;
                v[4].position = pos + sf::Vector2f(size.x, size.y);
                v[5].position = pos + sf::Vector2f(0, size.y);

                for (int j = 0; j < 6; j++) {
                    v[j].color = color;
                }

                i++;
            }
        }
    }

    window.draw(vertexArray);
}

void Manager::Refresh()
{

    auto it = std::remove_if(mEntities.begin(), mEntities.end(),
        [](Entity* entity) {
            bool shouldRemove = entity->IsEntityDestroy();
            if (shouldRemove) {
                delete entity; 
            }
            return shouldRemove;
        });

    
    mEntities.erase(it, mEntities.end());
}


