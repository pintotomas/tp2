#include "Producer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>
#include <map>
#include <string>
#define SLEEP_TIME 60

Producer::Producer(InventoryMonitor *inventory_monitor,
 std::map<Resource, int> requirements, int benefit_points)
    : inventory_monitor(inventory_monitor), requirements(requirements),
    benefit_points(benefit_points) {}

void Producer::run() {
  while (true) {
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
    }
  }

