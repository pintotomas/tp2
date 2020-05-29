#include "Chef.h"
#include <unistd.h>
#include <map>
#include <string>

Chef::Chef
    (InventoryMonitor &inventory_monitor, PointStorer &point_storer)
    : Producer(inventory_monitor, point_storer) {
    	requirements.emplace(Resource::trigo, 2);
    	requirements.emplace(Resource::carbon, 1);
    	benefit_points = 5;
    }
