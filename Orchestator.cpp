#include "Orchestator.h"
#include <map>
#include <string>
#include <vector>

std::map<std::string, int> Orchestator::parse_workers() {
    std::map<std::string, int> workers;
    std::string s; 
    std::string delimiter = "=";
    while (std::getline(workers_file, s)) {
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
        }
        workers[token] = std::stoi(s);
    }
    return std::move(workers);
}
std::vector<Gatherer *> Orchestator::create_start_gatherers(int quantity,
                                      BlockingQueueResource &queue,
                                      InventoryMonitor &inventory_monitor) {
  std::vector<Gatherer *> gatherers;
  for (int i = 0; i < quantity; i++) {
    gatherers.emplace_back(new Gatherer(queue, inventory_monitor));
    gatherers[gatherers.size() - 1]->start();
  }
  return std::move(gatherers);
}


std::vector<Producer *> Orchestator::create_start_producers
(const std::string description, const int quantity, 
  InventoryMonitor &inventory_monitor) {
  std::vector<Producer *> producers;
  for (int i = 0; i < quantity; i++) {
    if (description == "Armeros") {
      producers.emplace_back(new Gunsmith(inventory_monitor, point_storer));
    }
    if (description == "Carpinteros") {
      producers.emplace_back(new Carpenter(inventory_monitor, point_storer)); 
    }
    if (description == "Cocineros") {
      producers.emplace_back(new Chef(inventory_monitor, point_storer));
    }
    producers[producers.size() - 1]->start();
  }
  return std::move(producers);
}

void Orchestator::close_queues_finish_threads() {
    queue_trigo.close();
    queue_madera.close();
    queue_minerales.close();
    join_and_destroy_gatherers(farmers);
    join_and_destroy_gatherers(lumberjacks);
    join_and_destroy_gatherers(miners);
    join_and_destroy_producers(chefs);
    join_and_destroy_producers(carpenters);
    join_and_destroy_producers(gunsmiths);
}

void Orchestator::join_and_destroy_gatherers
                    (std::vector<Gatherer *> &gatherers) {
  for (auto gatherer = gatherers.begin();
   gatherer != gatherers.end(); gatherer++){
    (*gatherer)->join();
    delete *gatherer;
  }
}

void Orchestator::join_and_destroy_producers
                    (std::vector<Producer *> &producers) {
  for (auto producer = producers.begin();
   producer != producers.end(); producer++){
    (*producer)->join();
    delete *producer;
  }
}

void Orchestator::parse_map() {
  char ch;
  while (map_file >> std::noskipws >> ch) {
    if (ch == 'T') queue_trigo.push(Resource::trigo);
    else if (ch == 'M') queue_madera.push(Resource::madera);
    else if (ch == 'C') queue_minerales.push(Resource::carbon);
    else if (ch == 'H') queue_minerales.push(Resource::hierro);
  }
}
Orchestator::Orchestator(std::ifstream& workers_file, std::ifstream& map_file) :
workers_file(workers_file), map_file(map_file) {
  workers = parse_workers();

}

Orchestator::~Orchestator() {}

void Orchestator::print_results() {
  int remaining_trigo = inventory.remaining_quantity(Resource::trigo);
  int remaining_madera = inventory.remaining_quantity(Resource::madera);
  int remaining_carbon = inventory.remaining_quantity(Resource::carbon);
  int remaining_hierro = inventory.remaining_quantity(Resource::hierro);
  int points = point_storer.get_points();
  std::cout << "Recursos restantes:" << std::endl;
  std::cout << "  - Trigo: " << remaining_trigo << std::endl;
  std::cout << "  - Madera: " << remaining_madera << std::endl;
  std::cout << "  - Carbon: " <<  remaining_carbon << std::endl;
  std::cout << "  - Hierro: " << remaining_hierro << std::endl;
  std::cout << std::endl << "Puntos de Beneficio acumulados: "
  << points << std::endl; 
}

void Orchestator::spawn_producers(InventoryMonitor &inventory_monitor) {
    chefs = create_start_producers
    ("Cocineros", workers.find("Cocineros")->second, inventory_monitor);
    carpenters = create_start_producers
    ("Carpinteros", workers.find("Carpinteros")->second, inventory_monitor);
    gunsmiths =  create_start_producers
    ("Armeros", workers.find("Armeros")->second, inventory_monitor);
}

void Orchestator::spawn_gatherers(InventoryMonitor &inventory_monitor) { 
    farmers = create_start_gatherers
    (workers.find("Agricultores")->second, queue_trigo, inventory_monitor);
    lumberjacks = create_start_gatherers
    (workers.find("Leniadores")->second, queue_madera, inventory_monitor);
    miners = create_start_gatherers
    (workers.find("Mineros")->second, queue_minerales, inventory_monitor);
  }

void Orchestator::run() {
    //std::map<std::string, int> workers = parse_workers();
    int gatherers_quantity = workers.find("Agricultores")->second +
                             workers.find("Leniadores")->second +
                             workers.find("Mineros")->second;
    InventoryMonitor inventory_monitor(&inventory, gatherers_quantity);
    spawn_producers(inventory_monitor);
    spawn_gatherers(inventory_monitor);
    parse_map();
    close_queues_finish_threads();
}
