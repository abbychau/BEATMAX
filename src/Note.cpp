#include "Note.h"

Note::Note () {

}

Note::Note (int keyColumn, int millisecs, Texture &texture, int soundPoint) {
   this->setKeyColumn (keyColumn);
   this->setMillisecs (millisecs);
   this->setTexture (texture);
   this->setSoundPoint (soundPoint);
}

Note::~Note () {

}

void Note::setKeyColumn (int keyColumn) {
   this->keyColumn = keyColumn;
}

void Note::setMillisecs (int millisecs) {
   this->millisecs = millisecs;
}

void Note::setSoundPoint (int soundPoint) {
   this->soundPoint = soundPoint;
}


int Note::getKeyColumn () {
   return this->keyColumn;
}

int Note::getMillisecs () {
   return this->millisecs;
}

int Note::getSoundPoint () {
   return this->soundPoint;
}

void Note::draw () {

}

bool Note::operator< (const Note &note) const {
   return (this->millisecs < note.millisecs);
}
