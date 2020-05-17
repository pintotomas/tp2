#include "Producer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>
#include <map>
#include <string>
#define SLEEP_TIME 60

Producer::Producer(InventoryMonitor *inventory_monitor,
 std::map<Resource, int> requirements)
    : inventory_monitor(inventory_monitor), requirements(requirements) {}

void Producer::run() {
  while (true) {
  	//este is_active no deberia ni existir,
    // todo deberia hacerse en una unica funcion
    // if (!this->inventory_monitor->is_active()) {
    //      break;
    // }
    try {

      if (this->inventory_monitor->inventory_handle_requirements
         (this-> requirements)) {
        //std::cout << "Successfully retrieved materials, sum points!!" << std::endl;
      }
      usleep(SLEEP_TIME);
        //std::cout << "coudlnt retrieve materials, maybe in the future!!" << std::endl;
    } catch(NoMoreFutureResourcesException){
      break;
    }
      // for (const auto& p : requirements ) {

      // std::cout << to_string(p.first) << ":" << p.second <<
      // std::endl; // "Karl", "George"
      //     // p.second is Employee object.
      // }
      
    }
  }

