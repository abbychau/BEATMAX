#include <cassert>
#include <SDL.h>

#include "Font.h"
#include "Texture.h"


using std::string;

Font::Font () {
   this->font = NULL;
}

Font::Font (const string &location, int size) {
   this->loadFromFile (location, size);
}

Font::~Font () {
   if (this->font != NULL) {
      TTF_CloseFont (this->font);
   }
}

void Font::loadFromFile (const string &location, int size) {
   this->font = TTF_OpenFont (location.c_str(), size);

}

void Font::renderText (const string &text, Texture &texture, int r, int g, int b) {
   SDL_Surface *fontSurface = NULL;
   SDL_Color colour;

   // Make the default colour white
   colour.r = r;
   colour.g = g;
   colour.b = b;

   // Make sure a font has been loaded
   assert (this->font != NULL);

   fontSurface = TTF_RenderUTF8_Blended (this->font, text.c_str(), colour);

   // Make sure the font surface is fine
   assert (fontSurface != NULL);

   // Load into the texture
   texture.loadFromSurface (fontSurface);

   // Free the surface
   SDL_FreeSurface (fontSurface);
}
