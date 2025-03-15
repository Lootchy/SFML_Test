#include "Entity.h"

// =================================================================================================
// Entity Section
// =================================================================================================
uint32_t Entity::sNextId = 1;

Entity::~Entity()
{
}

void Entity::Destroy()
{
	IsDestroy = true;
}

bool Entity::IsEntityDestroy() const
{
    return IsDestroy;
}




void Entity::SetTexture(const std::string& filepath)
{

    if (!mTexture.loadFromFile(filepath, false)) {
        std::cerr << "Error loading texture: " << filepath << std::endl;
        exit(EXIT_FAILURE);
    }

    mSprite.setTexture(mTexture);

    sf::Vector2f newSize = mSprite.getLocalBounds().size;

    sf::Vector2f scale(
        newSize.x / static_cast<float>(mTexture.getSize().x),
        newSize.y / static_cast<float>(mTexture.getSize().y)
    );

    mSprite.setScale(scale);
    mSprite.setPosition(mSprite.getPosition());
}

void Entity::SetTexture(const sf::Texture& texture)
{
    mTexture = texture;
    mSprite.setTexture(mTexture, true);

    sf::Vector2f newSize = mSprite.getLocalBounds().size;

    sf::Vector2f scale(
        newSize.x / static_cast<float>(mTexture.getSize().x),
        newSize.y / static_cast<float>(mTexture.getSize().y)
    );

    mSprite.setScale(scale);
    mSprite.setPosition(mSprite.getPosition());
}





void Entity::SetColor(const sf::Color& color) 
{
    mSprite.setColor(color);
}

void Entity::SetPosition(float x, float y)
{
    mSprite.setPosition(sf::Vector2f(x, y));
}

void Entity::SetSize(float x, float y)
{
   
    sf::Vector2f textureSize(mTexture.getSize());
    mSprite.setScale(sf::Vector2f(x / textureSize.x, y / textureSize.y));

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
    /*size_t rectangleCount = 0;
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
    window.draw(vertexArray);*/

    for (auto& e : GetEntity()) {
        if (e->HasSprite()) {
            window.draw(e->GetSprite());
        }
    }
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


