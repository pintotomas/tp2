#ifndef INVENTORY_H
#define INVENTORY_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <map>

#include "Resource.h"

class Inventory {
 private:
  // std::mutex mutex;
  // std::condition_variable cv;
  std::map<Resource, int> resources;
  //int trigo;
  //int carbon;
  //int madera;
  //int hierro;
 protected:
 public:
  Inventory();
  ~Inventory();
  void add(const Resource material);
  bool has_resources(std::map<Resource, int> req);
  int get_carbon();
  int get_trigo();
  int get_madera();
  int get_hierro();
  //Resource pop();
  //void close();
  //Elimino constructor por copia y por movimiento
  Inventory(const Inventory &) = delete;
  Inventory &operator=(const Inventory &) = delete;
};

#endif //INVENTORY_H
