#ifndef _NOTE_H_
#define _NOTE_H_

#include "GraphicObject.h"

class Texture;

class Note : public GraphicObject {
   public:
      Note ();
      Note (int keyColumn, int millisecs, Texture &texture);
      ~Note ();

      void setKeyColumn (int keyColumn);
      void setMillisecs (int millisecs);

      int getKeyColumn ();
      int getMillisecs ();

      void draw ();
   private:
      // Column that the key is in
      int keyColumn;

      // Time from beginning of song 
      // when this key needs to be pressed
      int millisecs;
};

#endif
