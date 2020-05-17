#include "Producer.h"
#include <map>

#ifndef CHEF_H
#define CHEF_H

class Chef : public Producer {
 public:
  explicit Chef(InventoryMonitor *inventory_monitor);
};

#endif
