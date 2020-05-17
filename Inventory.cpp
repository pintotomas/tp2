#include "Inventory.h"
#include <string>
#include <map>

std::map<Resource, int > resources_stock =  {
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

int Inventory::remaining_quantity(Resource resource) {
  return this->resources.find(resource)->second;
}

void Inventory::retrieve_resources(std::map<Resource, int> req) {
  std::map<Resource, int>::iterator it = req.begin();
  // Iterate over the map using Iterator till end.
  while (it != req.end())
  {
    Resource resource = it->first;
    int required_ammount = it->second;
    this->resources[resource] -= required_ammount;
    it++;
  }
}

bool Inventory::has_resources(std::map<Resource, int> req) {
  std::map<Resource, int>::iterator it = req.begin();
  // Iterate over the map using Iterator till end.
  while (it != req.end())
  {
    Resource resource = it->first;
    int required_ammount = it->second;
    int current_ammount = this->resources.find(resource)->second;
    if (required_ammount > current_ammount) {
      //std::cout << "Cant satisfy, ammount needed for " << to_string(resource) << "is " << required_ammount << "but there only is" << current_ammount << std::endl;
      return false;
    }
    it++;
  }
  //std::cout << "CAN SATISFY!!!!" << std::endl;
  return true;
}