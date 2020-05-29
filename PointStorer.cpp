#include "PointStorer.h"

PointStorer::PointStorer()
    : points_accumulated(0), mutex() {}

PointStorer::~PointStorer() {}

void PointStorer::add_points(const int &points) {
  std::unique_lock<std::mutex> lock(mutex);
  points_accumulated += points;
} 

const int PointStorer::get_points() {
  std::unique_lock<std::mutex> lock(mutex);
  return std::move(points_accumulated);
} 
