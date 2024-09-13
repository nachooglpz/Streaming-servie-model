#include "pelicula.h"
#include <iostream>
using namespace std;

Pelicula::Pelicula(string ID, string nombre, string genero, double duracion)
    : Video(ID, nombre, genero, duracion) {}

Pelicula::~Pelicula() {}