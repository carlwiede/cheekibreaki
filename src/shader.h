#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

// General purpose shader object. Compiles from file,
// generates compile/link-time error messages and hosts
// several utility functions.
class Shader
{
    public:
        // state
        unsigned int ID;

        // constructor
        Shader() { }

        // sets current shader as active
        Shader &Use();

        // compiles shader from given source (geometrySource is optional)
        void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);

        // utility methods
        void    SetFloat    (const char *name, float value, bool useShader = false);
        void    SetInteger  (const char *name, int value, bool useShader = false);
        void    SetVector2f (const char *name, float x, float y, bool useShader = false);
        void    SetVector2f (const char *name, const glm::vec2 &value, bool useShader = false);
        void    SetVector3f (const char *name, float x, float y, float z, bool useShader = false);
        void    SetVector3f (const char *name, const glm::vec3 &value, bool useShader = false);
        void    SetVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
        void    SetVector4f (const char *name, const glm::vec4 &value, bool useShader = false);
        void    SetMatrix4  (const char *name, const glm::mat4 &matrix, bool useShader = false);

    private:
        // checks compilation or linking error
        void checkCompileErrors(unsigned int object, std::string type);
};

#endif