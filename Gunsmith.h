#include "Producer.h"
#include <map>

#ifndef GUNSMITH_H
#define GUNSMITH_H

class Gunsmith : public Producer {
 public:
  explicit Gunsmith(InventoryMonitor &inventory_monitor,
   PointStorer &point_storer);
};

#endif
