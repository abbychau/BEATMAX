#include "BmsParser.h"
#include "Song.h"

#include <cstdlib>
#include <fstream>

using std::string;
using std::ifstream;


namespace BMS {
   void initParser ();
   void parseLine (const string &line, Song &song);
   void parseMessage (const string &line, Song &song);
   int base36ToInt (const string &number);
   int toDigit (char c);

   double bpms[MAX_MEASURES];
   double timeSignatures[MAX_MEASURES];

   void parse (const string &location, Song &song) {
      ifstream bmsInput;
      string currentLine;

      initParser ();

      // Open the bms file
      bmsInput.open (location.c_str(), ifstream::in);

      while (bmsInput.good()) {
         // Read line by line
         getline (bmsInput, currentLine);

         if (currentLine[0] == '#') {
            // Parse the line
            parseLine (currentLine, song);
         }
      }

      bmsInput.close ();
   }

   void initParser () {
      for (int i = 0; i < MAX_MEASURES; i++) {
         // TODO: make bpm changing work in the middle of a measure
         bpms[i] = DEFAULT_BPM;
         timeSignatures[i] = DEFAULT_TIME_SIGNATURE;
      }
   }

   void parseLine (const std::string &line, Song &song) {
      string value;

      if (line.find (":") != string::npos) {
         // message
         parseMessage (line, song);
      } else if (line.find ("#WAV") == 0) {
         // New WAV Point
         value = line.substr (5, line.length());
      } else if (line.find ("#PLAYER") == 0) {
         value = line.substr (8, line.length());
      } else if (line.find ("#GENRE") == 0) {
         value = line.substr (7, line.length());
      } else if (line.find ("#TITLE") == 0) {
         value = line.substr (7, line.length());
      } else if (line.find ("#ARTIST") == 0) {
         value = line.substr (8, line.length());
      } else if (line.find ("#BPM") == 0) {
         value = line.substr (5, line.length());
      } else if (line.find ("#PLAYLEVEL") == 0) {
         value = line.substr (8, line.length());
         song.setPlayLevel (atoi(value.c_str()));
      } else if (line.find ("#RANK") == 0) {
         value = line.substr (6, line.length());
      } else if (line.find ("#BPM") == 0) {
         double newBPM;
         value = line.substr (5, line.length());

         // Set new BPM
         newBPM = atof(value.c_str());
         for (int i = 0; i < MAX_MEASURES; i++) {
            bpms[i] = newBPM;
         }
      }
   }

   void parseMessage (const std::string &line, Song &song) {
      int measureNumber;
      int channelNumber;
      string measureString;
      string channelString;
      string message;

      // Extract the measure and channel numbers
      measureString = line.substr (1, 3);
      channelString = line.substr (4, 2);

      sscanf (measureString.c_str(), "%d", &measureNumber);
      sscanf (channelString.c_str(), "%d", &channelNumber);

      // Extract the message
      message = line.substr (7, line.length());

      if (channelNumber == 1) {
         // BGM channel
      } else if (channelNumber == 2) {
         // Time signature channelNumber
      } else if (channelNumber == 3) {
         // BPM change channelNumber 
      } else if (channelNumber == 4) {
         // BGA channelNumber
      } else if (channelNumber == 8) {
         // extended BPM
      } else {

      }
   }

   int base36ToInt (const string &number) {
      int result = 0;
      int curDigitVal = 1;
      int length = number.length ();

      for (int i = length-1; i >= 0; i--) {
         result += curDigitVal * toDigit(number[i]);
         curDigitVal *= 36;
      }

      return result;
   }

   int toDigit (char c) {
      int digitVal;

      if (isalpha(c)) {
         digitVal = toupper(c)-'A'+10;
      } else {
         digitVal = c-'0';
      }

      return digitVal;
   }
}


