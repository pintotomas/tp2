#include "Carpenter.h"
#include <unistd.h>
#include <map>
#include <string>

std::map<std::string, int > carpenter_requirements =	{
	{ "hierro", 1 },
	{ "madera", 3 }
};

Carpenter::Carpenter(InventoryMonitor *inventory_monitor)
    : Producer(inventory_monitor, carpenter_requirements) {}
