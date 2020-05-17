#include "Gunsmith.h"
#include <unistd.h>
#include <map>
#include <string>
//para debug, borrar

std::map<std::string, int > gunsmith_requirements =	{
	{ "hierro", 2 },
	{ "carbon", 2 }
};

Gunsmith::Gunsmith(InventoryMonitor *inventory_monitor)
    : Producer(inventory_monitor, gunsmith_requirements) {}
