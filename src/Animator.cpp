#include "Animator.h"
#include "GraphicObject.h"
#include "Timer.h"

Animator::Animator () {

}

Animator::~Animator () {

}

// Adds a fade in animation
// lower numerical value for priority means a higher priority
void Animator::addFadeAnimation (GraphicObject &object, int time, int priority, 
                                 float startAlpha, float endAlpha) {
   Animation newAnimation;

   newAnimation.time = time;
   // Alpha changes
   newAnimation.startAlpha = startAlpha;
   newAnimation.endAlpha = endAlpha;

   // Position changeos
   newAnimation.startX = object.getX ();
   newAnimation.startY = object.getY ();
   newAnimation.endX = object.getX ();
   newAnimation.endY = object.getY ();

   newAnimation.priority = priority;
   newAnimation.timer.start ();

   animationQueue.push (newAnimation);
}

// Adds a slide in effect
void Animator::addSlideInAnimation (GraphicObject &object, int time, int priority, 
                                    int startX, int startY, int endX, int endY) {
   Animation newAnimation;

   newAnimation.time = time;

   // Alpha changes
   newAnimation.startAlpha = object.getAlpha();
   newAnimation.endAlpha = object.getAlpha();

   // Position changes
   newAnimation.startX = startX;
   newAnimation.startY = startY;
   newAnimation.endX = endX;
   newAnimation.endY = endY;

   newAnimation.priority = priority;
   newAnimation.timer.start ();

   animationQueue.push (newAnimation);
}

// Updates all animations handled by the Animator
void update () {
   int numObjects = this->animationQueue.size();

   for (int i = 0; i < numObjects; i++) {
      // Get the next animation we need to do from the queue
      Animation curAnimation = animationQueue.top ();
      animationQueue.pop ();

      // Proportion of time passed to time needed to complete the current animation
      double timePassed = (double)(curAnimation.time-curAnimation.timer.getTicks())/
         curAnimation.time;

      int totalXDist = curAnimation.endX - curAnimation.startX;
      int totalYDist = curAnimation.endY - curAnimation.startY;
      int totalAlphaDist = curAnimation.endAlpha - curAnimation.startAlpha ();

      // new position
      curObject.setX (curAnimation.startX + totalXDist*timePassed);
      curObject.setY (curAnimation.startY + totalYDist*timePassed);

      // new alpha
      curObject.setAlpha (curAnimation.startAlpha + totalAlphaDist*timePassed);

      if (timePassed > 0.0) {
         // Animation not complete yet
         animationQueue.push (curAnimation);
      }
   }
}
