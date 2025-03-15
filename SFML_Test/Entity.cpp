#include "Entity.h"
#include "TextureManager.h"

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
    // Récupère la texture depuis le TextureManager
    sf::Texture texture = TextureManager::GetInstance().GetTexture(filepath);

    mSprite.setTexture(texture);

    sf::Vector2f newSize = mSprite.getLocalBounds().size;

    sf::Vector2f scale(
        newSize.x / static_cast<float>(texture.getSize().x),
        newSize.y / static_cast<float>(texture.getSize().y)
    );

    mSprite.setScale(scale);
}


void Entity::SetTexture(const sf::Texture& texture)
{
    mTexture = &texture; 
    mSprite.setTexture(*mTexture, true);

    sf::Vector2f newSize = mSprite.getLocalBounds().size;

    sf::Vector2f scale(
        newSize.x / static_cast<float>(mTexture->getSize().x),
        newSize.y / static_cast<float>(mTexture->getSize().y)
    );

    mSprite.setScale(scale);
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
   
    sf::Vector2f textureSize(mSprite.getTexture().getSize());
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
    size_t spriteCount = mEntities.size();

    if (spriteCount == 0)
        return;

    sf::VertexArray vertexArray(sf::PrimitiveType::Triangles, spriteCount * 6);
    sf::Texture* lastTexture = nullptr;

    int i = 0;
    for (auto& e : mEntities) {

        const sf::Sprite& sprite = e->GetSprite();
        const sf::Texture* texture = &sprite.getTexture();

        if (!texture)
            continue;

        if (lastTexture && lastTexture != texture) {
            sf::RenderStates states;
            states.texture = lastTexture;
            window.draw(vertexArray, states);

            vertexArray.clear();
            vertexArray.resize(spriteCount * 6);
            i = 0;
        }

        lastTexture = const_cast<sf::Texture*>(texture);

        sf::Vector2f pos = sprite.getPosition();
        sf::Vector2f size(sprite.getGlobalBounds().size.x, sprite.getGlobalBounds().size.y);
        sf::IntRect texRect = sprite.getTextureRect();
        int baseIndex = i * 6;
        sf::Vertex* v = &vertexArray[baseIndex];

        // Assignation des positions
        v[0].position = pos;
        v[1].position = pos + sf::Vector2f(size.x, 0);
        v[2].position = pos + sf::Vector2f(size.x, size.y);

        v[3].position = pos;
        v[4].position = pos + sf::Vector2f(size.x, size.y);
        v[5].position = pos + sf::Vector2f(0, size.y);

        // Assignation des coordonnées de texture
        v[0].texCoords = sf::Vector2f(texRect.position.x, texRect.position.y);
        v[1].texCoords = sf::Vector2f(texRect.position.x + texRect.size.x, texRect.position.y);
        v[2].texCoords = sf::Vector2f(texRect.position.x + texRect.size.x, texRect.position.y + texRect.size.y);

        v[3].texCoords = sf::Vector2f(texRect.position.x, texRect.position.y);
        v[4].texCoords = sf::Vector2f(texRect.position.x + texRect.size.x, texRect.position.y + texRect.size.y);
        v[5].texCoords = sf::Vector2f(texRect.position.x, texRect.position.y + texRect.size.y);

        i++;
    }

    if (lastTexture) {
        sf::RenderStates states;
        states.texture = lastTexture;
        window.draw(vertexArray, states);
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


