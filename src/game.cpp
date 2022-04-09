#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include <iostream>

// Game-related state data
SpriteRenderer  *Renderer;
GameObject      *Player;
BallObject      *Ball;

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 

}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

void Game::Init()
{
    // load shaders
    #ifdef __linux__
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
    #else
    ResourceManager::LoadShader("..\\shaders\\sprite.vs", "..\\shaders\\sprite.fs", nullptr, "sprite");
    #endif

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader myShader;
    myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);
    
    // load textures
    #ifdef __linux__
    ResourceManager::LoadTexture("textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/block.png", false, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");

    // load levels
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height / 2);

    #else
    
    ResourceManager::LoadTexture("..\\textures\\background.jpg", false, "background");
    ResourceManager::LoadTexture("..\\textures\\awesomeface.png", true, "face");
    ResourceManager::LoadTexture("..\\textures\\block.png", false, "block");
    ResourceManager::LoadTexture("..\\textures\\block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("..\\textures\\paddle.png", true, "paddle");

    // load levels
    GameLevel one; one.Load("..\\levels\\one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("..\\levels\\two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("..\\levels\\three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("..\\levels\\four.lvl", this->Width, this->Height / 2);

    #endif
    
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;


    glm::vec2 playerPos = glm::vec2(
        this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->Height - PLAYER_SIZE.y
    );
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
                                              -BALL_RADIUS * 2.0f);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));

}


void Game::Update(float dt)
{
    // update objects
    Ball->Move(dt, this->Width);

    // check for collisions
    this->DoCollisions();

    if (Ball->Position.y >= this->Height)   // has ball passed bottom edge?
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // draw background
        Texture2D backgroundTexture;
        backgroundTexture = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(backgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

        // draw level
        this->Levels[this->Level].Draw(*Renderer);
    
        // draw player
        Player->Draw(*Renderer);

        // draw ball
        Ball->Draw(*Renderer);
    }
}

void Game::ResetLevel()
{
    #ifdef __linux__
    
    if (this->Level == 0)
        this->Levels[0].Load("levels/one.lvl", this->Width, this->Height / 2);
    else if (this->Level == 1)
        this->Levels[1].Load("levels/two.lvl", this->Width, this->Height / 2);
    else if (this->Level == 2)
        this->Levels[2].Load("levels/three.lvl", this->Width, this->Height / 2);
    else if (this->Level == 3)
        this->Levels[3].Load("levels/four.lvl", this->Width, this->Height / 2);

    #else

    if (this->Level == 0)
        this->Levels[0].Load("..\\levels\\one.lvl", this->Width, this->Height / 2);
    else if (this->Level == 1)
        this->Levels[1].Load("..\\levels\\two.lvl", this->Width, this->Height / 2);
    else if (this->Level == 2)
        this->Levels[2].Load("..\\levels\\three.lvl", this->Width, this->Height / 2);
    else if (this->Level == 3)
        this->Levels[3].Load("..\\levels\\four.lvl", this->Width, this->Height / 2);

    #endif
} 

void Game::ResetPlayer()
{
    // reset ball & player status
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

// collision function declarations
bool CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{

    // Ball - Brick collision
    for (GameObject &box : this->Levels[this->Level].Bricks)
    {
        if(!box.Destroyed)
        {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision)) // collision is true
            {
                // destroy block if not solid
                if (!box.IsSolid)
                    box.Destroyed = true;

                // collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);

                if (dir == LEFT || dir == RIGHT) // horizontal collision
                {
                    Ball->Velocity.x = -Ball->Velocity.x;   // reverse horizontal velocity

                    // relocate
                    float penetration = Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        Ball->Position.x += penetration;
                    else
                        Ball->Position.x -= penetration;
                }

                else // vertical collision
                {
                    Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical velocity

                    // relocate
                    float penetration = Ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        Ball->Position.y -= penetration;
                    else
                        Ball->Position.y += penetration;
                }
            }
        }
    }

    // Ball - Paddle collision
    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->Stuck && std::get<0>(result))
    {
        // check where it hit the board, change velocity accordingly
        float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
        float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        float percentage = distance / (Player->Size.x / 2.0f);

        // move
        float strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        // Ball->Velocity.y = -Ball->Velocity.y;        // causes sticky paddle
        Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
    }
}

Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // up
        glm::vec2(1.0f, 0.0f),  // right
        glm::vec2(0.0f, -1.0f), // down
        glm::vec2(-1.0f, 0.0f)  // left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

bool CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // collision on x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x
                    && two.Position.x + two.Size.x >= one.Position.x;

    // collision on y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y
                    && two.Position.y + two.Size.y >= one.Position.y;

    // return AND of both results
    return collisionX && collisionY;
}

Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // get center point of circle
    glm::vec2 center(one.Position + one.Radius);

    // calculate AABB info (center & half-extents)
    glm::vec2 aabb_half_exents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(
        two.Position.x + aabb_half_exents.x,
        two.Position.y + aabb_half_exents.y
    );

    // get difference between both center
    glm::vec2 difference = center - aabb_center;

    // clamp the difference
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_exents, aabb_half_exents);

    // add clamped values to aabb_center to get closest point
    glm::vec2 closest = aabb_center + clamped;

    // get distance between the closest point and circle center; return true if less than radius
    difference = closest - center;

    if (glm::length(difference) <= one.Radius)
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}