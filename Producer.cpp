#include "Producer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>
#include <map>
#include <string>

Producer::Producer(InventoryMonitor *inventory_monitor,
 std::map<Resource, int> requirements)
    : inventory_monitor(inventory_monitor), requirements(requirements) {}

void Producer::run() {
  bool producing = true;
  while (producing) {
  	//este is_active no deberia ni existir,
    // todo deberia hacerse en una unica funcion
    if (!this->inventory_monitor->is_active()) {
         break;
    }
    else {
      this->inventory_monitor->inventory_handle_requirements(this-> requirements);
    }

      // for (const auto& p : requirements ) {

      // std::cout << to_string(p.first) << ":" << p.second <<
      // std::endl; // "Karl", "George"
      //     // p.second is Employee object.
      // }
      
    }
    usleep(150);
  }

