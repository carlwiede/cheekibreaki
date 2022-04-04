#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "../include/glad/glad.h"

#ifdef __linux__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#else
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#endif

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
    public:
        // constructor
        SpriteRenderer(Shader &shader);

        // destructor
        ~SpriteRenderer();

        // renders defined quad textured with given sprite
        void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    private:
        // render state
        Shader          shader;
        unsigned int    quadVAO;

        // initialize and configure quad's buffer and vertex attributes
        void initRenderData();
};

#endif