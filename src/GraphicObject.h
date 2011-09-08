#ifndef _GRAPHICOBJECT_H_
#define _GRAPHICOBJECT_H_

#ifdef __APPLE__
   #include <OpenGL/gl.h>
#else
   #include <gl/gl.h>
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

      // Function that takes in a reference to a Texture object 
      // and sets it as the texture for the GraphicObject
      void setTexture (Texture &newTexture);

      // Function that set x and y coordinates
      void setX (int newX);
      void setY (int newY);

      // Function that sets x and y coordinates relative to the current 
      // coordinates
      void setRelativeX (int relativeX);
      void setRelativeY (int relativeY);
      
      // Function that sets width and height of the GraphicObject
      void setWidth (int newWidth);
      void setHeight (int newHeight);

      // Function that rotates the GraphicObject given the angle in degrees
      // Rotation is 2D
      void rotate (float degrees);

      // Function that sets the angle of rotation or the GraphicObject
      void setAngle (float newAngle);

      // Function that sets the colour of the GraphicObject 
      void setColour (float r, float g, float b);
      void setAlpha (float alpha);

      // Functions that enable/sets the OpenGL blend functions for the GraphicObject
      void enableBlend (bool enable);
      void setBlendFunc (GLenum sfactor, GLenum dfactor);

      // Function that returns a pointer to the current texture
      Texture * getTexture ();

      // Function that returns the GraphicObject's x and y coordinates
      int getX ();
      int getY ();

      // Function that returns the width and height of the GraphicObject
      int getWidth ();
      int getHeight ();

      // Function that returns the object's alpha
      float getAlpha ();

      // Function that draws the object at its current frame
      virtual void draw ();
   protected:
      bool firstFrame;

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

      // Function that sets the drawing options for the current GraphicObject
      // Sets things like colour and blending
      void setDrawingOptions ();

      // Function that draws the texture
      void drawTexture ();
};

#endif
