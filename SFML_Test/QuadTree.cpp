#include "QuadTree.h"
#include "Entity.h"

Quadtree::~Quadtree()
{
    for (auto child : children) {
        delete child;
    }
}

void Quadtree::Insert(Entity* entity)
{
    if (!Contains(entity)) {
        return; // L'entité n'est pas dans ce nœud
    }

    if (entities.size() < CAPACITY || level >= MAX_LEVELS) {
        entities.push_back(entity);
    }
    else {
        if (children.empty()) {
            Subdivide();
        }

        for (auto child : children) {
            child->Insert(entity);
        }
    }
}

std::vector<Entity*> Quadtree::Query(Entity* entity)
{
    std::vector<Entity*> result;

    if (!Contains(entity)) return result;

    for (auto e : entities) {
        if (e != entity && entity->IsColliding(e)) { // On filtre directement
            result.push_back(e);
        }
    }

    if (!children.empty()) {
        for (auto child : children) {
            auto childResult = child->Query(entity);
            result.insert(result.end(), childResult.begin(), childResult.end());
        }
    }

    return result;
}


void Quadtree::Clear()
{
    entities.clear();
    for (auto child : children) {
        child->Clear();
    }
}

bool Quadtree::Contains(Entity* entity) const
{
    const sf::Vector2f& pos = entity->GetPosition();
    const sf::Vector2f& size = entity->GetSize();
    return pos.x >= x &&
        pos.x + size.x <= x + width &&
        pos.y >= y &&
        pos.y + size.y <= y + height;
}

void Quadtree::Subdivide()
{
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    children.push_back(new Quadtree(x, y, halfWidth, halfHeight, level + 1));
    children.push_back(new Quadtree(x + halfWidth, y, halfWidth, halfHeight, level + 1));
    children.push_back(new Quadtree(x, y + halfHeight, halfWidth, halfHeight, level + 1));
    children.push_back(new Quadtree(x + halfWidth, y + halfHeight, halfWidth, halfHeight, level + 1));
}

void Quadtree::UpdateEntity(Entity* entity)
{
    if (!Contains(entity)) {
        Remove(entity); 
        Insert(entity); 
    }
}


void Quadtree::Remove(Entity* entity)
{
    // Suppression de l'entité si elle est dans ce nœud
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
        return;
    }

    // Si l'entité est dans un sous-nœud, on la supprime récursivement
    for (auto& child : children) {
        child->Remove(entity);
    }
}
