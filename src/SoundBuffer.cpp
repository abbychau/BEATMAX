#include <iostream>
#include <cassert>
#include <vorbis/vorbisfile.h>

#include "SoundBuffer.h"
#include "Decoder.h"

using std::string;

SoundBuffer::SoundBuffer () {
   this->loaded = false;

   // Generate buffer
   alGenBuffers (1, &(this->buffer));
}

SoundBuffer::SoundBuffer (const std::string &location) {
   this->loaded = false;
   this->loadFromFile (location);
}

SoundBuffer::~SoundBuffer () {
   // Delete buffer
   alDeleteBuffers (1, &(this->buffer));
}

void SoundBuffer::loadFromFile (const std::string &location) {
   ALsizei freq;
   ALenum format;
   int size = 0;

   // Allocate memory for decoded buffer, and decode
   char *soundBuf = new char[MAX_BUFFER];
   Decoder::decodeAudio (location, soundBuf, format, size, freq);

   alBufferData (this->buffer, format, soundBuf, size, freq);

   this->loaded = true;

   // Free memory used by decoded buffer
   delete[] soundBuf;
}

ALuint SoundBuffer::getALBuffer () const {
   assert (this->loaded);
   return (this->buffer);
}

