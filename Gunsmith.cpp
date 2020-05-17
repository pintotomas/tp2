#include "Gunsmith.h"
#include <unistd.h>
#include <map>
#include <string>
//para debug, borrar

std::map<Resource, int > gunsmith_requirements =	{
	{ Resource::hierro, 2 },
	{ Resource::carbon, 2 }
};

int gunsmith_benefit_points = 3;

Gunsmith::Gunsmith(InventoryMonitor *inventory_monitor,
 PointStorer *point_storer)
    : Producer(inventory_monitor, gunsmith_requirements,
     gunsmith_benefit_points, 
    	point_storer) {}
