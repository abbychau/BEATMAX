#ifndef _GAME_H_
#define _GAME_H_

#include "SDL.h"

#ifdef __APPLE__
   #include <OpenAL/al.h>
   #include <OpenAL/alc.h>
#else
   #include <AL/al.h>
   #include <AL/alc.h>
#endif

class Game {
   public:
      Game ();
      ~Game ();

      // Starts the game
      void start ();

      // Pauses the game timer
      void pauseTimer ();

      // Resumes the game timer
      void resumeTimer ();

      // Returns the time in millisecs since the game started 
      // (excludes pause times)
      unsigned int getTimeSinceInit ();

      SDL_Surface * getScreenHandle ();

      // Return a pointer to the game instance
      static Game * getInstance ();

   private:
      bool errorLoadingLibraries;
      bool running;
      bool paused;
      unsigned int initTime;
      unsigned int pauseTime;

      SDL_Surface *screen;

      ALCdevice *alcDevice;
      ALCcontext *alcContext;

      void initGL ();
      void initAL ();
      void resizeWindow (int width, int height);
};

#endif
