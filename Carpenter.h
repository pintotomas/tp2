#include "Producer.h"
#include "Resource.h"
#ifndef CARPENTER_H
#define CARPENTER_H

class Carpenter : public Producer {
 public:
  explicit Carpenter(InventoryMonitor *inventory_monitor, PointStorer *point_storer);
};

#endif
