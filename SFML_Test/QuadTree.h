#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Entity;

class Quadtree {
public:
    static const int CAPACITY = 5;

    Quadtree(float x, float y, float w, float h, int level = 0)
        : x(x), y(y), width(w), height(h), level(level) {
    }

    ~Quadtree();

    void Insert(Entity* entity);

    std::vector<Entity*> Query(Entity* entity);

    void Clear();
    void UpdateEntity(Entity* entity);
private:
    float x, y, width, height;
    int level;
    std::vector<Entity*> entities;
    std::vector<Quadtree*> children;

    static const int MAX_LEVELS = 50;

    bool Contains(Entity* entity) const;

    void Subdivide();

    void Remove(Entity* entity);
};

