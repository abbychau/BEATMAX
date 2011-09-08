#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <deque>

class GraphicObject;
class Timer;

class Animator {
   public: 
      struct Animation {
         int time;
         double startAlpha;
         double endAlpha;
         int startX;
         int startY;
         int endX;
         int endY;
         int priority;

         GraphicObject *object;
         Timer timer;

         bool operator< (const Animation &toCompare) const {
            return (this->priority > toCompare.priority);
         }
      };

      Animator ();
      ~Animator ();

      // Adds a fade animation
      void addFadeAnimation (GraphicObject &object, int time, int priority, 
                             float startAlpha, float endAlpha);

      // Adds a slide in effect
      void addSlideInAnimation (GraphicObject &object, int time, int priority, 
                                int startX, int startY, int endX, int endY);

      // Updates all animations handled by the Animator
      void update ();

   private:
      std::priority_queue<Animation> animationQueue;
};

#endif
