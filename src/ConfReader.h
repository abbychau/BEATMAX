#ifndef _CONFREADER_H_
#define _CONFREADER_H_

#include <string>

class ConfReader {
   public:
      ConfReader ();
      ConfReader (const std::string &location);
      ~ConfReader ();

      void loadFromFile (const std::string &location);
   private:
};

#endif
