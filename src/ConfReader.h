#ifndef _CONFREADER_H_
#define _CONFREADER_H_

#include <string>
#include <map>

class ConfReader {
   public:
      ConfReader ();
      ConfReader (const std::string &location);
      ~ConfReader();

      void loadFromFile (const std::string &location);
      std::string getStrValue (const std::string &sectionName, const std::string keyName);
      int getIntValue (const std::string &sectionName, const std::string keyName);

   private:
      // STL map that acts like a 2d array which stores
      // the section/key-value data
      // ie data[section][keyname]
      std::map<std::string, std::map<std::string, std::string> > data;
};

#endif
