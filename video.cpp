#include "video.h"
#include <iostream>
#include <vector>
using namespace std;

Video::Video(string id, string nombre, string genero, double duracion) {
  this->ID = id;
  this->nombre = nombre;
  this->genero = genero;
  this->duracion = duracion;
}

// Métodos modificadores

void Video::operator+(int calificacion) {
  calificaciones.push_back(calificacion);
}

void Video::setCalificacion(vector<int> calificaciones) {
  for (int i = 0; i < calificaciones.size(); i++) {
    this->calificaciones.push_back(calificaciones[i]);
  }
}

// Métodos accesores

string Video::getId() { return ID; }

// Devuelve el promedio de las calificaciones
int Video::getCalificacion() {
  double promedio = 0;
  for (int i = 0; i < calificaciones.size(); i++) {
    promedio = promedio + calificaciones[i];
  }
  return promedio / calificaciones.size();
}

string Video::getNombre() { return nombre; }

string Video::getGenero() { return genero; }

double Video::getDuracion() { return duracion; }

vector<int> Video::getCalificaciones(){ return calificaciones; }

Video::~Video() {}

//Metodos especializados 
void Video::mostrar() {
  cout<<"---------------------"<<endl; 
  cout << "ID: " << ID << endl;
  cout << "Nombre: " << nombre << endl;
  cout << "Genero: " << genero << endl;
  cout << "Duracion: " << duracion << endl;
  cout<< "Calificacion: "<<getCalificacion()<<endl; 
}

