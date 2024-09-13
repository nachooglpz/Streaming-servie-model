#include "serie.h"
#include <iostream>
#include <vector>
using namespace std;

Serie::Serie(string id, string nombre) {
  this->id = id;
  this->nombre = nombre;
}

Serie::~Serie() {}

// Métodos accesores

string Serie::getId() { return id; }
string Serie::getNombre() { return nombre; }
int Serie::getCalificacion() {
  for (Episodio &episodio : episodios) {
    calificacion = calificacion + episodio.getCalificacion();
  }
  return calificacion / episodios.size();
}
string Serie::getGenero() { return episodios[0].getGenero(); }
vector<Episodio> Serie::getEpisodios(){
    return episodios;
}
void Serie::setEpisodios(vector<Episodio> nuevos){
    episodios=nuevos;
}

// Métodos modificadores

void Serie::setId(string id) { this->id = id; }

// Métodos especializados

void Serie::agregarEpisodio(Episodio e) { episodios.push_back(e); }
void Serie::mostrar(){ 
  cout<<"---------------------"<<endl; 
  cout<<"ID: "<<id<<endl; 
  cout<<"Nombre: "<<nombre<<endl;
  cout<<"Genero: "<<episodios[0].getGenero()<<endl;
}