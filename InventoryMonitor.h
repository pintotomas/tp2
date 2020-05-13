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
  // int trigo;
  // int carbon;
  // int madera;
  // int hierro;
 protected:
 public:
  InventoryMonitor(Inventory *inventory);
  ~InventoryMonitor();
  void add(Resource material);
  // int get_carbon();
  // int get_trigo();
  // int get_madera();
  // int get_hierro();
  //Resource pop();
  //void close();
  //Elimino constructor por copia y por movimiento
  InventoryMonitor(const InventoryMonitor &) = delete;
  InventoryMonitor &operator=(const InventoryMonitor &) = delete;

};

#endif //INVENTORY_H