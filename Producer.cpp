#include "Producer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>
#include <map>
#include <string>
#define SLEEP_TIME 60

Producer::Producer(InventoryMonitor *inventory_monitor,
 std::map<Resource, int> requirements, int benefit_points,
  PointStorer* point_storer)
    : inventory_monitor(inventory_monitor), requirements(requirements),
    benefit_points(benefit_points), point_storer(point_storer) {}
Producer::~Producer() {}
void Producer::run() {
  while (true) {
    try {
      if (this->inventory_monitor->inventory_handle_requirements
         (this->requirements)) {
        this->point_storer->add_points(this->benefit_points);
      }
      usleep(SLEEP_TIME);
      } catch(NoMoreFutureResourcesException){
      break;
      }      
    }
  }
