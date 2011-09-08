#include "Sound.h"
#include "SoundBuffer.h"

#include <cstdio>

Sound::Sound () {
   this->loaded = false;
}

Sound::Sound (const SoundBuffer &buffer) {
   this->loaded = false;
   this->loadFromBuffer (buffer);
}

Sound::~Sound () {
   if (this->loaded) {
      alDeleteSources (1, &(this->source));
   }
}

void Sound::loadFromBuffer (const SoundBuffer &buffer) {
   if (this->loaded) {
      // Delete existing source
      alDeleteSources (1, &(this->source));
   }

   // Create new sound source
   alGenSources (1, &(this->source));

   // Set source settings
   alSourcef (this->source, AL_PITCH, 1.0f);
   alSourcef (this->source, AL_GAIN, 1.0f);
   alSource3f (this->source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
   alSource3f (this->source, AL_POSITION, 0.0f, 0.0f, 0.0f);
   alSourcei (this->source, AL_LOOPING, AL_FALSE);

   // Attach buffer
   alSourcei (this->source, AL_BUFFER, buffer.getALBuffer());

   this->loaded = true;
}

void Sound::play () {
   if (this->loaded) {
      alSourcePlay (this->source);
   }
}

void Sound::pause () {
   if (this->isPlaying()) {
      alSourcePause (this->source);
   }
}

void Sound::stop () {
   if (this->isPlaying()) {
      alSourceStop (this->source);
   }
}

bool Sound::isPlaying () {
   bool playing = false;

   if (this->loaded) {
      ALint state;
      alGetSourcei (this->source, AL_SOURCE_STATE, &state);

      if (state == AL_PLAYING) {
         playing = true;
      }
   } 

   return playing;
}
