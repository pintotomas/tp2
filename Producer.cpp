#include "Producer.h"
#include <map>
#define SLEEP_TIME 60

Producer::Producer(InventoryMonitor &inventory_monitor,
 std::map<Resource, int> &requirements, const int &benefit_points,
  PointStorer &point_storer)
    : inventory_monitor(inventory_monitor), requirements(requirements),
    benefit_points(benefit_points), point_storer(point_storer) {}
Producer::~Producer() {}
void Producer::run() {
  while (true) {
    try {
      if (inventory_monitor.inventory_handle_requirements
         (requirements)) {
        point_storer.add_points(benefit_points);
        usleep(SLEEP_TIME);
      }
      } catch(NoMoreFutureResourcesException){
      break;
      }      
    }
  }
