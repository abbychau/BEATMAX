#include <cstdlib>
#include <iostream>
#include <fstream>

#include "ConfReader.h"

using std::string;
using std::ifstream;

ConfReader::ConfReader () {
   
}

ConfReader::ConfReader (const string &location) {
   this->loadFromFile (location);
}

ConfReader::~ConfReader() {

}

void ConfReader::loadFromFile (const string &location) {
   ifstream input;
   string currentLine;
   string currentSection;

   input.open (location.c_str());

   getline (input, currentLine);
   
   while (input.good()) {
      if (currentLine[0] != ';') {
         // If the current line is not a comment
         size_t pos = currentLine.find ("[");
         if (pos != string::npos) {
            // The line is the start of a new section
            currentSection = currentLine.substr (pos+1, currentLine.find ("]")-pos-1);   
         }

         pos = currentLine.find ("=");

         if (pos != string::npos) {
            string newKey = currentLine.substr (0, pos);
            string newValue = currentLine.substr (pos+1, currentLine.length());

            this->data[currentSection][newKey] = newValue;
         }

     }

      getline (input, currentLine);
   }

   input.close ();
}

string ConfReader::getStrValue (const string &sectionName, const string keyName) {
   return this->data[sectionName][keyName]; 
}

int ConfReader::getIntValue (const string &sectionName, const string keyName) {
   string value = this->getStrValue (sectionName, keyName);

   return atoi (value.c_str());
}
