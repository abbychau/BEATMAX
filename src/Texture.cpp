#include <iostream>
#include <string>

#include "Texture.h"
#include "SDL.h"
#include "SDL_image.h"

using std::cerr;
using std::endl;
using std::string;

Texture::Texture () {
   // Initialise variables
   this->init ();
}

Texture::Texture (const string &texturePath) {
   // Initialise variables
   this->init (); 

   // Load the texture specified by texturePath
   this->loadFromFile (texturePath);
}

Texture::Texture (SDL_Surface *textureSurface) {
   // Initialise variables
   this->init ();
   
   // Convert the SDL_Surface * to an OpenGL texture
   this->texture = surfaceToTexture (textureSurface); 
   this->width = textureSurface->w;
   this->height = textureSurface->h;

   this->isTextureLoaded = true;
}

Texture::~Texture () {
   // Cleanup
   if (this->isTextureLoaded) {
      // If a texture has been loaded, delete the texture
      glDeleteTextures (1, &(this->texture));   
   }
}

bool Texture::textureLoaded () {
   return this->isTextureLoaded;
}

void Texture::loadFromFile (const string &texturePath) {
   // SDL_Surface * that stores the texture surface
   SDL_Surface *textureSurface = NULL; 

   if (this->isTextureLoaded) {
      // If a texture has already been loaded, delete that texture
      glDeleteTextures (1, &(this->texture));   
      this->isTextureLoaded = false;
   }

   try {
      // Load the texture into a SDL_Surface * first
      textureSurface = IMG_Load (texturePath.c_str());

      if (textureSurface == NULL) {
         // The texture surface was not loaded properly
         throw "Unable to load texture surface";
      }

      // Get texture dimensions from the surface
      this->width = textureSurface->w;
      this->height = textureSurface->h;
      
      // Convert the SDL_Surface * into an OpenGL texture
      this->texture = surfaceToTexture (textureSurface);
      
      // The texture has been successfully loaded
      this->isTextureLoaded = true;
   
      // Free the surface since it is no longer needed
      SDL_FreeSurface (textureSurface);
   } catch (const char *message) {
      // Print out error message
      cerr << message << ": " << texturePath << endl;
   }

}

void Texture::loadFromSurface (SDL_Surface *textureSurface) {
   // Convert SDL_Surface * to OpenGL texture
   assert (textureSurface != NULL);

   if (this->isTextureLoaded) {
      // If a texture has already been loaded, delete that texture
      glDeleteTextures (1, &(this->texture));   
      this->isTextureLoaded = false;
   }

   this->texture = surfaceToTexture (textureSurface); 
   this->width = textureSurface->w;
   this->height = textureSurface->h;

   this->isTextureLoaded = true;
}

GLuint Texture::getTextureName () {
   assert (this->isTextureLoaded);
   return this->texture;
}

int Texture::getWidth () {
   return this->width;
}

int Texture::getHeight () {
   return this->height;
}

void Texture::init () {
   // No texture has been loaded yet
   this->isTextureLoaded = false;

   // Set the width and height to be zero since no texture is loaded
   this->width = 0;
   this->height = 0;
}

GLuint Texture::surfaceToTexture (SDL_Surface *textureSurface) {
   // Variable to hold the new texture name
   GLuint newTexture;

   // Assert that the surface is valid
   assert (textureSurface != NULL);

   // Determine image format
   int numberOfColours = textureSurface->format->BytesPerPixel;
   int textureFormat = GL_RGB;
   
   if (numberOfColours == 3) {
      if (textureSurface->format->Rmask == 0x000000ff) {
         textureFormat = GL_RGB; 
      } else {
         textureFormat = GL_BGR; 
      }
   } else if (numberOfColours == 4) {
      if (textureSurface->format->Rmask == 0x000000ff) {
         textureFormat = GL_RGBA; 
      } else {
         textureFormat = GL_BGRA; 
      }
   }

   // Generate the texture
   glGenTextures (1, &newTexture);
   glBindTexture (GL_TEXTURE_2D, newTexture);

   glTexImage2D (GL_TEXTURE_2D, 0, numberOfColours, textureSurface->w, textureSurface->h, 0,
                 textureFormat, GL_UNSIGNED_BYTE, textureSurface->pixels);

   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   return newTexture;   
}

