#include "InventoryMonitor.h"
#include <map>

InventoryMonitor::InventoryMonitor
              (Inventory &inventory, const int &gatherers_working)
    : mutex(), cv(), inventory(inventory), gatherers_working(gatherers_working)
     {}

InventoryMonitor::~InventoryMonitor() {}

void InventoryMonitor::add(const Resource &resource) {
  std::unique_lock<std::mutex> lock(mutex);
  inventory.add(resource);
  cv.notify_all();
}

bool InventoryMonitor::inventory_handle_requirements
          (std::map<Resource, int> &requirements) {
  std::unique_lock<std::mutex> lock(mutex);
  while (true) {
    if (inventory.has_resources(requirements)) {
      inventory.retrieve_resources(requirements);
      return true;
    } else if (!is_active()) {
      throw NoMoreFutureResourcesException();
    }
    //Wait until there are more resources or a there aint any more gatherers
    cv.wait(lock);
  }
}

void InventoryMonitor::stop_one_worker(){
	std::unique_lock<std::mutex> lock(mutex);
	gatherers_working--;
  if (gatherers_working == 0) cv.notify_all();
}

bool InventoryMonitor::is_active(){
  return (gatherers_working > 0);
}
