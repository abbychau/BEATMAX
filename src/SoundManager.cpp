#include "SoundManager.h"

SoundManager::SoundManager () {

}

SoundManager::~SoundManager () {

}

void SoundManager::addSoundBuffer (SoundBuffer &buffer) {
   for (int i = 0; i < MAX_SOUNDS; i++) {
      if (!sounds[i].isPlaying()) {
         sounds[i].loadFromBuffer (buffer);
         sounds[i].play ();
         break;
      }
   }
}

