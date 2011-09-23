#include <iostream>

#ifdef __APPLE__
   #include <OpenGL/gl.h>
#else
   #include <GL/gl.h>
#endif

#include <SDL.h>
#include <SDL_ttf.h>

extern "C" {
   #include <libavcodec/avcodec.h>
   #include <libavformat/avformat.h>
}

#include "Game.h"
#include "settings.h"

// TEMP
#include "Song.h"
#include "BmsParser.h"

bool errorLoadingLibraries;
bool running;
bool paused;
unsigned int initTime;
unsigned int pauseTime;

SDL_Surface *screen;
ALCdevice *alcDevice;
ALCcontext *alcContext;


void initGUI ();
void initGL ();
void initAL ();
void initDecoder ();
void resizeWindow (int width, int height);


void Game::initialise (int argc, char *argv[]) {
   // Initialise libraries
   screen = NULL;
   errorLoadingLibraries = false;
   running = false;
   paused = false;
   initTime = SDL_GetTicks ();

   try {
      initGUI ();
      initGL ();
      resizeWindow (screen->w, screen->h);
      initAL ();
      initDecoder ();

   } catch (const char *message) {
      errorLoadingLibraries = true;
      std::cerr << message << std::endl;
   }
}

void Game::cleanup () {
   if (!errorLoadingLibraries) { 
      SDL_FreeSurface (screen);

      TTF_Quit ();
      SDL_Quit ();

      alcDestroyContext (alcContext);
      alcCloseDevice (alcDevice);
   }
}

void Game::start () {
   // Load menu screen
   if (!errorLoadingLibraries) {
      running = true;

      // Temporary
      Song song;
      // BMS::parse ("../git/data/songs/outlaw/song.bms", song);
      BMS::parse ("../git/data/songs/cypher/_cypher_7a.bms", song);
      song.play ();

      while (running) {
         // Main run loop
         SDL_Event event;

         // Temporary
         while (SDL_PollEvent (&event)) {
            if (event.type == SDL_QUIT) {
               running = false;
            }
         }
      }
   } 
}

void Game::exit () {
   running = false;
}

void Game::pauseTimer () {
   pauseTime = SDL_GetTicks ();
   paused = true;
}

void Game::resumeTimer () {
   if (paused) {
      paused = false;

      // Shift the game init time forward to 
      // offset the time paused 
      initTime += (SDL_GetTicks() - pauseTime);
   }
}

unsigned int Game::getTimeSinceInit () {
   unsigned int timeSince;

   if (paused) {
      timeSince = pauseTime-initTime;
   } else {
      timeSince = SDL_GetTicks () - initTime;
   }

   return timeSince;
}
void initGUI () {
   // Initialise SDL library
   if (SDL_Init (SDL_INIT_VIDEO) == -1) {
      throw "Error loading SDL";
   }

   // Initialise SDL_ttf
   if (TTF_Init () == -1) {
      throw "Error loading SDL_ttf";
   }

   // Set SDL settings
   // Make window open at the centre of the screen
   SDL_putenv ((char*)"SDL_VIDEO_WINDOW_POS=center");
   
   // Set window caption
   SDL_WM_SetCaption (WINDOW_NAME, NULL);
   SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

   // Set up screen
   screen = SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_BPP, 
                              SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE |
                              SDL_HWSURFACE);

   if (screen == NULL) {
      throw "Error while setting up SDL";
   }
}

void initGL () {
   // OpenGL settings
   glShadeModel (GL_SMOOTH);
   glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

   glDisable (GL_DEPTH_TEST);
   glEnable (GL_BLEND);

   glBlendFunc (GL_SRC_ALPHA, GL_ONE);
   
   glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);

   glEnable (GL_TEXTURE_2D);  
}

void initAL () {
   alcDevice = alcOpenDevice (NULL);

   if (alcDevice == NULL) {
      throw "Unable to open audio device";
   }

   alcContext = alcCreateContext (alcDevice, NULL);

   if (alcContext == NULL) {
      throw "Unable to create audio context";
   }

   alcMakeContextCurrent (alcContext);

   // Set default listener position
   alListener3f (AL_POSITION, 0.0f, 0.0f, 0.0f);
   alListener3f (AL_VELOCITY, 0.0f, 0.0f, 0.0f);
   alListener3f (AL_ORIENTATION, 0.0f, 0.0f, -1.0f);
}

void initDecoder () {
   // Register all codecs for decoding
   avcodec_register_all ();
   av_register_all ();
}

void resizeWindow (int width, int height) {
   glViewport (0, 0, (GLint)width, (GLint)height);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   
   // Make 1 unit = 1 pixel
   glOrtho (0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, 1, -1);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
}
