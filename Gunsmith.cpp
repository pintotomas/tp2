#include "Gunsmith.h"
#include <unistd.h>
#include <map>
#include <string>

Gunsmith::Gunsmith
    (InventoryMonitor &inventory_monitor, PointStorer &point_storer)
    : Producer(inventory_monitor, point_storer) {
    	requirements.emplace(Resource::hierro, 2);
    	requirements.emplace(Resource::carbon, 2);
    	benefit_points = 3;
    }
