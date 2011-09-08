#ifndef _SONG_H_
#define _SONG_H_

#include <string>
#include <queue>

class Note;
class SoundBuffer;

const double DEFAULT_BPM = 130.0;
const double DEFAULT_TIME_SIGNATURE = 1.0;

const int MAX_MEASURES = 1000;
const int MAX_WAV_POINTS = 1296;
const int MAX_BPM_POINTS = 1296;

class Song {
   public:
      Song ();
      Song (const std::string &location);
      ~Song ();

      void loadFromFile (const std::string &location);

      std::queue<Note> * getNoteEvents ();
      std::queue<int> * getMeasureLineEvents ();
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

     double bpms[MAX_MEASURES];
     double timeSignatures[MAX_MEASURES];

     SoundBuffer wavPoints[MAX_WAV_POINTS];
     double bpmPoints[MAX_BPM_POINTS;
};

#endif
