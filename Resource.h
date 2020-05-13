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
      return "trigo";
    case Resource::madera:
      return "madera";
    case Resource::carbon:
      return "carbon";
    case Resource::hierro:
      return "hierro";
    default:
      return "default";
  }
}

#endif //RESOURCE_H
