#include <iostream>

#ifdef __APPLE__
   #include <OpenGL/gl.h>
#else
   #include <gl/gl.h>
#endif

#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "settings.h"

// TEMP
#include "Song.h"
#include "BmsParser.h"

Game *game = NULL;

Game::Game () {
   // Initialise libraries
   this->screen = NULL;
   this->errorLoadingLibraries = false;
   this->running = false;
   this->paused = false;
   this->initTime = SDL_GetTicks ();

   try {
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
      this->screen = SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_BPP, 
                                 SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE |
                                 SDL_HWSURFACE);

      if (this->screen == NULL) {
         throw "Error while setting up SDL";
      }

      // Initialise OpenGL
      this->initGL ();
      this->resizeWindow (this->screen->w, this->screen->h);

      // Initialise OpenAL
      this->initAL ();

      // Set pointer to the game instance 
      game = this;

   } catch (const char *message) {
      this->errorLoadingLibraries = true;
      std::cerr << message << std::endl;
   }
}

Game::~Game () {
   // Cleanup    
   if (!this->errorLoadingLibraries) { 
      SDL_FreeSurface (screen);

      TTF_Quit ();
      SDL_Quit ();

      alcDestroyContext (alcContext);
      alcCloseDevice (alcDevice);
   }
}

void Game::start () {
   // Load menu screen
   if (!this->errorLoadingLibraries) {
      this->running = true;

      Song song;
      BMS::parse ("../git/data/songs/outlaw/song.bms", song);
      song.play ();

      while (this->running) {
         // Main run loop
         SDL_Event event;

         // Temporary
         while (SDL_PollEvent (&event)) {
            if (event.type == SDL_QUIT) {
               this->running = false;
            }
         }
      }
   } 
}

void Game::pauseTimer () {
   this->pauseTime = SDL_GetTicks ();
   this->paused = true;
}

void Game::resumeTimer () {
   if (this->paused) {
      this->paused = false;

      // Shift the game init time forward to 
      // offset the time paused 
      this->initTime += (SDL_GetTicks() - this->pauseTime);
   }
}

unsigned int Game::getTimeSinceInit () {
   unsigned int timeSince;

   if (this->paused) {
      timeSince = this->pauseTime-this->initTime;
   } else {
      timeSince = SDL_GetTicks () - this->initTime;
   }

   return timeSince;
}

SDL_Surface * Game::getScreenHandle () {
   return this->screen;
}

Game * Game::getInstance () {
   return game;
}

void Game::initGL () {
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

void Game::initAL () {
   this->alcDevice = alcOpenDevice (NULL);
   this->alcContext = alcCreateContext (this->alcDevice, NULL);
   alcMakeContextCurrent (this->alcContext);

   alListener3f (AL_POSITION, 0.0f, 0.0f, 0.0f);
   alListener3f (AL_VELOCITY, 0.0f, 0.0f, 0.0f);
   alListener3f (AL_ORIENTATION, 0.0f, 0.0f, -1.0f);
}

void Game::resizeWindow (int width, int height) {
   glViewport (0, 0, (GLint)width, (GLint)height);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   
   // Make 1 unit = 1 pixel
   glOrtho (0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, 1, -1);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
}
