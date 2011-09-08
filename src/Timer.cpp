#include "Timer.h"
#include "Game.h"

Timer::Timer () {
   // Initial settings
   this->started = false;
   this->reset ();

   // Game instance to get timer information from
   this->game = Game::getInstance ();
}

Timer::~Timer () {

}

void Timer::start () {
   this->started = true;

   if (this->startTime != this->stopTime) {
      // Shift start time forward to offset stop time
      this->startTime += (this->game->getTimeSinceInit() - this->stopTime);
      this->stopTime = this->startTime;
   }
}

void Timer::stop () {
   this->started = false;
   this->stopTime = this->game->getTimeSinceInit ();
}

void Timer::reset () {
   this->startTime = this->game->getTimeSinceInit ();
   this->stopTime =  this->startTime;
}

unsigned int Timer::getTicks () {
   unsigned int ticks;

   if (this->started) {
      ticks = this->game->getTimeSinceInit () - this->startTime;
   } else {
      ticks = this->stopTime - this->startTime;
   }

   return ticks;
}
