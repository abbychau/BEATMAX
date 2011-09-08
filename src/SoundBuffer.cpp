#include "SoundBuffer.h"

#include <vorbis/vorbisfile.h>

using std::string;

SoundBuffer::SoundBuffer () {
   this->loaded = false;
}

SoundBuffer::SoundBuffer (const std::string &location) {
   this->loaded = false;
   this->loadFromFile (location);
}

SoundBuffer::~SoundBuffer () {
   if (this->loaded) {
      alDeleteBuffers (1, &(this->buffer));
   }
}

void SoundBuffer::loadFromFile (const std::string &location) {
   if (this->loaded) {
      // Delete any existing buffers
      alDeleteBuffers (1, &(this->buffer));
   }

   // Generate buffer
   alGenBuffers (1, &(this->buffer));

   // Only supports ogg's for now
   this->loadOgg (location);
}

ALuint SoundBuffer::getALBuffer () const {
   return (this->buffer);
}

void SoundBuffer::loadOgg (const string &location) {
   char temp[CHUNK_SIZE];
   char *soundBuf;

   ALsizei freq;
   ALenum format;

   int bitStream;
   vorbis_info *info;
   OggVorbis_File oggFile;

   // Open vorbis file
   ov_fopen (location.c_str(), &oggFile);

   // Get info
   info = ov_info (&oggFile, -1);
   freq = info->rate;

   if (info->channels == 1) {
      format = AL_FORMAT_MONO16;
   } else {
      format = AL_FORMAT_STEREO16;
   }

   // Decode
   int curOffset = 0;
   int bytesRead = ov_read (&oggFile, temp, CHUNK_SIZE, 0, 2, 1, &bitStream);

   // Allocate memory for decoded data
   soundBuf = new char[MAX_BUFFER];

   while (bytesRead > 0) {
      // append decoded data chunk
      memcpy (soundBuf+curOffset, temp, bytesRead);
      curOffset += bytesRead;

      bytesRead = ov_read (&oggFile, temp, CHUNK_SIZE, 0, 2, 1, &bitStream);
   }

   // Close the ogg file
   ov_clear (&oggFile);
   
   //  the buffer
   alBufferData (buffer, format, soundBuf, curOffset, freq);

   this->loaded = true;

   // Free the memory used for the decoded data
   delete[] soundBuf;
}
