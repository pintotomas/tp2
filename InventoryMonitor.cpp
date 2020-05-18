#include "InventoryMonitor.h"
#include <map>

InventoryMonitor::InventoryMonitor(Inventory *inventory, int gatherers_working)
    : mutex(), cv(), inventory(inventory), gatherers_working(gatherers_working)
     {}

InventoryMonitor::~InventoryMonitor() {}

void InventoryMonitor::add(const Resource resource) {
  std::unique_lock<std::mutex> lock(mutex);
  this->inventory->add(resource);
  cv.notify_all();
}

bool InventoryMonitor::inventory_handle_requirements
(std::map<Resource, int> requirements) {
  std::unique_lock<std::mutex> lock(mutex);
  while (true) {
    if (this->inventory->has_resources(requirements)) {
      this->inventory->retrieve_resources(requirements);
      return true;
    } else if (!this->is_active()) {
      throw NoMoreFutureResourcesException();
    }
    //Wait until there are more resources or a gatherer stops working
    cv.wait(lock);
  }
}

void InventoryMonitor::stop_one_worker(){
	std::unique_lock<std::mutex> lock(mutex);
	this->gatherers_working--;
	cv.notify_all();
}

bool InventoryMonitor::is_active(){
  return (this->gatherers_working > 0);
}
