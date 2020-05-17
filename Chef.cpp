#include "Chef.h"
#include <unistd.h>
#include <map>
#include <string>
//para debug, borrar

std::map<std::string, int > chef_requirements =	{
		{ "trigo", 2 },
		{ "carbon", 1 }
	};

Chef::Chef(InventoryMonitor *inventory_monitor)
    : Producer(inventory_monitor, chef_requirements){}
