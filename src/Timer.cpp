#include "Timer.h"
#include "Game.h"

Timer::Timer () {
   // Initial settings
   this->started = false;
   this->reset ();

   // Game instance to get timer information from
   game = Game::getInstance ();
}

Timer::~Timer () {

}

void Timer::start () {
   this->started = true;
}

void Timer::stop () {
   this->started = false;
   this->stopTime = game->getTimeSinceInit ();
}

void Timer::reset () {
   this->startTime = game->getTimeSinceInit ();
   this->stopTime =  this->startTime;
}

unsigned int Timer::getTicks () {
   unsigned int ticks;

   if (this->started) {
      ticks = game->getTimeSinceInit () - this->startTime;
   } else {
      ticks = this->stopTime - this->startTime;
   }

   return ticks;
}
