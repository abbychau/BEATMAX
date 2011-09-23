#ifndef _SOUNDBUFFER_H_
#define _SOUNDBUFFER_H_

#include <string>

#ifdef __APPLE__
   #include <OpenAL/al.h>
#else
   #include <AL/al.h>
#endif

class SoundBuffer {
   public:
      static const int MAX_BUFFER = 67108864;
      static const int CHUNK_SIZE = 4096;

      SoundBuffer ();
      SoundBuffer (const std::string &location);
      ~SoundBuffer ();

      void loadFromFile (const std::string &location);

      ALuint getALBuffer () const;
   protected:
      bool loaded;
      ALuint buffer;

      void loadOgg (const std::string &location);
};

#endif
