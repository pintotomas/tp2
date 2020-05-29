#ifndef BLOCKING_QUEUE_RESOURCE_H
#define BLOCKING_QUEUE_RESOURCE_H

#include <condition_variable>
#include <mutex>
#include <queue>

#include "Resource.h"

class BlockingQueueResource {
 private:
  bool isClosed;
  std::queue<Resource> queue;
  std::mutex mutex;
  std::condition_variable cv;

 protected:
 public:
  BlockingQueueResource();
  ~BlockingQueueResource();
  void push(const Resource &material);
  const Resource pop();
  void close();
  BlockingQueueResource(const BlockingQueueResource &) = delete;
  BlockingQueueResource &operator=(const BlockingQueueResource &) = delete;
};

#endif //BLOCKING_QUEUE_RESOURCE_H
