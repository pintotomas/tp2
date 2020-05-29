#ifndef GATHERER_H
#define GATHERER_H

#include "Thread.h"
#include "BlockingQueueResource.h"
#include "InventoryMonitor.h"

class Gatherer : public Thread {
 private:
  BlockingQueueResource &queue;
  InventoryMonitor &inventory_monitor;

 public:
  explicit Gatherer(BlockingQueueResource &queue, 
  	InventoryMonitor &inventory_monitor);
  //Recollects resources from the queue until it's closed.
  void run();
  Gatherer(const Gatherer &) = delete;
  Gatherer &operator=(const Gatherer &) = delete;
};

#endif //GATHERER_H
