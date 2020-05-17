#include "Inventory.h"
#include <string>

Inventory::Inventory()
    : trigo(0), carbon(0), madera(0), hierro(0) {}

Inventory::~Inventory() {}

void Inventory::add(const Resource resource) {
  std::string resource_description = to_string(resource);
  if (resource_description == TRIGO) this->trigo++;
  if (resource_description == MADERA) this->madera++; 
  if (resource_description == CARBON) this->carbon++; 
  if (resource_description == HIERRO) this->hierro++; 
}

int Inventory::get_carbon() {
	return this->carbon;
}

int Inventory::get_hierro() {
	return this->hierro;
}

int Inventory::get_trigo() {
	return this->trigo;
}

int Inventory::get_madera() {
	return this->madera;
}
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
