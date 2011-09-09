#include "BmsParser.h"
#include "Song.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cctype>

using std::string;
using std::ifstream;

namespace BMS {
   void initParser (const string &location);
   void parseHeaderLine (const string &line, Song &song);
   void parsePointLine (const string &line, Song &song);
   void parseMainLine (const string &line, Song &song);

   inline int getMeasure (const string &line);
   inline int getChannel (const string &line);
   inline string getMessage (const string &line);
   int baseXToInt (const string &number, int X);
   int toDigit (char c);

   string path;
   double bpms[MAX_MEASURES];
   double timeSignatures[MAX_MEASURES];
   unsigned int measureStartTimes[MAX_MEASURES];

   void parse (const string &location, Song &song) {
      initParser (location);

      parseHeaders (location, song);
      parsePoints (location, song);
      parseMain (location, song);
   }

   void parseHeaders (const string &location, Song &song) {
      ifstream bmsInput;
      string currentLine;

      // Open the bms file
      bmsInput.open (location.c_str(), ifstream::in);

      while (bmsInput.good()) {
         // Read line by line
         getline (bmsInput, currentLine);

         if (currentLine[0] == '#') {
            if (currentLine[6] != ':') {
               // Parse the line
               parseHeaderLine (currentLine, song);
            } else {
               break;
            }
         }
      }

      bmsInput.close ();

   }

   void parsePoints (const string &location, Song &song) {
      ifstream bmsInput;
      string currentLine;

      // Open the bms file
      bmsInput.open (location.c_str(), ifstream::in);

      while (bmsInput.good()) {
         // Read line by line
         getline (bmsInput, currentLine);

         if (currentLine[0] == '#') {
            parsePointLine (currentLine, song);
         } 
      }

      bmsInput.close ();

      // Calculate the start times of each measure
      measureStartTimes[0] = 0;
      for (int i = 1; i < MAX_MEASURES; i++) {
         measureStartTimes[i] = measureStartTimes[i-1] + (240000.0/bpms[i-1])*timeSignatures[i-1];
      }
   }


   void parseMain (const string &location, Song &song) {
      ifstream bmsInput;
      string currentLine;

      // Open the bms file
      bmsInput.open (location.c_str(), ifstream::in);

      while (bmsInput.good()) {
         // Read line by line
         getline (bmsInput, currentLine);

         if (currentLine[0] == '#' && currentLine[6] == ':') {
            // Parse the line
            parseMainLine (currentLine, song);
         }
      }

      bmsInput.close ();
   }

   void initParser (const string &location) {
      // Find path to BMS folder
      int lastSeparatorPos = location.rfind('/');
      path = location.substr (0, lastSeparatorPos);

      for (int i = 0; i < MAX_MEASURES; i++) {
         // TODO: make bpm changing work in the middle of a measure
         bpms[i] = DEFAULT_BPM;
         timeSignatures[i] = DEFAULT_TIME_SIGNATURE;
      }
   }

   void parseHeaderLine (const std::string &line, Song &song) {
      string value;

      if (line.find ("#PLAYER") == 0) {
         value = line.substr (8, line.length());
      } else if (line.find ("#GENRE") == 0) {
         value = line.substr (7, line.length());
         song.setGenre (value);
      } else if (line.find ("#TITLE") == 0) {
         value = line.substr (7, line.length());
         song.setTitle (value);
      } else if (line.find ("#ARTIST") == 0) {
         value = line.substr (8, line.length());
         song.setArtist (value);
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


   void parsePointLine (const std::string &line, Song &song) {
      string value;
      if (line[6] == ':') {
         // BPM/Time signature changes
         int measureNumber;
         int channelNumber;
         string message;

         measureNumber = getMeasure (line);
         channelNumber = getChannel (line);
         message = getMessage (line);

         if (channelNumber == 2) {
            // Time signature channelNumber
            timeSignatures[measureNumber] = atof (message.c_str());
         } else if (channelNumber == 3) {
            // BPM change channelNumber 
            double newBPM = atof (message.c_str());
            for (int i = measureNumber; i < MAX_MEASURES; i++) {
               bpms[i] = newBPM;
            }
         } else if (channelNumber == 8) {
            // extended BPM
         }

      } else {
         // Data Points
         
         // Find relative path

         if (line.find ("#WAV") == 0) {
            // New WAV Point
            int point = baseXToInt (line.substr (4, 2), 36);
            value = line.substr (7, line.length());

            song.setWavPoint (point, path+"/"+value);
         }
      }
   }

   void parseMainLine (const std::string &line, Song &song) {
      int measureNumber;
      int channelNumber;
      string message;
      int numMessages;

      measureNumber = getMeasure (line);
      channelNumber = getChannel (line);
      message = getMessage (line);

      numMessages = message.length()/2;

      for (int i = 1; i <= numMessages; i++) {
         int measureLength = measureStartTimes[measureNumber+1] -
            measureStartTimes[measureNumber];

         int point = baseXToInt (message.substr((i-1)*2, 2), 36);

         if (point != 0) {
            // If is valid point

            int curTime = measureStartTimes[measureNumber] + 
               (measureLength * i)/numMessages;


            if (channelNumber == 1) {
               // BGM channel
               song.addEvent (Song::BGM, point, curTime);
            } else if (channelNumber == 4) {
               // BGA channelNumber
            } else {
               // a key
               for (int c = 0; c < 8; c++) {
                  if (channelNumber == PLAYER1_NOTE_CHANNELS[c]) {
                     song.addEvent (Song::NOTE, point, curTime);
                     break;
                  }
               }
            }
         }
      }
   }

   inline int getMeasure (const string &line) {
      return (atoi(line.substr (1, 3).c_str()));
   }

   inline int getChannel (const string &line) {
      return (atoi(line.substr (4, 2).c_str()));
   }

   inline string getMessage (const string &line) {
      return (line.substr (7, line.length()));
   }

   int baseXToInt (const string &number, int X) {
      int result = 0;
      int curDigitVal = 1;
      int length = number.length ();

      for (int i = length-1; i >= 0; i--) {
         result += curDigitVal * toDigit(number[i]);
         curDigitVal *= X;
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


