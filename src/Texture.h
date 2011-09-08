#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <iostream>
#include <string>
#include <cassert>

#include "SDL.h"

#ifdef __APPLE__
   #include <OpenGL/gl.h>
#else
   #include <gl/gl.h>
#endif

class Texture {
   public:
      Texture ();

      // Constructor that also takes in a path to a texture file
      Texture (const std::string &texturePath);

      // Constructor that also takes in a SDL_Surface *
      Texture (SDL_Surface *textureSurface);

      // Destructor
      ~Texture ();

      // Function that returns true if a texture has been loaded,
      // false otherwise
      bool textureLoaded ();

      // Loads a texture, given the path to that texture file
      // If a texture has already been loaded, that old texture is deleted
      void loadFromFile (const std::string &texturePath);

      // Loads a texture given a SDL_Surface *
      void loadFromSurface (SDL_Surface *textureSurface);

      // Function that returns the OpenGL texture name
      GLuint getTextureName ();

      // Function that returns the texture's dimensions
      int getWidth ();
      int getHeight ();
   private:
      // Variable that keeps track of whether a texture has been loaded
      bool isTextureLoaded; 

      // Variable that stores the texture name
      GLuint texture;

      // Variables which store the texture's original size dimensions (in pixels)
      int width;
      int height;

      // Function that initialises the variables used by the class
      void init ();

      // Function that converts a SDL_Surface * to a OpenGL texture
      GLuint surfaceToTexture (SDL_Surface *textureSurface);
};

#endif
