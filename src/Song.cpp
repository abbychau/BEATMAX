#include <cstdio>
#include <fstream>
#include <string>
#include <cassert>
#include <iostream>

#include "Song.h"
#include "Sound.h"
#include "SoundBuffer.h"
#include "Timer.h"
#include "SoundManager.h"

using std::string;
using std::multiset;

Song::Song () {

}

Song::~Song () {

}

void Song::play () {
   // Temporary, used for testing
   // Maybe make this run on a separate thread
   SoundManager soundManager;
   Timer timer;
   timer.start ();

   multiset<event>::iterator it;

   it = this->events.begin();

   while (it != this->events.end()) {
      if (timer.getTicks() >= it->millisecs) {
         if (it->type == BGM || it->type == NOTE) {
            soundManager.addSoundBuffer (this->wavPoints[it->intValue]);
         }

         it++;
      }
   }

   // Temp
   timer.reset ();
   while (timer.getTicks() < 1000) {

   }
}

void Song::setTitle (const string &title) {
   this->title = title;
}

void Song::setArtist (const string &artist) {
   this->artist = artist;
}

void Song::setGenre (const string &genre) {
   this->genre = genre;
}

void Song::setPlayLevel (const int level) {
   this->playLevel = level;
}

void Song::setWavPoint (int point, const string &location) {
   assert (point >= 0 && point < MAX_WAV_POINTS);
   this->wavPoints[point].loadFromFile (location);
}

void Song::addEvent (eventType type, int value, int millisecs) {
   event newEvent;
   newEvent.type = type;
   newEvent.intValue = value;
   newEvent.millisecs = millisecs;

   this->events.insert (newEvent);
}

void Song::addEvent (eventType type, double value, int millisecs) {
   event newEvent;
   newEvent.type = type;
   newEvent.doubleValue = value;
   newEvent.millisecs = millisecs;

   this->events.insert (newEvent);
}

multiset<Song::event> * Song::getEvents () {
   return &(this->events);
}


string Song::getTitle () {
   return (this->title);
}

string Song::getArtist () {
   return (this->artist);
}

string Song::getGenre () {
   return (this->genre);
}

int Song::getPlayLevel () {
   return (this->playLevel);
}

