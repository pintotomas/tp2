// Your First C++ Program

#include <iostream>
#include <fstream>
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

int main(int argc, char *argv[]) {
    if (!valid_arguments(argc)) return ERROR;
    std::ifstream workersStream(argv[1]);
    std::ifstream mapStream(argv[2]);
    if (!valid_stream(workersStream)) return ERROR;
    if (!valid_stream(mapStream)) return ERROR;
    return SUCCESS;
}
