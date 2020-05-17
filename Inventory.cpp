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

int Inventory::get_carbon() {
  return this->resources.find(Resource::carbon)->second;
}

int Inventory::get_hierro() {
  return this->resources.find(Resource::hierro)->second;
}

int Inventory::get_trigo() {
  return this->resources.find(Resource::trigo)->second;
}

int Inventory::get_madera() {
  return this->resources.find(Resource::madera)->second;
}
//Esta funcion en vez de bool deebria devolver un int y 
// debo contemplar los 3 casos (ver notas)
//
bool Inventory::has_resources(std::map<Resource, int> req) {
  std::map<Resource, int>::iterator it = req.begin();
  // Iterate over the map using Iterator till end.
  while (it != req.end())
  {
    Resource resource = it->first;
    int required_ammount = it->second;
    int current_ammount = this->resources.find(resource)->second;
    if (required_ammount > current_ammount) {
      std::cout << "Cant satisfy, ammount needed for " << to_string(resource) << "is " << required_ammount << "but there only is" << current_ammount << std::endl;
      return false;
    }
    it++;
  }
  std::cout << "CAN SATISFY!!!!" << std::endl;
  return true;
}