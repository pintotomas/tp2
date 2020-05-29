#include "Chef.h"
#include <unistd.h>
#include <map>
#include <string>
//para debug, borrar

std::map<Resource, int > chef_requirements =	{
		{ Resource::trigo, 2 },
		{ Resource::carbon, 1 }
	};

const int chef_benefit_points = 5;

Chef::Chef(InventoryMonitor &inventory_monitor, PointStorer &point_storer)
    : Producer(inventory_monitor, chef_requirements,
     chef_benefit_points, point_storer){}
