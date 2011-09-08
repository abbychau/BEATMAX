#include <iostream>
#include <cmath>
#include "GraphicObject.h"
#include "Texture.h"

GraphicObject::GraphicObject () {
   // Set default position
   this->x = 0;
   this->y = 0;

   // Set default colours
   this->colour.r = DEFAULT_R;
   this->colour.g = DEFAULT_G;
   this->colour.b = DEFAULT_B;
   this->colour.alpha = DEFAULT_ALPHA;

   // Set default rotation angle to zero
   this->rotationAngle = 0.0f;

   // Set default blending options
   this->isBlendEnabled = true;
   this->blendSrcFactor = GL_SRC_ALPHA;
   this->blendDestFactor = GL_ONE_MINUS_SRC_ALPHA;

   // No texture has been loaded yet, set it to NULL
   this->objectTexture = NULL;
}

GraphicObject::~GraphicObject () {
}

void GraphicObject::setTexture (Texture &newTexture) {
   // Set the GraphicObject's dimensions to the texture's default
   this->width = newTexture.getWidth();
   this->height = newTexture.getHeight();
   
   // Set the texture pointer
   this->objectTexture = &newTexture;
}

void GraphicObject::setX (int newX) {
   this->x = newX;
}

void GraphicObject::setY (int newY) {
   this->y = newY;
}

void GraphicObject::setRelativeX (int relativeX) {
   this->x += relativeX;
}

void GraphicObject::setRelativeY (int relativeY) {
   this->y += relativeY;
}

void GraphicObject::setWidth (int newWidth) {
   this->width = newWidth;
   assert (this->width >= 0);
}

void GraphicObject::setHeight (int newHeight) {
   this->height = newHeight;
   assert (this->height >= 0);
}

void GraphicObject::rotate (float degrees) {
   // Rotate by degrees
   this->rotationAngle += degrees; 

   if (this->rotationAngle >= MAX_ANGLE) {
      // If the angle exceeds 360 degrees, the angle
      // should be made into the smaller value that results in the
      // same amount of rotation
      this->rotationAngle -= MAX_ANGLE;
   }
}

void GraphicObject::setAngle (float newAngle) {
   this->rotationAngle = newAngle;
   if (this->rotationAngle >= MAX_ANGLE) {
      this->rotationAngle -= MAX_ANGLE;
   }
}

void GraphicObject::setColour (float r, float g, float b) {
   this->colour.r = r;
   this->colour.g = g;
   this->colour.b = b;
}

void GraphicObject::setAlpha (float alpha) {
   this->colour.alpha = alpha;
}

void GraphicObject::enableBlend (bool enable) {
   this->isBlendEnabled = enable;
}

void GraphicObject::setBlendFunc (GLenum sfactor, GLenum dfactor) {
   this->blendSrcFactor = sfactor;
   this->blendDestFactor = dfactor;
}

Texture * GraphicObject::getTexture () {
   // Make sure there is a valid objectTexture to return
   assert (this->objectTexture != NULL);

   return objectTexture;
}

int GraphicObject::getX () {
   return x;
}

int GraphicObject::getY () {
   return y;
}

int GraphicObject::getWidth () {
   return width;
}

int GraphicObject::getHeight () {
   return height;
}

float GraphicObject::getAlpha () {
   return colour.alpha;
}

void GraphicObject::draw () {
   // Make sure that a texture has been loaded
   // assert (objectTexture != NULL);
   
   // Draw the texture
   this->drawTexture ();
}

void GraphicObject::setDrawingOptions () {
   // Set colour
   glColor4f (colour.r, colour.g, colour.b, colour.alpha);

   // Set blending options
   if (this->isBlendEnabled) {
      glEnable (GL_BLEND);
      glBlendFunc (this->blendSrcFactor, this->blendDestFactor);
   } else {
      glDisable (GL_BLEND);
   }
}

void GraphicObject::drawTexture () {
   GLuint texture;

   assert (this->objectTexture != NULL);

   setDrawingOptions (); 
   texture = objectTexture->getTextureName ();

   // Find the centre coordinates of the texture (for rotation)
   int halfW = ceil ((float)width/2);
   int halfH = ceil ((float)height/2);

   // Load identity matrix
   glLoadIdentity ();

   // Bind the current texture
   glBindTexture (GL_TEXTURE_2D, texture);

   // Move the the location to the centre of the texture to be rotated
   glTranslatef (x+halfW, y+halfH, 0);

   // Rotate the texture
   glRotatef (rotationAngle, 0.0f, 0.0f, 1.0f);

   // Translate back so we can draw the texture
   glTranslatef (-halfW, -halfH, 0);

   // Draw the textured quad
   glBegin (GL_QUADS);
      glTexCoord2d (1, 1);
      glVertex2f (width, height);

      glTexCoord2d (0, 1);
      glVertex2f (0, height);

      glTexCoord2d (0, 0);
      glVertex2f (0, 0);

      glTexCoord2d (1, 0);
      glVertex2f (width, 0);
   glEnd ();
}

