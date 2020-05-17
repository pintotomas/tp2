// Your First C++ Program

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

#define SUCCESS 0
#define ERROR 1
#define ARG_COUNT 3

bool valid_arguments(int argc) {
    if (argc != ARG_COUNT) {
        std::cerr << "Se deben especificar los archivos de mapa"
        "y trabajadores. Ejemplo:" 
        "./tp trabajadores.txt mapa.txt\n";
        return false;
    }
    return true;
}

bool valid_stream(std::ifstream& stream) {
    if (!stream) {
      std::cerr << "Error al abrir archivo!\n";
      return false;
    }
    return true;
}

/* Recibe el archivo de trabajadores, y devuelve un mapa
   <Tipo trabajador, cantidad>
*/
std::map<std::string, int> parse_workers(std::ifstream& stream) {
    std::map<std::string, int> workers;
    std::string s; 
    std::string delimiter = "=";
    while (std::getline(stream, s)) {
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            //std::cout << "Type: " << token << std::endl;
            s.erase(0, pos + delimiter.length());
        }
        workers[token] = std::stoi(s);
        //std::cout << "Quantity: " << s << std::endl;
    }
    return workers;
}

std::vector<Gatherer *> generate_gatherers(int quantity,
                                      BlockingQueueResource *queue,
                                      InventoryMonitor *inventory_monitor) {
  std::vector<Gatherer *> gatherers(quantity);
  for (int i = 0; i < quantity; i++) {
    gatherers[i] = new Gatherer(queue, inventory_monitor);
    gatherers[i]->start();
  }
  return gatherers;
}


std::vector<Producer *> generate_producers(std::string description,
 int quantity, InventoryMonitor *inventory_monitor, PointStorer *point_storer) {
  std::vector<Producer *> producers(quantity);
  for (int i = 0; i < quantity; i++) {
    if (description == "Armeros") {
      producers[i] = new Gunsmith(inventory_monitor, point_storer);
    }
    if (description == "Carpinteros") {
      producers[i] = new Carpenter(inventory_monitor, point_storer); 
    }
    if (description == "Cocineros") {
      producers[i] = new Chef(inventory_monitor, point_storer);
    }
    producers[i]->start();
  }
  return producers;
}

void join_and_destroy_gatherers(std::vector<Gatherer *> gatherers) {
  for (auto gatherer = gatherers.begin();
   gatherer != gatherers.end(); gatherer++){
    (*gatherer)->join();
    delete *gatherer;
  }
}

void join_and_destroy_producers(std::vector<Producer *> producers) {
  for (auto producer = producers.begin();
   producer != producers.end(); producer++){
    (*producer)->join();
    delete *producer;
  }
}

void parse_map(std::ifstream& stream,
 BlockingQueueResource *queue_trigo,
  BlockingQueueResource *queue_madera,
   BlockingQueueResource *queue_minerales) {
  char ch;
  while (stream >> std::noskipws >> ch) {
    if (ch == 'T') queue_trigo->push(Resource::trigo);
    else if (ch == 'M') queue_madera->push(Resource::madera);
    else if (ch == 'C') queue_minerales->push(Resource::carbon);
    else if (ch == 'H') queue_minerales->push(Resource::hierro);
  }
}

int main(int argc, char *argv[]) {
    if (!valid_arguments(argc)) return ERROR;
    std::ifstream workers_file(argv[1]);
    std::ifstream map_file(argv[2]);
    if (!valid_stream(workers_file)) return ERROR;
    if (!valid_stream(map_file)) return ERROR;
    std::map<std::string, int> workers = parse_workers(workers_file);
    int gatherers_quantity = workers.find("Agricultores")->second +
                             workers.find("Leniadores")->second +
                             workers.find("Mineros")->second;
    BlockingQueueResource queue_trigo;
    BlockingQueueResource queue_madera;
    BlockingQueueResource queue_minerales;

    Inventory inventory;
    PointStorer point_storer;

    InventoryMonitor inventory_monitor(&inventory, gatherers_quantity);

    std::vector<Producer *> cocineros =
     generate_producers("Cocineros", workers.find("Cocineros")->second,
      &inventory_monitor, &point_storer);
    std::vector<Producer *> carpinteros =
     generate_producers("Carpinteros", workers.find("Carpinteros")->second,
      &inventory_monitor, &point_storer);
    std::vector<Producer *> armeros = 
    generate_producers("Armeros", workers.find("Armeros")->second,
     &inventory_monitor, &point_storer);

    std::vector<Gatherer *> agricultores = 
    generate_gatherers(workers.find("Agricultores")->second, &queue_trigo,
     &inventory_monitor);
    std::vector<Gatherer *> leniadores =
     generate_gatherers(workers.find("Leniadores")->second, &queue_madera,
      &inventory_monitor);
    std::vector<Gatherer *> mineros =
     generate_gatherers(workers.find("Mineros")->second, &queue_minerales,
      &inventory_monitor);
    

    parse_map(map_file, &queue_trigo, &queue_madera, &queue_minerales);
    queue_trigo.close();
    queue_madera.close();
    queue_minerales.close();
    join_and_destroy_gatherers(agricultores);
    join_and_destroy_gatherers(leniadores);
    join_and_destroy_gatherers(mineros);

    join_and_destroy_producers(cocineros);
    join_and_destroy_producers(carpinteros);
    join_and_destroy_producers(armeros);
    /*
    Imprimo recursos restantes
    */
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
    std::cout << "Puntos de Beneficio acumulados: " << points << std::endl; 

    return SUCCESS;
}
