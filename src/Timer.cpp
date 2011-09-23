#include "Timer.h"
#include "Game.h"

Timer::Timer () {
   // Initial settings
   this->started = false;
   this->reset ();
}

Timer::~Timer () {

}

void Timer::start () {
   this->started = true;

   if (this->startTime != this->stopTime) {
      // Shift start time forward to offset stop time
      this->startTime += (Game::getTimeSinceInit() - this->stopTime);
      this->stopTime = this->startTime;
   }
}

void Timer::stop () {
   this->started = false;
   this->stopTime = Game::getTimeSinceInit ();
}

void Timer::reset () {
   this->startTime = Game::getTimeSinceInit ();
   this->stopTime =  this->startTime;
}

unsigned int Timer::getTicks () {
   unsigned int ticks;

   if (this->started) {
      ticks = Game::getTimeSinceInit () - this->startTime;
   } else {
      ticks = this->stopTime - this->startTime;
   }

   return ticks;
}
