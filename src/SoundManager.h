#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

class Sound;

class SoundManager {
   public:
      SoundManager ();
      ~SoundManager ();

      void addSound (Sound &sound);
      void update ();
   private:

};

#endif

