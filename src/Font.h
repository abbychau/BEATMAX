#ifndef _FONT_H_
#define _FONT_H_

#include <string>
#include <SDL_ttf.h>

class Texture;

class Font {
   public:
      Font ();
      Font (const std::string &location, int size);
      ~Font ();

      void loadFromFile (const std::string &location, int size);
      void renderText (const std::string &text, Texture &texture, int r=255, int g=255, int b=255);

   private:
      TTF_Font *font;
};

#endif
