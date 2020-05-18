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
  InventoryMonitor(Inventory *inventory, int gatherers_working);
  ~InventoryMonitor();
  void add(Resource material);
  void stop_one_worker();
  //Elimino constructor por copia y por movimiento
  InventoryMonitor(const InventoryMonitor &) = delete;
  InventoryMonitor &operator=(const InventoryMonitor &) = delete;
  bool inventory_handle_requirements(std::map<Resource, int> requirements);
};

#endif //INVENTORY_H
