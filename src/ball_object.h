#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"

#include "game_object.h"
#include "texture.h"

// BallObject, subclass of GameObject
// Contains relevant data and functionality to
// the Breakout ball, some that are too specific
// for keeping in the general GameObject superclass
class BallObject : public GameObject
{
    public:
        // ball state
        float Radius;
        bool Stuck;

        // constructor(s)
        BallObject();
        BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

        // move the ball, keeping it constrained within window bounds (except bottom), return new position
        glm::vec2   Move(float dt, unsigned int window_width);

        // reset ball to original state with given position and velocity
        void        Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif