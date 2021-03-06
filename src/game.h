#ifndef GAME_H
#define GAME_H

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include "game_level.h"

// Current game state
enum GameState 
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

// Initial size of paddel
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);

// Initial velocity of player paddle
const float PLAYER_VELOCITY(500.0f);

// Initial velocity of the ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

// Radius of the ball object
const float BALL_RADIUS = 12.5f;

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

        // level data
        std::vector<GameLevel>  Levels;
        unsigned int            Level;

        // initialize game state (load shaders/textures/levels)
        void Init();

        // game loop methods
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
        void DoCollisions();

        // reset
        void ResetLevel();
        void ResetPlayer();
};

#endif