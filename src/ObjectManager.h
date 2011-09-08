#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <list>

class GraphicObject;

class ObjectManager {
   public:
      ObjectManager ();
      ~ObjectManager ();

      // Adds an object to the manager (to be drawn)
      void addObject (GraphicObject &object);

      // Draws all objects onto the screen
      virtual void update ();
   protected:
      std::list<GraphicObject *> objectList;
};

#endif
