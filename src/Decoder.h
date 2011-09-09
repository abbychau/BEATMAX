#ifndef _DECODER_H_
#define _DECODER_H_

#include <string>

#ifdef __APPLE__
   #include <OpenAL/al.h>
#else
   #include <al/al.h>
#endif

namespace Decoder {
   // Loads an audio file from location, and stores the decoded
   // data into the buffer
   // Returns true on success
   bool decodeAudio (const std::string &location, void *buffer,
                     ALenum &format, int &size, ALsizei &freq);
}

#endif
