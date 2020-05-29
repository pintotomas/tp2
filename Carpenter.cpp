#include "Carpenter.h"
#include <unistd.h>
#include <map>
#include <string>

std::map<Resource, int > carpenter_requirements =	{
	{ Resource::hierro, 1 },
	{ Resource::madera, 3 }
};

const int carpenter_benefit_points = 2;

Carpenter::Carpenter(InventoryMonitor &inventory_monitor,
 PointStorer &point_storer)
    : Producer(inventory_monitor, carpenter_requirements,
     carpenter_benefit_points, 
    	point_storer) {}
