#ifndef GATHERER_H
#define GATHERER_H

#include "Thread.h"
#include "BlockingQueueResource.h"

class Gatherer : public Thread {
 public:
  explicit Gatherer(BlockingQueueResource *queue);
  void run();

 private:
  BlockingQueueResource *queue;
};


#endif //GATHERER_H