#include "funciones.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <limits>
using namespace std;

NodoMenu* buscar(NodoMenu* lista, infoMenu v){
    while(lista != NULL && lista->info.nroPlato != v.nroPlato){
        lista = lista->sgte;
    }
    return lista;
}

NodoMenu* buscaEInsertaOrdenado(NodoMenu* &lista, infoMenu v, bool &enc){
    NodoMenu* buscado = buscar(lista, v);
    if(buscado == NULL){
        enc = false;
        buscado = insertarOrdenado(lista, v);
    } else{
        enc = true;
    }
    return buscado;
}

// Agrega un plato a un archivo
void agrearPlatoAArchivo(infoMenu platoMenu, const char* nombreArchivo){
    FILE* arch = fopen(nombreArchivo, "ab");
    fwrite(&platoMenu, sizeof(infoMenu), 1, arch);
    fclose(arch);
}

void cargarDatosDePruebaEnArchivo(const char* nombreArchivo){
    infoMenu platoMenu;

    platoMenu.nroPlato = 3;
    strcpy(platoMenu.nombre, "Rattatouile");
    strcpy(platoMenu.descripcion, "Pollo al horno con papas");
    platoMenu.precio = 100.0;

    agrearPlatoAArchivo(platoMenu, nombreArchivo);

    platoMenu.nroPlato = 2;
    strcpy(platoMenu.nombre, "Algortimos");
    strcpy(platoMenu.descripcion, "Fideos Spagetti con tuco");
    platoMenu.precio = 150.0;

    agrearPlatoAArchivo(platoMenu, nombreArchivo);

    platoMenu.nroPlato = 8;
    strcpy(platoMenu.nombre, "Carmen");
    strcpy(platoMenu.descripcion, "Ravioles con tuco");
    platoMenu.precio = 50.0;

    agrearPlatoAArchivo(platoMenu, nombreArchivo);
}

void traerDatosDeArchivo(NodoMenu* &lista, const char* nombreArchivo){
    infoMenu platoMenu;
    FILE* arch = fopen(nombreArchivo, "rb");
    rewind(arch);
    fread(&platoMenu, sizeof(infoMenu), 1, arch);
    while(!feof(arch)){
        insertarOrdenado(lista,platoMenu);
        fread(&platoMenu, sizeof(infoMenu), 1, arch);
    }
    fclose(arch);
}

void actualizarArchivo(NodoMenu* lista, const char* nombreArchivo){
    FILE* arch = fopen(nombreArchivo, "wb");
    while(lista != NULL){
        fwrite(&lista->info, sizeof(infoMenu), 1, arch);
        lista = lista->sgte;
    }
    fclose(arch);
}



NodoMenu* insertarOrdenado(NodoMenu* &lista, infoMenu v){
    NodoMenu* nuevo = new NodoMenu();
    nuevo->info = v;
    nuevo->sgte = NULL;

    NodoMenu* aux = lista;
    NodoMenu* ant = NULL;

    while(aux != NULL && aux->info.nroPlato <= v.nroPlato){
        ant = aux;
        aux = aux->sgte;
    }

    if(ant == NULL){
        lista = nuevo;
    } else{
        ant->sgte = nuevo;
    }

    nuevo->sgte = aux;
    return nuevo;
}

void mostrarMenu(NodoMenu* lista){
    cout << "-------------------- Platos del menu --------------------" << endl;
    while(lista != NULL){
        cout << "=========================================================" << endl;
        cout << "Plato numero: " << lista->info.nroPlato << endl;
        cout << "Nombre: " << lista->info.nombre << endl;
        cout << "Descripcion: " << lista->info.descripcion << endl;
        cout << "Precio: $" << lista->info.precio << endl;
        cout << "=========================================================" << endl;
        lista = lista->sgte;
    }
}

bool modificarMenu(NodoMenu* &lista, int nroPlato){
    bool modificado = false;
    infoMenu menu;
    menu.nroPlato = nroPlato;
    NodoMenu* buscado = buscar(lista, menu);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(buscado){
        cout << "Plato numero " << nroPlato << " seleccionado:" << endl;
        cout << "Nombre del plato (" << buscado->info.nombre << "): ";
        cin.getline(buscado->info.nombre, sizeof(buscado->info.nombre));
        cout << "Descripcion del plato (" << buscado->info.descripcion << "): ";
        cin.getline(buscado->info.descripcion, sizeof(buscado->info.descripcion));
        cout << "Precio del plato (" << buscado->info.precio << "): ";
        cin >> buscado->info.precio;
        modificado = true;
    } else{
        cout << "No existe el plato seleccionado. Porfavor indique uno valido." << endl;
    }
    return modificado;
}

void eliminarMenu(NodoMenu* &lista, infoMenu v){ // Elimina el nodo que tenga el valor 'v'
    NodoMenu* aux = lista;
    NodoMenu* ant = NULL; // Puntero para guardar la referencia al nodo anterior
    while(aux != NULL && aux->info.nroPlato != v.nroPlato){ // Recorro hasta el final de la lista o hasta donde encuentre el valor
        ant = aux;
        aux = aux->sgte; // Avanzo un nodo
    }
    if(ant != NULL){
        ant->sgte = aux->sgte; // Referencia el nodo anterior al que se elimina con el que seguia
    } else{ // Si el anterior es NULL significa que el nodo a eliminar es el primero
        lista = aux->sgte;
    }
    delete aux;
}
