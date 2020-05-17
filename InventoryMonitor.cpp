#include "InventoryMonitor.h"
#include "string.h"
#include <map>

InventoryMonitor::InventoryMonitor(Inventory *inventory, int gatherers_working)
    : mutex(), cv(), inventory(inventory), gatherers_working(gatherers_working)
     {}

InventoryMonitor::~InventoryMonitor() {}

void InventoryMonitor::add(Resource resource) {
  std::unique_lock<std::mutex> lock(mutex);
  this->inventory->add(resource);
  cv.notify_all();
}

bool InventoryMonitor::inventory_handle_requirements
(std::map<Resource, int> requirements) {
  std::unique_lock<std::mutex> lock(mutex);
  bool success = false;
  if (this->inventory->has_resources(requirements)) {
    this->inventory->retrieve_resources(requirements);
    success = true;
  } else if (!this->is_active()) {
    //No hay recursos ni habra en el futuro
    throw NoMoreFutureResourcesException();
  }
  return success;
}

void InventoryMonitor::stop_one_worker(){
	std::unique_lock<std::mutex> lock(mutex);
	this->gatherers_working--;
	cv.notify_all();
}

bool InventoryMonitor::is_active(){
  return (this->gatherers_working > 0);
}
