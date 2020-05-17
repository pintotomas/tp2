#include "BlockingQueueResource.h"
#include "exceptions.h"

#include <string>

BlockingQueueResource::BlockingQueueResource()
    : isClosed(false), queue(), mutex(), cv() {}

BlockingQueueResource::~BlockingQueueResource() {}

void BlockingQueueResource::push(Resource resource) {
  std::unique_lock<std::mutex> lock(mutex);
  queue.push(resource);
  cv.notify_all();
}

Resource BlockingQueueResource::pop() {
  std::unique_lock<std::mutex> lock(mutex);

  while (queue.empty()) {
    if (isClosed) {
      throw ClosedQueueException();
    }
    cv.wait(lock);
  }

  Resource resource = queue.front();
  queue.pop();
  return resource;
}

void BlockingQueueResource::close() {
  std::unique_lock<std::mutex> lock(mutex);
  isClosed = true;
  cv.notify_all();
}
