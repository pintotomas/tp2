#include "Carpenter.h"
#include <unistd.h>
#include <map>
#include <string>

Carpenter::Carpenter
    (InventoryMonitor &inventory_monitor, PointStorer &point_storer)
    : Producer(inventory_monitor, point_storer) {
    	requirements.emplace(Resource::hierro, 1);
    	requirements.emplace(Resource::madera, 3);
    	benefit_points = 2;
    }
