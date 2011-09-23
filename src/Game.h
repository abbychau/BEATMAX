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

namespace Game {
   // Initialise the game
   void initialise (int argc, char *argv[]);

   // Do any cleanup before exiting the game
   void cleanup ();

   // Starts the game
   void start ();

   // Exits the game
   void exit ();

   // Pauses the main game timer (all Timer objects depend on this)
   void pauseTimer ();

   // Resumes the main game timer
   void resumeTimer ();

   // Returns the time in millisecs since the game started 
   // (excludes pause times)
   unsigned int getTimeSinceInit ();
}

#endif
