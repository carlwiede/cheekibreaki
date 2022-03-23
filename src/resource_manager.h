#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "../include/glad/glad.h"

#include "texture.h"
#include "shader.h"


// Static singleton resource manager hosting functions
// to load textures and shaders. Loaded textures and/or
// shaders are stored for future reference through string handles.
// All functions are static with no public constructor defined.
class ResourceManager
{
    public:
        // resource storage
        static std::map<std::string, Shader>    Shaders;
        static std::map<std::string, Texture2D> Textures;

        // load and generate shader program
        static Shader       LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);

        // retrieves a stored shader
        static Shader       GetShader(std::string name);

        // load and generate texture from file
        static Texture2D    LoadTexture(const char *file, bool alpha, std::string name);

        // retrieve stored texture
        static Texture2D    GetTexture(std::string name);

        // properly de-allocate all loaded resources
        static void         Clear();
    
    private:
        // private constructor as we don't want any actual resource manager objects, members and functions should be publicly available (static)
        ResourceManager() { }

        // loads and generates shader from file
        static Shader       loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

        // loads a single texture from file
        static Texture2D    loadTextureFromFile(const char *file, bool alpha);
};

#endif