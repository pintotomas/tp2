#include "InventoryMonitor.h"
#include "string.h"

InventoryMonitor::InventoryMonitor(Inventory *inventory, int gatherers_working)
    : mutex(), cv(), inventory(inventory), gatherers_working(gatherers_working)
     {}

InventoryMonitor::~InventoryMonitor() {}

void InventoryMonitor::add(Resource resource) {
  std::unique_lock<std::mutex> lock(mutex);
  this->inventory->add(resource);
  cv.notify_all();
}

void InventoryMonitor::inventory_handle_requirements(std::map<Resource, int> requirements) {
  std::unique_lock<std::mutex> lock(mutex);
  bool a = this->inventory->has_resources(requirements);
  std::cout << "Result: " << a << std::endl;
  cv.notify_all();
}

void InventoryMonitor::stop_one_worker(){
	std::unique_lock<std::mutex> lock(mutex);
	this->gatherers_working--;
	std::cout << "Gatherers working: " << this->gatherers_working << std::endl;
	cv.notify_all();
}

bool InventoryMonitor::is_active(){
  return (this->gatherers_working > 0);
}
