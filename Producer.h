#ifndef PRODUCER_H
#define PRODUCER_H

#include "Resource.h"
#include "Thread.h"
#include "InventoryMonitor.h"
#include "PointStorer.h"
#include <map>
#include "exceptions.h"
#include <unistd.h>

class Producer : public Thread {
 private:
  InventoryMonitor &inventory_monitor;
  PointStorer &point_storer;
 protected:
  std::map<Resource, int> requirements;
  int benefit_points;
 public:
  explicit Producer(InventoryMonitor &inventory_monitor
  , PointStorer &point_storer);
  ~Producer();
  void run();
  //Elimino constructor por copia y por movimiento
  Producer(const Producer &) = delete;
  Producer &operator=(const Producer &) = delete;
};

#endif //PRODUCER_H
