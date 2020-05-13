#ifndef INVENTORY_H
#define INVENTORY_H

#include <condition_variable>
#include <mutex>
#include <queue>

#include "Resource.h"

class Inventory {
 private:
  std::mutex mutex;
  std::condition_variable cv;
  int trigo;
  int carbon;
  int madera;
  int hierro;
 protected:
 public:
  Inventory();
  ~Inventory();
  void add(Resource material);
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