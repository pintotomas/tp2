// Your First C++ Program

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "BlockingQueueResource.h"
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

int main(int argc, char *argv[]) {
    if (!valid_arguments(argc)) return ERROR;
    std::ifstream workers_file(argv[1]);
    std::ifstream map_file(argv[2]);
    if (!valid_stream(workers_file)) return ERROR;
    if (!valid_stream(map_file)) return ERROR;
    std::map<std::string, int> workers = parse_workers(workers_file);
    // print content:
      std::cout << "elements in mymap:" << '\n';
      std::cout << "Agricultores => " << workers.find("Agricultores")->second << '\n';
      std::cout << "Leniadores => " << workers.find("Leniadores")->second << '\n';
      std::cout << "Cocineros => " << workers.find("Cocineros")->second << '\n';
      std::cout << "Carpinteros => " << workers.find("Carpinteros")->second << '\n';
      std::cout << "Armeros => " << workers.find("Armeros")->second << '\n';

    return SUCCESS;
}
