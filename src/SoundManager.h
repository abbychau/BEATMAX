#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#include "Sound.h"

class SoundBuffer;

class SoundManager {
   public:
      // Maximum number of simultaneous sounds
      static const int MAX_SOUNDS = 32;

      SoundManager ();
      ~SoundManager ();

      void addSoundBuffer (SoundBuffer &buffer);
   private:
      Sound sounds[MAX_SOUNDS];
};

#endif

