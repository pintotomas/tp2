#include "Gatherer.h"
//para debug, borrar
#include <iostream>
#include <unistd.h>
#include "exceptions.h"
#define SLEEP_TIME 50

Gatherer::Gatherer(BlockingQueueResource *queue) { this->queue = queue; }

void Gatherer::run() {
  bool gathering = true;
  while (gathering) {
  	try {
  		Resource resource = this->queue->pop();
      usleep(SLEEP_TIME);
  		std::cout << "Recolecte: " << to_string(resource) << '\n';
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
