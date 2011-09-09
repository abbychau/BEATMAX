#include <string>

class Song;

namespace BMS {
   const double DEFAULT_BPM = 130.0;
   const double DEFAULT_TIME_SIGNATURE = 1.0;

   const int MAX_MEASURES = 1000;

   void parse (const std::string &location, Song &song);
}

