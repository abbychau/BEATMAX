#include <list>
#include "ObjectManager.h"
#include "GraphicObject.h"

using std::list;

ObjectManager::ObjectManager () {

}

ObjectManager::~ObjectManager () {

}

void ObjectManager::addObject (GraphicObject &object) {
   this->objectList.push_back (&object);
}

void ObjectManager::update () {
   list<GraphicObject *>::iterator it;

   for (it = this->objectList.begin(); 
        it != this->objectList.end();
        it++) {
      (*it)->draw ();
   }
}

