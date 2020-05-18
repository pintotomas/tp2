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
  Inventory inventory;
  PointStorer point_storer;
  BlockingQueueResource queue_trigo;
  BlockingQueueResource queue_madera;
  BlockingQueueResource queue_minerales;
  std::vector<Producer *> productores;
  std::vector<Producer *> cocineros;
  std::vector<Producer *> carpinteros;
  std::vector<Producer *> armeros;
  std::vector<Gatherer *> agricultores;
  std::vector<Gatherer *> leniadores;
  std::vector<Gatherer *> mineros;
 protected:
 public:
  Orchestator(std::ifstream& workers_file, std::ifstream& map_file);
  ~Orchestator();
  void run();
  void print_results();
  std::vector<Producer *> create_producers(std::string description,
 int quantity, InventoryMonitor *inventory_monitor);
  //Elimino constructor por por movimiento
  Orchestator(const Orchestator &) = delete;
  Orchestator &operator=(const Orchestator &) = delete;
};

#endif //ORCHESTATOR_H
