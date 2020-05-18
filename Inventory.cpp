#include "Inventory.h"
#include <string>
#include <map>

const std::map<Resource, int > resources_stock =  {
  { Resource::hierro, 0 },
  { Resource::carbon, 0 },
  { Resource::madera, 0 },
  { Resource::trigo, 0 }
};

Inventory::Inventory()
    : resources(resources_stock) {}

Inventory::~Inventory() {}

void Inventory::add(const Resource resource) {
  this->resources[resource]++;
}

int Inventory::remaining_quantity(const Resource resource) {
  return this->resources.find(resource)->second;
}

void Inventory::retrieve_resources(std::map<Resource, int> req) {
  std::map<Resource, int>::iterator it = req.begin();
  // Iterate over the map using Iterator till end.
  while (it != req.end())
  {
    const Resource resource = it->first;
    const int required_ammount = it->second;
    this->resources[resource] -= required_ammount;
    it++;
  }
}

bool Inventory::has_resources(std::map<Resource, int> req) {
  std::map<Resource, int>::iterator it = req.begin();
  // Iterate over the map using Iterator till end.
  while (it != req.end())
  {
    const Resource resource = it->first;
    const int required_ammount = it->second;
    const int current_ammount = this->resources.find(resource)->second;
    if (required_ammount > current_ammount) {
      return false;
    }
    it++;
  }
  return true;
}
