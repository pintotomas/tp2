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
    return workers;
}

std::vector<Gatherer *> Orchestator::create_start_gatherers(int quantity,
                                      BlockingQueueResource *queue,
                                      InventoryMonitor *inventory_monitor) {
  std::vector<Gatherer *> gatherers(quantity);
  for (int i = 0; i < quantity; i++) {
    gatherers[i] = new Gatherer(queue, inventory_monitor);
    gatherers[i]->start();
  }
  return gatherers;
}


std::vector<Producer *> Orchestator::create_start_producers
(const std::string description, const int quantity, 
  InventoryMonitor *inventory_monitor) {
  std::vector<Producer *> producers(quantity);
  for (int i = 0; i < quantity; i++) {
    if (description == "Armeros") {
      producers[i] = new Gunsmith(inventory_monitor, &point_storer);
    }
    if (description == "Carpinteros") {
      producers[i] = new Carpenter(inventory_monitor, &point_storer); 
    }
    if (description == "Cocineros") {
      producers[i] = new Chef(inventory_monitor, &point_storer);
    }
    producers[i]->start();
  }
  return producers;
}

static void join_and_destroy_gatherers(std::vector<Gatherer *> gatherers) {
  for (auto gatherer = gatherers.begin();
   gatherer != gatherers.end(); gatherer++){
    (*gatherer)->join();
    delete *gatherer;
  }
}

static void join_and_destroy_producers(std::vector<Producer *> producers) {
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
workers_file(workers_file), map_file(map_file) {}

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

void Orchestator::close_queues_finish_threads() {
    queue_trigo.close();
    queue_madera.close();
    queue_minerales.close();
    join_and_destroy_gatherers(agricultores);
    join_and_destroy_gatherers(leniadores);
    join_and_destroy_gatherers(mineros);
    join_and_destroy_producers(cocineros);
    join_and_destroy_producers(carpinteros);
    join_and_destroy_producers(armeros);
}

void Orchestator::generate_producers(const std::map<std::string, int> *workers, 
  InventoryMonitor *inventory_monitor) {
    cocineros = create_start_producers
    ("Cocineros", workers->find("Cocineros")->second, inventory_monitor);
    carpinteros = create_start_producers
    ("Carpinteros", workers->find("Carpinteros")->second, inventory_monitor);
    armeros =  create_start_producers
    ("Armeros", workers->find("Armeros")->second, inventory_monitor);
}

void Orchestator::generate_gatherers(const std::map<std::string, int> *workers,
    InventoryMonitor *inventory_monitor) { 
    agricultores = create_start_gatherers
    (workers->find("Agricultores")->second, &queue_trigo, inventory_monitor);
    leniadores = create_start_gatherers
    (workers->find("Leniadores")->second, &queue_madera, inventory_monitor);
    mineros = create_start_gatherers
    (workers->find("Mineros")->second, &queue_minerales, inventory_monitor);
  }

void Orchestator::run() {
    std::map<std::string, int> workers = parse_workers();
    int gatherers_quantity = workers.find("Agricultores")->second +
                             workers.find("Leniadores")->second +
                             workers.find("Mineros")->second;
    InventoryMonitor inventory_monitor(&inventory, gatherers_quantity);
    generate_producers(&workers, &inventory_monitor);
    generate_gatherers(&workers, &inventory_monitor);
    parse_map();
    close_queues_finish_threads();
}
