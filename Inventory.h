#ifndef INVENTORY_H
#define INVENTORY_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <map>

#include "Resource.h"

class Inventory {
 private:
  std::map<Resource, int> resources;
 protected:
 public:
  Inventory();
  ~Inventory();
  //Adds one resource to the inventory
  void add(const Resource material);
  /*Returns true if the inventory has all of the resources specified in
    the map. Example of the map is {Resource::hierro, 3}. The integer 
    represents the quantity needed of the Resource */
  bool has_resources(std::map<Resource, int> req);
  int remaining_quantity(Resource resource);
  /*Retrieves the resources specified in the map req, with the same 
    format as the map received in has_resources
    PRE: the inventory has enough resources (has_resources was called previous
    to this function)
    POST: the inventory resources will be diminished*/
  void retrieve_resources(std::map<Resource, int> req);
  //Elimino constructor por copia y por movimiento
  Inventory(const Inventory &) = delete;
  Inventory &operator=(const Inventory &) = delete;
};

#endif //INVENTORY_H
