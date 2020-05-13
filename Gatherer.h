#ifndef GATHERER_H
#define GATHERER_H

#include "Thread.h"
#include "BlockingQueueResource.h"
#include "InventoryMonitor.h"

class Gatherer : public Thread {
 public:
  explicit Gatherer(BlockingQueueResource *queue, InventoryMonitor *inventory_monitor);
  void run();

 private:
  BlockingQueueResource *queue;
  InventoryMonitor *inventory_monitor;
};


#endif //GATHERER_H