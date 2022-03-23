#ifndef TEXTURE_H
#define TEXTURE_H

#include "../include/glad/glad.h"

// Class to store and configure texture in OpenGL.
// Also hosts utility functions
class Texture2D
{
    public:
        // ID of texture object, used in texture operations to refer to this particular texture
        unsigned int ID;

        // texture image dimensions
        unsigned int Width, Height; // width and height of loaded image in pixels

        // texture format
        unsigned int Internal_Format; // format of texture object
        unsigned int Image_Format;    // format of loaded image

        // texture configuration
        unsigned int Wrap_S;        // wrapping mode on S axis
        unsigned int Wrap_T;        // wrapping mode on T axis
        unsigned int Filter_Min;    // filtering mode if texture pixels < screen pixels
        unsigned int Filter_Max;    // filtering mode if texture pixels > screen pixels

        // constructor (sets default texture modes)
        Texture2D();

        // generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data);

        // binds texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;

};

#endif