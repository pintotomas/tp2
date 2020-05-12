// Your First C++ Program

#include <iostream>
#define SUCCESS 0
#define ERROR 1

int main(int argc, char *argv[]) {
    if (argc != 3) {
    	std::cerr << "Se deben especificar los archivos de mapa"
    	"y recolectores. Ejemplo:" 
    	"./tp trabajadores.txt mapa.txt\n";
    	return ERROR;
    }
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << "\n"; 
    }
    return SUCCESS;
}
