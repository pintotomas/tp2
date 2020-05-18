#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "BlockingQueueResource.h"
#include "Gatherer.h"
#include "Producer.h"
#include "Gunsmith.h"
#include "Chef.h"
#include "Carpenter.h"
#include <vector>
#include "InventoryMonitor.h"

#ifndef ORCHESTATOR_H
#define ORCHESTATOR_H

class Orchestator {
 private:
  std::ifstream& workers_file;
  std::ifstream& map_file;
//  Inventory &inventory;
//  Inventory &inventory;

 protected:
 public:
  Orchestator(std::ifstream& workers_file, std::ifstream& map_file);
  ~Orchestator();
  void run();
  //Elimino constructor por por movimiento
  Orchestator(const Orchestator &) = delete;
  Orchestator &operator=(const Orchestator &) = delete;
};

#endif //ORCHESTATOR_H
