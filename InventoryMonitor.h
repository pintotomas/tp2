#ifndef INVENTORY_MONITOR_H
#define INVENTORY_MONITOR_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include "Resource.h"
#include "Inventory.h"

class InventoryMonitor {
 private:
  std::mutex mutex;
  std::condition_variable cv;
  Inventory *inventory;
  int gatherers_working;

 public:
  InventoryMonitor(Inventory *inventory, int gatherers_working);
  ~InventoryMonitor();
  void add(Resource material);
  void stop_one_worker();
  bool is_active();
  //Elimino constructor por copia y por movimiento
  InventoryMonitor(const InventoryMonitor &) = delete;
  InventoryMonitor &operator=(const InventoryMonitor &) = delete;
  void inventory_handle_requirements(std::map<Resource, int> requirements);
};

#endif //INVENTORY_H
