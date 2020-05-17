#include "Chef.h"
#include <unistd.h>
#include <map>
#include <string>
//para debug, borrar

std::map<Resource, int > chef_requirements =	{
		{ Resource::trigo, 2 },
		{ Resource::carbon, 1 }
	};

Chef::Chef(InventoryMonitor *inventory_monitor)
    : Producer(inventory_monitor, chef_requirements){}
