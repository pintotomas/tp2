#include "PointStorer.h"

PointStorer::PointStorer()
    : points_accumulated(0), mutex(), cv() {}

PointStorer::~PointStorer() {}

void PointStorer::add_points(const int points) {
  std::unique_lock<std::mutex> lock(mutex);
  this->points_accumulated += points;
  cv.notify_all();
} 

const int PointStorer::get_points() {
  std::unique_lock<std::mutex> lock(mutex);
  cv.notify_all();
  return this->points_accumulated;
} 
