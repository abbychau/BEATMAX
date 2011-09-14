#include <iostream>

#include "Decoder.h"

extern "C" {
   #include <libavcodec/avcodec.h>
   #include <libavformat/avformat.h>
}

using std::string;
using std::cerr;
using std::endl;

namespace Decoder {
   bool decodeAudio (const string &location, void *buffer,
                     ALenum &format, int &size, ALsizei &freq) {

      bool result = true;
      AVFormatContext *formatContext = NULL;
      AVCodecContext *codecContext = NULL;
      AVCodec *codec = NULL;
      AVPacket packet;
      int audioStreamIndex = -1;
      int16_t audioFrameBuffer[AVCODEC_MAX_AUDIO_FRAME_SIZE];
      int dataSize = sizeof(audioFrameBuffer);

      try {
         // Open the file and read header information
         if (avformat_open_input (&formatContext, location.c_str(), NULL, 
                                  NULL) != 0) {

            throw "Unable to open file for audio decoding: " + location;
         } 

         // Get stream info
         if (av_find_stream_info (formatContext) < 0) {
            throw "Unable to find stream information";
         }

         for (unsigned int i = 0 ; i < formatContext->nb_streams; i++) {
            // For each stream

            // Look for an audio stream
            if (formatContext->streams[i]->codec->codec_type == 
                AVMEDIA_TYPE_AUDIO) {

               audioStreamIndex = i;
               break;
            }
         }

         if (audioStreamIndex == -1) throw "Unable to find audio stream";

         // Set codec context for this audio stream
         codecContext = formatContext->streams[audioStreamIndex]->codec;

         // Set audio file info
         freq = codecContext->sample_rate;

         if (codecContext->channels == 1) {
            format = AL_FORMAT_MONO16;
         } else {
            format = AL_FORMAT_STEREO16;
         }
         
         // Try to find a decoder for this stream 
         codec = avcodec_find_decoder (codecContext->codec_id);
         if (codec == NULL) throw "Unsupported codec";

         // Open codec
         if (avcodec_open (codecContext, codec) < 0) {
            throw "Unable to open codec";
         }

         int curIndex = 0;

         while (av_read_frame (formatContext, &packet) >= 0) {
            if (packet.stream_index == audioStreamIndex) {
               // Decode audio
               uint8_t *origData = packet.data;
               int origSize = packet.size;

               while (packet.size > 0) {
                  // Decode all data from this packet
                  dataSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
                  int length = avcodec_decode_audio3 (codecContext, 
                                                      audioFrameBuffer, 
                                                      &dataSize, &packet);

                  if (length < 0) throw "Error while decoding";

                  // Copy over the decoded data
                  memcpy ((char*)buffer+curIndex, audioFrameBuffer, 
                          dataSize);

                  packet.size -= length;
                  packet.data += length;
                  curIndex += dataSize;
               }

               packet.size = origSize;
               packet.data = origData;
               av_free_packet (&packet);
            }
         }

         // Set size of decoded data
         size = curIndex;

      } catch (const string &exception) {
         cerr << exception << endl;
         result = false;
      }

      // Cleanup

      if (codecContext != NULL) 
         avcodec_close (codecContext);

      if (formatContext != NULL) 
         av_close_input_file (formatContext);

      return result;
   }
}
