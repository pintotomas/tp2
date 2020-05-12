#include "BlockingQueueResource.h"

#include <string>

BlockingQueueResource::BlockingQueueResource()
    : isClosed(false), queue(), mutex(), cv() {}

BlockingQueueResource::~BlockingQueueResource() {}

void BlockingQueueResource::push(Resource resource) {
  std::unique_lock<std::mutex> lock(mutex);
  queue.push(resource);
  cv.notify_all();
}

Resource *BlockingQueueResource::pop() {
  std::unique_lock<std::mutex> lock(mutex);

  while (queue.empty()) {
    if (isClosed) {
      return nullptr;
    }
    cv.wait(lock);
  }

  Resource resource = queue.front();
  queue.pop();
  Resource *resourcePtr = &resource;
  return resourcePtr;
}

void BlockingQueueResource::close() {
  std::unique_lock<std::mutex> lock(mutex);
  isClosed = true;
  cv.notify_all();
}
