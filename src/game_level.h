#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include "../include/glad/glad.h"

#ifdef __linux__
#include <glm/glm.hpp>
#else
#include "../include/glm/glm.hpp"
#endif

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

// A GameLevel holds all Tiles of a Breakout level
// and has functionality to load and render levels from drive
class GameLevel
{
    public:
        // level state
        std::vector<GameObject> Bricks;

        // constructor
        GameLevel() { }

        // load level from file
        void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);

        // render level
        void Draw(SpriteRenderer &renderer);

        // check if level is completed (all non-solid tiles destroyed)
        bool IsCompleted();

    private:
        // init level from tile data
        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);

};

#endif