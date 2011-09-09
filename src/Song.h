#ifndef _SONG_H_
#define _SONG_H_

#include <string>
#include <set>

#include "Note.h"
#include "SoundBuffer.h"

class Song {
   public:
      static const int MAX_WAV_POINTS = 1296;
      static const int MAX_BPM_POINTS = 1296;

      enum eventType {
         BGM,
         BPM_CHANGE,
         MEASURE_LINE,
         NOTE
      };

      struct event {
         eventType type;
         unsigned int millisecs;
         int intValue;
         double doubleValue;

         bool operator< (const event &compare) const {
            return (this->millisecs < compare.millisecs);
         }
      };

      Song ();
      ~Song ();

      // Play the song
      void play ();

      void setTitle (const std::string &title);
      void setArtist (const std::string &artist);
      void setGenre (const std::string &genre);
      void setPlayLevel (const int level);
      void setWavPoint (int point, const std::string &location);
      void addEvent (eventType type, double value, int millisecs);
      void addEvent (eventType type, int value, int millisecs);

      std::set<event> * getEvents ();
      std::string getTitle ();
      std::string getArtist ();
      std::string getGenre ();
      int getPlayLevel ();

   private:
     std::set<event> events; 

     // Song properties
     int playerMode;
     std::string genre;
     std::string title;
     std::string artist;
     double bpm;
     int playLevel;
     int rank;

     SoundBuffer wavPoints[MAX_WAV_POINTS];
     double bpmPoints[MAX_BPM_POINTS];
};

#endif
