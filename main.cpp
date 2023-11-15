#include "funciones.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <limits>
using namespace std;

int main(){

    int opcionGeneral;
    bool repetirInterfazGeneral = true;
    NodoMenu* listaMenu = NULL;
    NodoCliente* listaCliente = NULL;
    NodoPedidos* colaftePedidosPendientes = NULL;
    NodoPedidos* colafinPedidosPendientes = NULL;
    NodoPedidos* pilaPedidosCompletados = NULL;
    bool repetirInterfazMenu = true;
    bool repetirInterfazClientes = true;
    bool repetirInterfazPedidos = true;

    //cargarDatosDePruebaEnArchivo("menu.dat"); // Carga datos de prueba al archivo SE DEBE EJECUTAR UNA SOLA VEZ
    //cargarClienteDePruebaEnArchivo("clientes.dat"); // Carga datos de prueba al archivo SE DEBE EJECUTAR UNA SOLA VEZ

    //visualizarDatosDeFacturacion("facturacion.dat"); // FUNCION PARA PROBAR SI EL ARCHIVO FACTURACION ESTA CORRECTO

    do {
        cout << "-------------------- Sistema de Gestion de Delivery --------------------" << endl;
        cout << "1. Gestionar Menu" << endl;
        cout << "2. Gestionar Clientes" << endl;
        cout << "3. Gestionar Pedidos" << endl;
        cout << "4. Generar Facturacion" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese la opcion: ";
        cin >> opcionGeneral;
        switch(opcionGeneral){
            case 1:
                // GESTION MENU
                infoMenu platoMenu;
                int opcionMenu, nroPlato;
                bool menuModificado;

                traerDatosDeArchivo(listaMenu, "menu.dat"); // Genero una lista con los datos del archivo

                do {
                    cout << "-------------------- Gestionar menu --------------------" << endl;
                    cout << "1. Agregar un plato" << endl;
                    cout << "2. Listar los platos" << endl;
                    cout << "3. Modificar un plato" << endl;
                    cout << "4. Eliminar un plato" << endl;
                    cout << "0. Atras" << endl;
                    cout << "Ingrese la opcion: ";
                    cin >> opcionMenu;
                    switch(opcionMenu){
                        case 1:
                            cout << "Numero del plato: ";
                            cin >> platoMenu.nroPlato;
                            cout << "Nombre del plato: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.getline(platoMenu.nombre, sizeof(platoMenu.nombre));
                            cout << "Descripcion del plato: ";
                            cin.getline(platoMenu.descripcion, sizeof(platoMenu.descripcion));
                            cout << "Precio del plato: ";
                            cin >> platoMenu.precio;
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
                                menuModificado = modificarMenu(listaMenu, nroPlato);
                            } while(!menuModificado);
                            cout << "Plato modificado correctamente" << endl;
                            actualizarArchivo(listaMenu, "menu.dat");
                            break;
                        case 4:
                            cout << "Ingrese numero de plato a eliminar: ";
                            cin >> nroPlato;
                            platoMenu.nroPlato = nroPlato;
                            eliminarMenu(listaMenu, platoMenu);
                            cout << "Plato eliminado correctamente" << endl;
                            actualizarArchivo(listaMenu, "menu.dat");
                            break;
                        case 0:
                            repetirInterfazMenu = false;
                            break;
                        default:
                            cout << "No es una opcion valida" << endl;
                            break;
                    }
                } while(repetirInterfazMenu);
                break;

            case 2:
                // GESTION CLIENTES
                infoCliente cliente;
                int opcionCliente, idCliente;
                bool clienteModificado;

                traerClientesDeArchivo(listaCliente, "clientes.dat"); // Genero una lista con los clientes del archivo

                do {
                    cout << "-------------------- Gestionar clientes --------------------" << endl;
                    cout << "1. Agregar un cliente" << endl;
                    cout << "2. Listar los clientes" << endl;
                    cout << "3. Modificar un cliente" << endl;
                    cout << "4. Eliminar un cliente" << endl;
                    cout << "0. Atras" << endl;
                    cout << "Ingrese la opcion: ";
                    cin >> opcionCliente;
                    switch(opcionCliente){
                        case 1:
                            cout << "ID del cliente: ";
                            cin >> cliente.id;
                            cout << "Nombre del cliente: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.getline(cliente.nombre, sizeof(cliente.nombre));
                            cout << "Direccion del cliente: ";
                            cin.getline(cliente.direccion, sizeof(cliente.direccion));
                            cout << "Numero de telefono del cliente: ";
                            cin >> cliente.telefono;
                            insertarOrdenadoCliente(listaCliente, cliente);
                            cout << "Cliente agregado correctamente" << endl;
                            actualizarArchivoClientes(listaCliente, "clientes.dat");
                            break;
                        case 2:
                            mostrarClientes(listaCliente);
                            break;
                        case 3:
                            do{
                                cout << "Ingrese ID de cliente a modificar: ";
                                cin >> idCliente;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                clienteModificado = modificarCliente(listaCliente, idCliente);
                            } while(!clienteModificado);
                            cout << "Cliente modificado correctamente" << endl;
                            actualizarArchivoClientes(listaCliente, "clientes.dat");
                            break;
                        case 4:
                            cout << "Ingrese ID de cliente a eliminar: ";
                            cin >> idCliente;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cliente.id = idCliente;
                            eliminarCliente(listaCliente, cliente);
                            cout << "Cliente eliminado correctamente" << endl;
                            actualizarArchivoClientes(listaCliente, "clientes.dat");
                            break;
                        case 0:
                            repetirInterfazClientes = false;
                            break;
                        default:
                            cout << "No es una opcion valida" << endl;
                            break;
                    }
                } while(repetirInterfazClientes);
                break;

            case 3:
                // GESTION PEDIDOS
                infoPedidos pedidoPendiente;
                int opcionPedido;

                do {
                    cout << "-------------------- Gestionar pedidos --------------------" << endl;
                    cout << "1. Agregar un nuevo pedido" << endl;
                    cout << "2. Listar pedidos pendientes" << endl;
                    cout << "3. Listar pedidos completados" << endl;
                    cout << "4. Pasar ultimo pedido a completado" << endl;
                    cout << "0. Atras" << endl;
                    cout << "Ingrese la opcion: ";
                    cin >> opcionPedido;
                    switch(opcionPedido){
                        case 1:
                            cout << "ID pedido: ";
                            cin >> pedidoPendiente.id;
                            cout << "ID del cliente: ";
                            cin >> pedidoPendiente.idCliente;
                            cout << "ID del menu del cliente: ";
                            cin >> pedidoPendiente.idPlato;
                            cout << "Cantidad de platos: ";
                            cin >> pedidoPendiente.cantidad;
                            encolar(colaftePedidosPendientes, colafinPedidosPendientes, pedidoPendiente);
                            // AGREGAR PEDIDO AL HISTORIAL DE PEDIDOS DEL CLIENTE
                            cout << "Nuevo pedido agregado correctamente" << endl;
                            break;
                        case 2:
                            mostrarPedidosPendientes(colaftePedidosPendientes, colafinPedidosPendientes);
                            break;
                        case 3:
                            mostrarPedidosCompletados(pilaPedidosCompletados);
                            break;
                        case 4:
                            pedidoPendiente = desencolar(colaftePedidosPendientes, colafinPedidosPendientes);
                            push(pilaPedidosCompletados, pedidoPendiente);
                            cout << "Pedido marcado como completado" << endl;
                            break;
                        case 0:
                            repetirInterfazPedidos = false;
                            break;
                        default:
                            cout << "No es una opcion valida" << endl;
                            break;
                    }
                } while(repetirInterfazPedidos);
                break;

            case 4:
                facturacionDePedidos(pilaPedidosCompletados, listaCliente, listaMenu, "facturacion.dat");
                cout << "Archivo generado correctamente" << endl;
                break;

            case 0:
                repetirInterfazGeneral = false;
                break;
            default:
                cout << "No es una opcion valida" << endl;
                break;
        }
    } while(repetirInterfazGeneral);

    return 0;
}
