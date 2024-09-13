#include "episodio.h"
#include <iostream>
using namespace std;

Episodio::Episodio(string ID, string nombre, string genero, double duracion,
                   int episodio, int temporada, string titulo)
    : Video(ID, nombre, genero, duracion) {
  this->episodio = episodio;
  this->temporada = temporada;
  this->titulo = titulo;
}

Episodio::~Episodio() {}

// Métodos accesores

int Episodio::getTemporada() { return temporada; }
int Episodio::getEpisodio() { return episodio; }
string Episodio::getTitulo() { return titulo; }

// Métodos especializados

void Episodio::mostrar(){
  cout<<"---------------------"<<endl; 
  cout<<"No. Episodio: "<<episodio<<endl;
  cout<<"Temporada: "<<temporada<<endl;
  cout<<"Titulo: "<<titulo<<endl;  
  cout<<"Calificacion: "<<getCalificacion()<<endl;            
}