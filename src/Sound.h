#ifndef _SOUND_H_
#define _SOUND_H_

#ifdef __APPLE__
   #include <OpenAL/al.h>
#else
   #include <al/al.h>
#endif

class SoundBuffer;

class Sound {
   public:
      Sound ();
      Sound (const SoundBuffer &buffer);
      ~Sound ();

      void loadFromBuffer (const SoundBuffer &buffer);

      void play ();
      void pause ();
      void stop ();

      bool isPlaying ();
   private:
      bool loaded;
      ALuint source;
};

#endif
