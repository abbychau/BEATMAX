#include "../Sound.h"
#include "../SoundBuffer.h"
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <unistd.h>

extern "C" {
   #include <libavcodec/avcodec.h>
   #include <libavformat/avformat.h>
}

int main () {
   avcodec_init ();
   av_register_all ();

   ALCdevice *device = alcOpenDevice (NULL);
   ALCcontext *context = alcCreateContext (device, NULL);
   alcMakeContextCurrent (context);

   Sound sound;
   SoundBuffer buffer;

   alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
   alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
   alListener3f(AL_ORIENTATION, 0.0f, 0.0f, -1.0f);

   buffer.loadFromFile ("_test-01.wav");
   sound.loadFromBuffer (buffer);

   sound.play ();

   while (sound.isPlaying()) {
      sleep (1);
   }

   alcDestroyContext (context);
   alcCloseDevice (device);

   return 0;
}
