#include "Producer.h"
#include <map>
#define SLEEP_TIME 60

Producer::Producer
    (InventoryMonitor &inventory_monitor,PointStorer &point_storer)
    : inventory_monitor(inventory_monitor), point_storer(point_storer) {}
Producer::~Producer() {}
void Producer::run() {
  while (true) {
    try {
      if (inventory_monitor.inventory_handle_requirements
         (requirements)) {
        usleep(SLEEP_TIME);
        point_storer.add_points(benefit_points);
      }
      } catch(NoMoreFutureResourcesException){
      break;
      }      
    }
  }
