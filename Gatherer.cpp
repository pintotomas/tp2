#include "Gatherer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>
#include "exceptions.h"
#define SLEEP_TIME 50

Gatherer::Gatherer(BlockingQueueResource *queue, 
  InventoryMonitor *inventory_monitor) {
 this->queue = queue; 
 this->inventory_monitor = inventory_monitor; 
}

void Gatherer::run() {
  bool gathering = true;
  while (gathering) {
  	try {
  		Resource resource = this->queue->pop();
      usleep(SLEEP_TIME);
  		//std::cout << "Recolecte: " << to_string(resource) << '\n';
      this->inventory_monitor->add(resource);
  	} catch(ClosedQueueException){
      this->inventory_monitor->stop_one_worker();
  		break;
  	}
    // Resource *resource = this->queue->pop();
    // if (resource != nullptr) {
    //   // Guardar en inventario
    //   std::cout << "Recolecte: " << to_string(*resource) << '\n';
    //   delete resource;
    // } else {
    //   std::cout << "End\n";
    //   gathering = false;
    // }
  }
}
