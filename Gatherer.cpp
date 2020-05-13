#include "Gatherer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>
#include "exceptions.h"
#define SLEEP_TIME 50

Gatherer::Gatherer(BlockingQueueResource *queue, Inventory *inventory) {
 this->queue = queue; 
 this->inventory = inventory; 

}

void Gatherer::run() {
  bool gathering = true;
  while (gathering) {
  	try {
  		Resource resource = this->queue->pop();
      usleep(SLEEP_TIME);
  		//std::cout << "Recolecte: " << to_string(resource) << '\n';
      this->inventory->add(resource);
  	} catch (ClosedQueueException) {
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
