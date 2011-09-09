#ifndef _NOTE_H_
#define _NOTE_H_

#include "GraphicObject.h"

class Texture;

class Note : public GraphicObject {
   public:
      Note ();
      Note (int keyColumn, int millisecs, Texture &texture, int soundPoint);
      ~Note ();

      void setKeyColumn (int keyColumn);
      void setMillisecs (int millisecs);
      void setSoundPoint (int soundPoint);

      int getKeyColumn ();
      int getMillisecs ();
      int getSoundPoint ();

      void draw ();

      bool operator< (const Note &note) const;
   private:
      // Column that the key is in
      int keyColumn;

      // Time from beginning of song 
      // when this key needs to be pressed
      int millisecs;

      // Sound point that this note is associated with
      int soundPoint;
};

#endif
