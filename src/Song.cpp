#include <cstdio>
#include <fstream>
#include <string>
#include <queue>
#include <cctype>

#include "Song.h"
#include "Sound.h"
#include "SoundBuffer.h"

using std::string;
using std::queue;

static void parseLine (string currentLine);
static void parseMessage (string currentLine);
static int base36ToInt (string number);
static int toDigit (char c);

Song::Song () {
   for (int i = 0; i < MAX_MEASURES; i++) {
      // TODO: make bpm changing work in the middle of a measure
      bpms[i] = DEFAULT_BPM;
      timeSignatures[i] = DEFAULT_TIME_SIGNATURE;
   }
}

Song::Song (const string &location) {
   this->loadFromFile (location);
}

Song::~Song () {

}

void Song::loadFromFile (const string &location) {
   // Parse BMS/BME
   ifstream bmsInput;
   string currentLine;

   // Open the bms file
   bmsInput.open (location, ifstream::in);

   while (bmsInput.good()) {
      // Read line by line
      getline (bmsInput, currentLine);

      if (currentLine[0] = '#') {
         // Parse the line
         parseLine (currentLine);
      }
   }
}

queue<Note> * getNoteEvents () {
   return &(this->noteEvents);
}

queue<int> * getMeasureLineEvents () {
   return &(this->measureLineEvents);
}

static void parseLine (string currentLine) {
   if (currentLine.find (":") != string::npos) {
      // message
      parseMessage (currentLine);
   } else if (currentLine.find ("#PLAYER") == 0) {

   } else if (currentLine.find ("#GENRE") == 0) {

   } else if (currentLine.find ("#TITLE") == 0) {
   } else if (currentLine.find ("#ARTIST") == 0) {

   } else if (currentLine.find ("#BPM") == 0) {

   } else if (currentLine.find ("#PLAYLEVEL") == 0) {

   } else if (currentLine.find ("#RANK") == 0) {

   } else if (currentLine.find ("#WAV") == 0) {

   } else if (currentLine.find ("#BPM") == 0) {

   }
}

static void parseMessage (string currentLine) {
   int measureNumber;
   int channelNumber;
   string measureString;
   string channelString;
   string message;

   // Extract the measure and channel numbers
   measureString = currentLine.substr (1, 3);
   channelString = currentLine.substr (4, 2);

   sscanf (measureString.c_str(), "%d", &measureNumber);
   sscanf (channelString.c_str(), "%d", &channelNumber);

   // Extract the message
   message = currentLine.substr (7, currentLine.length());

   if (channel == 1) {
      // BGM channel
   } else if (channel == 2) {
      // Time signature channel
   } else if (channel == 3) {
      // BPM change channel 
   } else if (channel == 4) {
      // BGA channel
   } else if (channel == 8) {
      // extended BPM
   } else {

   }
}

static int base36ToInt (string number) {
   int result = 0;
   int curDigitVal = 1;
   int length = number.length ();

   for (int i = length-1; i >= 0; i--) {
      result += curDigitVal * toDigit(number[i]);
      curDigitVal *= 36;
   }

   return result;
}

static int toDigit (char c) {
   int digitVal;

   if (isalpha(c)) {
      digitVal = toupper(c)-'A'+10;
   } else {
      digitVal = c-'0';
   }

   return digitVal;
}
