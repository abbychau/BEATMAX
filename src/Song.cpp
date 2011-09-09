#include <cstdio>
#include <fstream>
#include <string>
#include <queue>
#include <cctype>
#include <cassert>

#include "Song.h"
#include "Sound.h"
#include "SoundBuffer.h"

using std::string;
using std::queue;

Song::Song () {

}

Song::~Song () {

}

queue<Note> * Song::getNoteEvents () {
   return &(this->noteEvents);
}

queue<int> * Song::getMeasureLineEvents () {
   return &(this->measureLineEvents);
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

