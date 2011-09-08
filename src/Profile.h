#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <string>

class Profile {
   public:
      Profile ();
      Profile (const std::String &location);
      ~Profile ();

      void loadFromFile (const std::string &location);
   private:
      std::string name;
};

#endif
