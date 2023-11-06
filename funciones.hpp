#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;

struct infoMenu{
    int nroPlato;
    char nombre[20];
    float precio;
    char descripcion[40];
};

struct NodoMenu{
    infoMenu info;
    NodoMenu* sgte;
};

void agrearPlatoAArchivo(infoMenu plato, const char* nombreArchivo);
void cargarDatosDePruebaEnArchivo(const char* nombreArchivo);
void traerDatosDeArchivo(NodoMenu* &lista, const char* nombreArchivo);
void actualizarArchivo(NodoMenu* lista, const char* nombreArchivo);



NodoMenu* insertarOrdenado(NodoMenu* &lista, infoMenu v);
void mostrarMenu(NodoMenu* lista);
bool modificarMenu(NodoMenu* &lista, int nroPlato);
void eliminarMenu(NodoMenu* &lista, infoMenu v);


