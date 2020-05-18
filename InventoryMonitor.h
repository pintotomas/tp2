#ifndef INVENTORY_MONITOR_H
#define INVENTORY_MONITOR_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include "Resource.h"
#include "Inventory.h"
#include "exceptions.h"
#include <map>

class InventoryMonitor {
 private:
  std::mutex mutex;
  std::condition_variable cv;
  Inventory *inventory;
  int gatherers_working;
  bool is_active();

 public:
  InventoryMonitor(Inventory *inventory, const int gatherers_working);
  ~InventoryMonitor();
  void add(const Resource material);
  void stop_one_worker();
  InventoryMonitor(const InventoryMonitor &) = delete;
  InventoryMonitor &operator=(const InventoryMonitor &) = delete;
  /*
    Tries to retrieve the quantity of resource specified in the map
    requirements. If not possible, makes the producer wait until 
    there are new resources and checks again if the requirements are satisfied.
    Throws NoMoreFutureResourcesException when there wont be any more resources
    in the inventory.
  */
  bool inventory_handle_requirements(std::map<Resource, int> requirements);
};

#endif //INVENTORY_H
