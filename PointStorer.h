#ifndef POINT_STORER_H
#define POINT_STORER_H

#include <condition_variable>
#include <mutex>

class PointStorer {
 private:
  int points_accumulated;
  std::mutex mutex;

 protected:
 public:
  PointStorer();
  ~PointStorer();
  void add_points(const int points);
  const int get_points();
  //Elimino constructor por copia y por movimiento
  PointStorer(const PointStorer &) = delete;
  PointStorer &operator=(const PointStorer &) = delete;
};

#endif //BLOCKING_QUEUE_RESOURCE_H
