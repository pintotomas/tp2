#ifndef GATHERER_H
#define GATHERER_H

#include "Thread.h"
#include "BlockingQueueResource.h"
#include "InventoryMonitor.h"

class Gatherer : public Thread {
 private:
  BlockingQueueResource *queue;
  InventoryMonitor *inventory_monitor;

 public:
  explicit Gatherer(BlockingQueueResource *queue, 
  	InventoryMonitor *inventory_monitor);
  void run();
  //Elimino constructor por copia y por movimiento
  Gatherer(const Gatherer &) = delete;
  Gatherer &operator=(const Gatherer &) = delete;
};

#endif //GATHERER_H
