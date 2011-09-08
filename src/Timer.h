#ifndef _TIMER_H_
#define _TIMER_H_

class Game;

class Timer {
   public:
      Timer ();
      ~Timer ();

      void start ();
      void stop ();
      void reset ();
      unsigned int getTicks ();
   protected:
      unsigned int startTime;
      unsigned int stopTime;
      bool started;

      Game *game;
};

#endif