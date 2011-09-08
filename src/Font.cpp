#ifndef _FONT_H_
#define _FONT_H_

#include <string>

class Font {
   public:
      Font ();
      Font (const std::string &location);
      ~Font ();

      void loadFromFile (const std::string &location);
   private:
};

#endif
