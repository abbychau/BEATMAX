#ifndef _SONGPLAYSCREEN_H_
#define _SONGPLAYSCREEN_H_

#include <string>

class Screen;
class NoteManager;

class SongPlayScreen : public Screen {
   public:
      SongPlayScreen ();
      SongPlayScreen (const std::string &confLocation);
      ~SongPlayScreen ();

   private:
      NoteManager noteManager;
};

#endif
