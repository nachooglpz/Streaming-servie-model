#ifndef PELICULA_H
#define PELICULA_H

#include "video.h"

#include <iostream>
using namespace std;

class Pelicula : public Video {
public:
  Pelicula(string, string, string, double);
  virtual ~Pelicula();

private:
};

#endif