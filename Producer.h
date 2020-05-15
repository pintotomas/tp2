#ifndef PRODUCER_H
#define PRODUCER_H

#include "Resource.h"
#include "Thread.h"
#include "InventoryMonitor.h"

class Producer : public Thread {
 protected:
  InventoryMonitor *inventory_monitor;

 public:
  explicit Producer(InventoryMonitor *inventory_monitor);
  void run();
  //Elimino constructor por copia y por movimiento
  Producer(const Producer &) = delete;
  Producer &operator=(const Producer &) = delete;

};

#endif //PRODUCER_H
