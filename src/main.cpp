#include "Game.h"

int main (int argc, char *argv[]) {
   Game::initialise (argc, argv);
   Game::start ();
   Game::cleanup ();

   return 0;
}
