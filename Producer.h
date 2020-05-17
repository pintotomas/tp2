#ifndef PRODUCER_H
#define PRODUCER_H

#include "Resource.h"
#include "Thread.h"
#include "InventoryMonitor.h"
#include "PointStorer.h"
#include <map>
#include <string>
#include "exceptions.h"

class Producer : public Thread {
 private:
  InventoryMonitor *inventory_monitor;
  std::map<Resource, int> requirements;
  int benefit_points;
  PointStorer* point_storer;

 public:
  explicit Producer(InventoryMonitor *inventory_monitor,
   std::map<Resource, int> requirements, int benefit_points,
   PointStorer *point_storer);
  void run();
  //Elimino constructor por copia y por movimiento
  Producer(const Producer &) = delete;
  Producer &operator=(const Producer &) = delete;
};

#endif //PRODUCER_H