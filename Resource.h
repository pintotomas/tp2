#ifndef RESOURCE_H
#define RESOURCE_H

#define TRIGO "trigo"
#define MADERA "madera"
#define CARBON "carbon"
#define HIERRO "hierro"
#include <iostream>
enum class Resource { trigo, madera, carbon, hierro };

inline const char* to_string(Resource resource) {
  switch (resource) {
    case Resource::trigo:
      return TRIGO;
    case Resource::madera:
      return MADERA;
    case Resource::carbon:
      return CARBON;
    case Resource::hierro:
      return HIERRO;
    default:
      return "";
  }
}

#endif //RESOURCE_H
