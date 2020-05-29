#include "Gatherer.h"
#include <unistd.h>
#include "exceptions.h"
#define SLEEP_TIME 50

Gatherer::Gatherer(BlockingQueueResource &queue, 
  InventoryMonitor &inventory_monitor) : queue(queue), inventory_monitor(inventory_monitor) {
}

void Gatherer::run() {
  bool gathering = true;
  while (gathering) {
  	try {
  		const Resource resource = queue.pop();
      usleep(SLEEP_TIME);
      inventory_monitor.add(resource);
  	} catch(ClosedQueueException){
        inventory_monitor.stop_one_worker();
  		break;
  	}
  }
}
