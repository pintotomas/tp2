#ifndef GATHERER_H
#define GATHERER_H

#include "Thread.h"
#include "BlockingQueueResource.h"
#include "Inventory.h"

class Gatherer : public Thread {
 public:
  explicit Gatherer(BlockingQueueResource *queue, Inventory *inventory);
  void run();

 private:
  BlockingQueueResource *queue;
  Inventory *inventory;
};


#endif //GATHERER_H