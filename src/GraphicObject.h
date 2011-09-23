#ifndef _GRAPHICOBJECT_H_
#define _GRAPHICOBJECT_H_

#ifdef __APPLE__
   #include <OpenGL/gl.h>
#else
   #include <GL/gl.h>
#endif

class Texture;

// Default colour values
const float DEFAULT_R     = 1.0f;
const float DEFAULT_G     = 1.0f;
const float DEFAULT_B     = 1.0f;
const float DEFAULT_ALPHA = 1.0f;

const float MAX_ANGLE = 360.0f;

class GraphicObject {
   public:
      // Colour struct
      struct Colour {
         float r;
         float g;
         float b;
         float alpha;
      };

      // Construtor/destructor
      GraphicObject ();
      ~GraphicObject ();

      // Method that takes in a reference to a Texture object 
      // and sets it as the texture for the GraphicObject
      void setTexture (Texture &newTexture);

      // Method that sets x and y coordinates (top left)
      void setX (int newX);
      void setY (int newY);

      // Method that sets x and y coordinates (centre)
      void setCentreX (int newX);
      void setCentreY (int newY);

      // Method that sets x and y coordinates relative to the current 
      // coordinates
      void setRelativeX (int relativeX);
      void setRelativeY (int relativeY);
      
      // Method that sets width and height of the GraphicObject
      void setWidth (int newWidth);
      void setHeight (int newHeight);

      // Method that rotates the GraphicObject given the angle in degrees
      // Rotation is 2D
      void rotate (float degrees);

      // Method that sets the angle of rotation or the GraphicObject
      void setAngle (float newAngle);

      // Method that sets the colour of the GraphicObject 
      void setColour (float r, float g, float b);
      void setAlpha (float alpha);

      // Methods that enable/sets the OpenGL blend functions for the GraphicObject
      void enableBlend (bool enable);
      void setBlendFunc (GLenum sfactor, GLenum dfactor);

      // Method that returns a pointer to the current texture
      Texture * getTexture ();

      // Method that returns the GraphicObject's x and y coordinates
      int getX ();
      int getY ();

      // Method that returns the width and height of the GraphicObject
      int getWidth ();
      int getHeight ();

      // Method that returns the object's alpha
      float getAlpha ();

      // Method that draws the object at its current frame
      virtual void draw ();
   protected:
      // Position/size information
      int x, y;
      int width, height;

      // Rotation information
      float rotationAngle;

      // Colour values in RGB
      Colour colour;

      // Blending information
      bool isBlendEnabled;
      GLenum blendSrcFactor;
      GLenum blendDestFactor;

      // Pointer to texture that the object is going to use
      Texture *objectTexture;

      // Method that sets the drawing options for the current GraphicObject
      // Sets things like colour and blending
      void setDrawingOptions ();

      // Method that draws the texture
      void drawTexture ();
};

#endif
