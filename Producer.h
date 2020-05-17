#ifndef PRODUCER_H
#define PRODUCER_H

#include "Resource.h"
#include "Thread.h"
#include "InventoryMonitor.h"
#include <map>
#include <string>

class Producer : public Thread {
 protected:
  InventoryMonitor *inventory_monitor;
  std::map<std::string, int> requirements;

 public:
  explicit Producer(InventoryMonitor *inventory_monitor,
   std::map<std::string, int> requirements);
  void run();
  //Elimino constructor por copia y por movimiento
  Producer(const Producer &) = delete;
  Producer &operator=(const Producer &) = delete;
};

#endif //PRODUCER_H
