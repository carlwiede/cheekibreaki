#ifndef GAME_H
#define GAME_H

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

// Current game state
enum GameState 
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game-related state and functionality.
// Combines game-related data into a single class
// for easier access to components and manageability.
class Game 
{
    public:
        // state
        GameState       State;
        bool            Keys[1024];
        unsigned int    Width, Height;

        // constructor/destructor
        Game(unsigned int width, unsigned int height);
        ~Game();

        // initialize game state (load shaders/textures/levels)
        void Init();

        // game loop methods
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
};

#endif