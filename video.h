#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <vector>
using namespace std;

class Video {
private:
  string nombre, genero;
  double duracion;
  vector<int> calificaciones;
  string ID;

public:
  Video(string, string, string, double);

  void operator+(int);
  virtual void setCalificacion(vector<int>);

  virtual void mostrar(); 

  virtual ~Video();

  // Métodos accesores
  string getId();
  int getCalificacion();
  vector<int> getCalificaciones();
  string getNombre();
  string getGenero();
  double getDuracion();

  //otros
  //int validar(int calif); 
  //string validar(string genero);
};

#endif // VIDEO_H