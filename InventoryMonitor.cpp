#include "InventoryMonitor.h"
#include "string.h"

InventoryMonitor::InventoryMonitor(Inventory *inventory)
    : mutex(), cv(), inventory(inventory) {}

InventoryMonitor::~InventoryMonitor() {}

void InventoryMonitor::add(Resource resource) {

  std::unique_lock<std::mutex> lock(mutex);
  this->inventory->add(resource);
  // std::string resource_description = to_string(resource);
  // if(resource_description == TRIGO) this->trigo++;
  // if(resource_description == MADERA) this->madera++; 
  // if(resource_description == CARBON) this->carbon++; 
  // if(resource_description == HIERRO) this->hierro++; 
  cv.notify_all();
}

// int InventoryMonitor::get_carbon() {
// 	return this->carbon;
// }
// int InventoryMonitor::get_hierro() {
// 	return this->hierro;
// }
// int InventoryMonitor::get_trigo() {
// 	return this->trigo;
// }
// int InventoryMonitor::get_madera() {
// 	return this->madera;
// }
// Resource BlockingQueueResource::pop() {
//   std::unique_lock<std::mutex> lock(mutex);

//   while (queue.empty()) {
//     if (isClosed) {
//       //return nullptr;
//       throw ClosedQueueException();
//     }
//     cv.wait(lock);
//   }

//   Resource resource = queue.front();
//   queue.pop();
//   //Resource *resource2;
//   //resource2 = new Resource;
//   //*resource2 = resource;
//   //Resource *resourcePtr = &resource;
//   //return &resource;
//   return resource;
// }

// void BlockingQueueResource::close() {
//   std::unique_lock<std::mutex> lock(mutex);
//   isClosed = true;
//   cv.notify_all();
// }
