#ifndef _SONG_H_
#define _SONG_H_

#include <string>
#include <queue>

#include "Note.h"
#include "SoundBuffer.h"

class Song {
   public:
      static const int MAX_WAV_POINTS = 1296;
      static const int MAX_BPM_POINTS = 1296;

      Song ();
      ~Song ();

      std::queue<Note> * getNoteEvents ();
      std::queue<int> * getMeasureLineEvents ();

      void setTitle (const std::string &title);
      void setArtist (const std::string &artist);
      void setGenre (const std::string &genre);
      void setPlayLevel (const int level);
      void setWavPoint (int point, const std::string &location);

      std::string getTitle ();
      std::string getArtist ();
      std::string getGenre ();
      int getPlayLevel ();

   private:
     std::queue<Note> noteEvents; 
     std::queue<int> measureLineEvents;

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
