#include "Producer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>

Producer::Producer(InventoryMonitor *inventory_monitor)
    : inventory_monitor(inventory_monitor) {}

void Producer::run() {
  bool producing = true;
  while (producing) {
    if(!this->inventory_monitor->is_active()){
        std::cout << "Stopping producer" << std::endl;
      break;
    }
    usleep(150);

  }
}
