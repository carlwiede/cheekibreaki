#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../include/glad/glad.h"

#ifdef __linux__
#include <glm/glm.hpp>
#else
#include "../include/glm/glm.hpp"
#endif

#include "texture.h"
#include "sprite_renderer.h"

// A container object for storing relevant information
// about a single object entity in the game.
class GameObject
{
    public:
        // object state
        glm::vec2   Position, Size, Velocity;
        glm::vec3   Color;
        float       Rotation;
        bool        IsSolid;
        bool        Destroyed;

        // render state
        Texture2D   Sprite;

        // constructor(s)
        GameObject();
        GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

        // draw sprite
        virtual void Draw(SpriteRenderer &renderer);
};

#endif