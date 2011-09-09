#include <string>

class Song;

namespace BMS {
   const double DEFAULT_BPM = 130.0;
   const double DEFAULT_TIME_SIGNATURE = 1.0;

   const int MAX_MEASURES = 1001;

   const int PLAYER1_NOTE_CHANNELS[] = {16, 11, 12, 13, 14, 15, 18, 19};

   void parse (const std::string &location, Song &song);
   void parseHeaders (const std::string &location, Song &song);
   void parsePoints (const std::string &location, Song &song);
   void parseMain (const std::string &location, Song &song);
}

