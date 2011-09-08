#include "Note.h"

Note::Note () {

}

Note::Note (int keyColumn, int millisecs, Texture &texture) {
   this->setKeyColumn (keyColumn);
   this->setMillisecs (millisecs);
   this->setTexture (texture);
}

Note::~Note () {

}

void Note::setKeyColumn (int keyColumn) {
   this->keyColumn = keyColumn;
}

void Note::setMillisecs (int millisecs) {
   this->millisecs = millisecs;
}

int Note::getKeyColumn () {
   return this->keyColumn;
}

int Note::getMillisecs () {
   return this->millisecs;
}

void Note::draw () {

}
