#include "Carpenter.h"
#include <unistd.h>
#include <map>
#include <string>

std::map<Resource, int > carpenter_requirements =	{
	{ Resource::hierro, 1 },
	{ Resource::madera, 3 }
};

Carpenter::Carpenter(InventoryMonitor *inventory_monitor)
    : Producer(inventory_monitor, carpenter_requirements) {}
