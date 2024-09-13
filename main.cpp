#include "episodio.h"
#include "pelicula.h"
#include "serie.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void importarDatos(vector<Serie> &series, vector<Pelicula> &peliculas);
void videos_calif_genre(vector<Serie> &series, vector<Pelicula> &peliculas);
void series_episodios_calif(vector<Serie> &series);
void peliculas_calif(vector<Pelicula> &peliculas);
void sobreescribirDatos(vector<Serie> &series, vector<Pelicula> &peliculas);
void calificarVideo(vector<Pelicula> &peliculas, vector<Serie> &series);
void mostrarCalifs(vector<Pelicula> &peliculas, vector<Serie> &series);
bool verificador=false;
bool *ptR=&verificador;

int main() {
  vector<Serie> *series = new vector<Serie>;
  vector<Pelicula> *peliculas = new vector<Pelicula>;

  int opcion = -1;
  while (opcion != 0) {
    cout << "-----------MENU-----------" << endl;
    cout << "Ingrese la opcion que desea ejecutar: " << endl;
    cout << "1. Cargar archivo de datos" << endl;
    cout << "2. Mostrar los videos en general con una cierta calificacion o de un cierto genero "<< endl;
    cout << "3. Mostrar los episodios de una determinada serie con una calificaion determinada"<< endl;
    cout << "4. Mostrar las peliculas con cierta calificacion" << endl;
    cout << "5. Calificar un video" << endl;
    cout << "6. Mostrar registros calificaciones" << endl;
    cout << "0. Salir" << endl;
    cin >> opcion;
    if(*ptR==false && opcion!=0 && opcion!=1){
      opcion=-1;
    }
    switch (opcion) {
    case 1: {
      importarDatos(*series, *peliculas);
      break;
    }
    case 2: {
      videos_calif_genre(*series, *peliculas);
      break;
    }
    case 3: {
      series_episodios_calif(*series);
      break;
    }
    case 4: {
      peliculas_calif(*peliculas);
      break;
    }
    case 5: {
      calificarVideo(*peliculas,*series);
      break;
    }
    case 6: {
      mostrarCalifs(*peliculas,*series);
      break;
    }
    case 0: {
      sobreescribirDatos(*series, *peliculas);
      cout << "Saliendo..." << endl;
      break;
    }
    default: {
      cout << "Opcion invalida" << endl;
      cout<<endl;
      break;
    }
    }
  }
  return 0;
}

// Sube los datos del documento .txt a los vectores de películas y series
void importarDatos(vector<Serie> &series, vector<Pelicula> &peliculas) {
  ifstream archivo;
  string cadena;
  string nombreArchivo = "./peliculas_series.txt";

  archivo.open(nombreArchivo, ios::in);
  if (archivo.fail()) {
    cout << "El archivo no se pudo abrir" << endl;
    exit(1);
  }else{
    *ptR=true;
    cout<<"El archivo fue cargado correctamente"<<endl;
    cout<<endl;
  }

  // Comienza a leer el archivo
  while (getline(archivo, cadena)) {
    // Si la línea es de película
    if (cadena[0] == 'P') {
      // Separa la información de la película
      string id, nombre, genero, duracion;
      vector<int> calificaciones;

      // Utiliza una expresión regular para dividir la línea
      regex reg(R"((\w+)\s+'([^']+)'\s+'([^']+)'\s+(\d+)\s+\(([^)]+)\))");
      smatch match;

      if (regex_search(cadena, match, reg)) {
        id = match[1];
        nombre = match[2];
        genero = match[3];
        duracion = match[4];

        string calificaciones_str = match[5];
        stringstream ss(calificaciones_str);
        string calificacion;

        // Divide las calificaciones por comas
        while (getline(ss, calificacion, ',')) {
          calificaciones.push_back(stoi(calificacion));
        }

        // Crea una instancia de Película y la agrega al vector de película
        Pelicula p(id, nombre, genero, stod(duracion));
        p.setCalificacion(calificaciones);
        peliculas.push_back(p);
      }
    } else if (cadena[0] == 'S') { // Si la línea es de serie
      // Separa la información de la serie
      string id, nombre, genero, duracion, episodio, temporada, titulo;
      vector<int> calificaciones;

      // Utiliza una expresión regular para dividir la línea
      regex reg(
          R"((\w+)\s+'([^']+)'\s+'([^']+)'\s+(\d+)\s+(\d+)\s+(\d+)\s+'([^']+)'\s+\(([^)]+)\))");
      smatch match;

      if (regex_search(cadena, match, reg)) {
        id = match[1];
        nombre = match[2];
        genero = match[3];
        duracion = match[4];
        temporada = match[5];
        episodio = match[6];
        titulo = match[7];

        string calificaciones_str = match[8];
        stringstream ss(calificaciones_str);
        string calificacion;

        // Divide las calificaciones por comas
        while (getline(ss, calificacion, ',')) {
          calificaciones.push_back(stoi(calificacion));
        }

        // Crea una instancia de Episodio
        Episodio e(id, nombre, genero, stod(duracion),
                   stoi(episodio), stoi(temporada), titulo);
        e.setCalificacion(calificaciones);

        // Revisa si el ID de serie ya existe en el vector series
        string idSerie =
            id.substr(0, 2); // Cambia para obtener los primeros tres caracteres
        bool existe = false;
        for (Serie &serie : series) {
          if (serie.getId() == idSerie) {
            serie.agregarEpisodio(e);
            existe = true;
            break;
          }
        }
        // Si el ID de serie no existe en el vector series, crea una nueva
        if (!existe) {
          Serie s(idSerie, nombre);
          s.agregarEpisodio(e);
          series.push_back(s);
        }
      }
    } else {
      cout << "Error: linea no es serie ni pelicula" << endl;
    }
  }
  archivo.close();
}

void videos_calif_genre(vector<Serie> &series, vector<Pelicula> &peliculas) {
  cout << "¿Deseas buscar por calificacion(1) o por genero(2)?" << endl;
  int r;
  cin >> r;
  if (r == 1) {
    cout << "Ingrese la calificacion deseada" << endl;
    int calif;
    cin >> calif;
    while (calif<0 || calif >5){//Validar calif correctas. 
      cout<<("Opcion invalida. Ingresa una calificacion entre 1 y 5: ");
      cin>>calif; 
    }
    cout<<"PELICULAS"<<endl;
    for (Pelicula &pelicula : peliculas) {
      if (pelicula.getCalificacion() >= calif) {
        pelicula.mostrar();
      }
  
    }
    cout<<"SERIES"<<endl;
    for (Serie &serie : series) {
      if (serie.getCalificacion() >= calif) {
        serie.mostrar();
      }
    }
  } else if (r == 2) {
    cout << "Ingrese el genero deseado (Accion, Aventura, Comedia o Drama)"
         << endl;
    string genero_usuario;
    cin >> genero_usuario; //Podria convertirlo a minusculas 
    while (genero_usuario != "Accion" && genero_usuario != "Aventura" &&
           genero_usuario != "Comedia" && genero_usuario != "Drama"){//Validar calif correctas. 
      cout<<("Opcion invalida. Ingresa un genero valido.");
      cin>>genero_usuario; 
    }
    cout<<"PELICULAS"<<endl; 
    for (Pelicula &pelicula : peliculas) {
      if (pelicula.getGenero() == genero_usuario) {
        pelicula.mostrar(); 
      }
    }
    cout<<"SERIES"<<endl; 
    for (Serie &serie : series) {
      if (serie.getGenero() == genero_usuario) {
        serie.mostrar();
      }
      
    }

  } else {
    cout << "Opcion no valida" << endl;
  }
}

void series_episodios_calif(vector<Serie> &series) {
  cout << "Seleccione la serie a buscar: " << endl;
  // imprimo un pequeño menu para que el usuario pueda seleccionar la serie
  int cont = 1;
  for (Serie &serie : series) {
    cout << cont <<". "<< serie.getNombre() << endl;
    cont += 1;
  }
  // Se ingresa la opción del usuario, que además represeta mi posición en el
  // vector
  int opc;
  cin >> opc;
  while (opc>cont || opc<0){//Validar opc correctas. 
      cout<<("Opcion invalida. Ingresa un numero de la lista: ");
      cin>>opc; 
    }
  string nombre;
  nombre = series[opc - 1].getNombre();
  cout << "Ingrese la calificacion deseada a buscar: " << endl;
  int calif;
  cin >> calif;
  while (calif<0 || calif >5){//Validar calif correctas. 
      cout<<("Opcion invalida. Ingresa una calificacion entre 1 y 5: ");
      cin>>calif; 
    }
  vector<Episodio> episodios = series[opc - 1].getEpisodios();
  bool v; 
  v=false; 
  for (Episodio &episodio : episodios) { 
    if (episodio.getCalificacion() >= calif) {
      episodio.mostrar(); 
      v=true;
    }
  }
  if (v==false){
    cout<<"No hay episodios con calificacion de "<<calif<<endl; 
  }
}

void peliculas_calif(vector<Pelicula> &peliculas){
  cout << "Ingrese la calificacion deseada a buscar: " << endl;
  int calif; 
  cin>>calif; 
  while (calif<0 || calif >5){//Validar calif correctas. 
      cout<<("Opcion invalida. Ingresa una calificacion entre 1 y 5: ");
      cin>>calif; 
    }
  for (Pelicula &pelicula : peliculas){
    if (pelicula.getCalificacion() >= calif){
      pelicula.mostrar(); 
    }
  }
}

void sobreescribirDatos(vector<Serie> &series, vector<Pelicula> &peliculas)
{
  if (series.empty() && peliculas.empty()){
    return;
  }
  ofstream archivo;
  archivo.open("peliculas_series.txt", ios::out);

  if(archivo.fail()){
        cout << "El archivo no se pudo abrir" << endl;
        exit(2);
    }

      // Imprime los datos de cada película
      for (Pelicula &pelicula : peliculas){
        archivo << pelicula.getId() << " '" << pelicula.getNombre() << "' '" << pelicula.getGenero() << "' " << pelicula.getDuracion() << " (";

        // Itera por las calificaciones para imprimirlas
        vector<int> calis = pelicula.getCalificaciones();
        for (int i = 0; i < calis.size() - 1; i++){
          archivo << calis[i] << ",";
        }
        archivo << calis[calis.size() - 1] << ")" << endl; // Imprime la útlima calificación
      }

      // Imprime los datos de cada serie
      for (Serie &serie : series){
        vector<Episodio> episodios = serie.getEpisodios(); // Recibe los episodios de cada serie

        for (Episodio &episodio : episodios){
          // Imprime los datos del episodio
          archivo << episodio.getId() << " '" << episodio.getNombre() << "' '" << episodio.getGenero() << "' " << episodio.getDuracion() << " " << episodio.getTemporada() << " " << episodio.getEpisodio() << " '" << episodio.getTitulo() << "' ("; 
          
          // Itera por las calificaciones para imprimirlas
          vector<int> calis = episodio.getCalificaciones();
          for (int i = 0; i < calis.size() - 1; i++){
            archivo << calis[i] << ",";
          }
          archivo << calis[calis.size() - 1] << ")" << endl; // Imprime la útlima calificación
        }
      }

      // Finaliza el proceso
      archivo.close();
}

void calificarVideo(vector<Pelicula> &peliculas,vector<Serie> &series){
  int caso=0;
  while(caso!=3){
    cout<<"Calificar... opciones:"<<endl;
    cout<<"  1. Pelicula"<<endl;
    cout<<"  2. Serie"<<endl;
    cout<<"  3. Salir"<<endl;
    cin>>caso;
    if(caso==1 || caso==2){
      string id;
      int calif;
      int verif=0;
      cout<<"-CALIFICAR VIDEO-"<<endl;
      cout<<"Lista de videos: "<<endl;
      cout<<"  ID  -  Nombre"<<endl;
      if(caso==1){
        for(Pelicula &pelicula:peliculas){
          cout<<"  "<<pelicula.getId()<<"  -  "<<pelicula.getNombre()<<endl;
        }
      }else{
        for(Serie &serie:series){
          cout<<"  "<<serie.getId()<<"  -  "<<serie.getNombre()<<endl;
        }
      }
      cout<<"Selecciona ID del video a calificar: ";
      cin>>id;
      cout<<endl;
      if(caso==1){
        for(Pelicula &pelicula:peliculas){
          if(pelicula.getId()==id){
            verif=1;
            cout<<"Okay... "<<pelicula.getNombre()<<endl;
            cout<<"Insertar calificacion del 1 al 5: ";
            cin>>calif;
            if(calif>0 && calif<6){
              pelicula+(calif);
              cout<<endl;
              cout<<"Calificacion actualizada"<<endl;
            }else{
              cout<<"Calificacion no valida"<<endl;
            }
          }
        }
      }else{
        string idE;
        for(Serie &serie:series){
          if(serie.getId()==id){
            cout<<"Okay... "<<serie.getNombre()<<endl;
            vector<Episodio> episodios = serie.getEpisodios();
            cout<<"Episodios: "<<endl;
            for(Episodio &episodio:episodios){
              cout<<"  "<<episodio.getId()<<"  -  "<<episodio.getTitulo()<<endl;
            }
            cout<<"Selecciona ID del episodio a calificar: ";
            cin>>idE;
            for(Episodio &episodio:episodios){
              if(episodio.getId()==idE){
                verif=1;
                cout<<"Okay... "<<episodio.getTitulo()<<endl;
                cout<<"Insertar calificacion del 1 al 5: ";
                cin>>calif;
                if(calif>0 && calif<6){
                  episodio+(calif);
                  serie.setEpisodios(episodios);
                  cout<<endl;
                  cout<<"Calificacion actualizada"<<endl;
                }else{
                  cout<<"Calificacion no valida"<<endl;
                }
              }
            }
          }
        } 
      }
      if(verif==0){
        cout<<"No existe el video"<<endl;
      }
    }else if(caso==3){
      cout<<"Saliendo..."<<endl;
    }else{
      cout<<"Opcion no valida"<<endl;
      cout<<"Intente de nuevo"<<endl;
    }
    cout<<endl;
  }
}

void mostrarCalifs(vector<Pelicula> &peliculas, vector<Serie> &series){
int caso=0;

while(caso!=3){ 
  int tamano=0;
  int cont=0;
  cout<<"Mostrar calificaciones... opciones:"<<endl;
  cout<<"  1. Pelicula"<<endl;
  cout<<"  2. Serie"<<endl;
  cout<<"  3. Salir"<<endl;
  cin>>caso;
  if (caso == 1){
    cout << "Lista de peliculas: " << endl;
    cout << "  Nombre  -  Calificaiones" << endl;

    for (Pelicula &pelicula:peliculas){
      cout << "  " << pelicula.getNombre() << "  -  (";
      for (int i = 0; i < pelicula.getCalificaciones().size()-1; i++){
        cout << pelicula.getCalificaciones()[i] << ",";
      }
      cout << pelicula.getCalificaciones()[pelicula.getCalificaciones().size()-1] << ")" << endl;
    }
  }

    else if (caso == 2){
      cout << "Lista de series: " << endl;
      for (Serie &serie : series){
        cout << "  " << serie.getNombre() << endl;

        for (Episodio &episodio : serie.getEpisodios()){
          cout << "    " << episodio.getTitulo() << "  -  (";
          for (int i = 0; i < episodio.getCalificaciones().size()-1; i++){
            cout << episodio.getCalificaciones()[i] << ",";
          }
          cout << episodio.getCalificaciones()[episodio.getCalificaciones().size()-1] << ")" << endl;
        }
      }
    }
  else if(caso==3){
    cout<<"Saliendo..."<<endl;
  }else{
    cout<<"Opcion no valida"<<endl;
  }
}
}