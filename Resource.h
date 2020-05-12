#ifndef RESOURCE_H
#define RESOURCE_H

#define TRIGO 1
#define MADERA 2
#define CARBON 3
#define HIERRO 4

enum class Resource { trigo, madera, carbon, hierro };

inline const int toInt(Resource resource) {
  switch (resource) {
    case Resource::trigo:
      return TRIGO;
    case Resource::madera:
      return MADERA;
    case Resource::carbon:
      return CARBON;
    case Resource::hierro:
      return HIERRO;
  }
}

#endif //RESOURCE_H
