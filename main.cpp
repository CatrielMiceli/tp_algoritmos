#include "funciones.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <limits>
using namespace std;

int main(){

    NodoMenu* listaMenu = NULL;
    infoMenu platoMenu;
    int opcion, nroPlato;
    bool repetir = true, modificado;

    //cargarDatosDePruebaEnArchivo("menu.dat"); // Carga datos de prueba al archivo SE DEBE EJECUTAR UNA SOLA VEZ
    traerDatosDeArchivo(listaMenu, "menu.dat"); // Genero una lista con los datos del archivo

    do {
        cout << "-------------------- CRUD menu --------------------" << endl;
        cout << "1. Agregar un plato" << endl;
        cout << "2. Listar los platos" << endl;
        cout << "3. Modificar un plato" << endl;
        cout << "4. Eliminar un plato" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese la opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(opcion){
            case 1:
                cout << "Numero del plato: ";
                cin >> platoMenu.nroPlato;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nombre del plato: ";
                cin.getline(platoMenu.nombre, sizeof(platoMenu.nombre));
                cout << "Descripcion del plato: ";
                cin.getline(platoMenu.descripcion, sizeof(platoMenu.descripcion));
                cout << "Precio del plato: ";
                cin >> platoMenu.precio;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                insertarOrdenado(listaMenu, platoMenu);
                cout << "Plato agregado correctamente" << endl;
                actualizarArchivo(listaMenu, "menu.dat");
                break;
            case 2:
                mostrarMenu(listaMenu);
                break;
            case 3:
                do{
                    cout << "Ingrese numero de plato a modificar: ";
                    cin >> nroPlato;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    modificado = modificarMenu(listaMenu, nroPlato);
                } while(!modificado);
                cout << "Plato modificado correctamente" << endl;
                actualizarArchivo(listaMenu, "menu.dat");
                break;
            case 4:
                cout << "Ingrese numero de plato a eliminar: ";
                cin >> nroPlato;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                platoMenu.nroPlato = nroPlato;
                eliminarMenu(listaMenu, platoMenu);
                cout << "Plato eliminado correctamente" << endl;
                actualizarArchivo(listaMenu, "menu.dat");
                break;
            case 0:
                repetir = false;
                break;
            default:
                cout << "No es una opcion valida" << endl;
                break;
        }
    } while(repetir);

    return 0;
}
