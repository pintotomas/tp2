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
  int lenia;
  int carbon;
  int madera;
  int hierro;
 protected:
 public:
  Inventory();
  ~Inventory();
  void add(Resource material);
  //Resource pop();
  //void close();
  //Elimino constructor por copia y por movimiento
  Inventory(const BlockingQueueResource &) = delete;
  Inventory &operator=(const BlockingQueueResource &) = delete;

};

#endif //INVENTORY_H