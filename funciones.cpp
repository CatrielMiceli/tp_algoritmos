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

NodoCliente* buscarCliente(NodoCliente* lista, infoCliente v){
    while(lista != NULL && lista->info.id != v.id){
        lista = lista->sgte;
    }
    return lista;
}

// ----------- Menejo de archivo MENU (menu.dat) -----------
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

// ----------- CRUD MENU -----------

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



// ----------- Manejo de archivo CLIENTES (clientes.dat) -----------
void agrearClienteAArchivo(infoCliente cliente, const char* nombreArchivo){
    FILE* arch = fopen(nombreArchivo, "ab");
    fwrite(&cliente, sizeof(infoCliente), 1, arch);
    fclose(arch);
}

void cargarClienteDePruebaEnArchivo(const char* nombreArchivo){
    infoCliente cliente;

    cliente.id = 3;
    strcpy(cliente.nombre, "Catriel");
    strcpy(cliente.direccion, "9 de Julio 5059");
    cliente.telefono = 47683371;
    //cliente.pedidos

    agrearClienteAArchivo(cliente, nombreArchivo);

    cliente.id = 2;
    strcpy(cliente.nombre, "Carlos");
    strcpy(cliente.direccion, "Rocket 567");
    cliente.telefono = 11223344;
    //cliente.pedidos

    agrearClienteAArchivo(cliente, nombreArchivo);

    cliente.id = 8;
    strcpy(cliente.nombre, "Gimena");
    strcpy(cliente.direccion, "Malabia 5687");
    cliente.telefono = 12345678;
    //cliente.pedidos

    agrearClienteAArchivo(cliente, nombreArchivo);
}

void traerClientesDeArchivo(NodoCliente* &lista, const char* nombreArchivo){
    infoCliente cliente;
    FILE* arch = fopen(nombreArchivo, "rb");
    rewind(arch);
    fread(&cliente, sizeof(infoCliente), 1, arch);
    while(!feof(arch)){
        insertarOrdenadoCliente(lista,cliente);
        fread(&cliente, sizeof(infoCliente), 1, arch);
    }
    fclose(arch);
}

void actualizarArchivoClientes(NodoCliente* lista, const char* nombreArchivo){
    FILE* arch = fopen(nombreArchivo, "wb");
    while(lista != NULL){
        fwrite(&lista->info, sizeof(infoCliente), 1, arch);
        lista = lista->sgte;
    }
    fclose(arch);
}

// ----------- CRUD CLIENTES -----------

NodoCliente* insertarOrdenadoCliente(NodoCliente* &lista, infoCliente v){
    NodoCliente* nuevo = new NodoCliente();
    nuevo->info = v;
    nuevo->sgte = NULL;

    NodoCliente* aux = lista;
    NodoCliente* ant = NULL;

    while(aux != NULL && aux->info.id <= v.id){
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

void mostrarClientes(NodoCliente* lista){
    cout << "-------------------- Clientes --------------------" << endl;
    while(lista != NULL){
        cout << "=========================================================" << endl;
        cout << "ID: " << lista->info.id << endl;
        cout << "Nombre: " << lista->info.nombre << endl;
        cout << "Direccion: " << lista->info.direccion << endl;
        cout << "Telefono: " << lista->info.telefono << endl;
        //cout << "Pedidos: " << lista->info.precio << endl;
        cout << "=========================================================" << endl;
        lista = lista->sgte;
    }
}

bool modificarCliente(NodoCliente* &lista, int idCliente){
    bool modificado = false;
    infoCliente cliente;
    cliente.id = idCliente;
    NodoCliente* buscado = buscarCliente(lista, cliente);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(buscado){
        cout << "ID " << idCliente << " seleccionado:" << endl;
        cout << "Nombre del cliente (" << buscado->info.nombre << "): ";
        cin.getline(buscado->info.nombre, sizeof(buscado->info.nombre));
        cout << "Direccion del cliente (" << buscado->info.direccion << "): ";
        cin.getline(buscado->info.direccion, sizeof(buscado->info.direccion));
        cout << "Telefono del cliente (" << buscado->info.telefono << "): ";
        cin >> buscado->info.telefono;
        modificado = true;
    } else{
        cout << "No existe el cliente seleccionado. Porfavor indique uno valido." << endl;
    }
    return modificado;
}

void eliminarCliente(NodoCliente* &lista, infoCliente v){ // Elimina el nodo que tenga el valor 'v'
    NodoCliente* aux = lista;
    NodoCliente* ant = NULL; // Puntero para guardar la referencia al nodo anterior
    while(aux != NULL && aux->info.id != v.id){ // Recorro hasta el final de la lista o hasta donde encuentre el valor
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



// ----------- GESTION PEDIDOS -----------

void push(NodoPedidos* &pila, infoPedidos v){
    NodoPedidos* nuevo = new NodoPedidos();
    nuevo->info = v;
    nuevo->sgte = pila;
    pila = nuevo;
}

infoPedidos pop(NodoPedidos* &pila){
    infoPedidos ret = pila->info;
    NodoPedidos* aux = pila;
    pila = aux->sgte;
    delete aux;
    return ret;
}

void encolar(NodoPedidos* &colafte, NodoPedidos* &colafin, infoPedidos v){
    NodoPedidos* nuevo = new NodoPedidos();
    nuevo->info = v;
    nuevo->sgte = NULL;
    if(colafte == NULL){
        colafte = nuevo;
    } else{
        colafin->sgte = nuevo;
    }
    colafin = nuevo;
}

infoPedidos desencolar(NodoPedidos* &colafte, NodoPedidos* &colafin){
    infoPedidos ret = colafte->info;
    NodoPedidos* aux = colafte;
    colafte = colafte->sgte;
    if(colafte == NULL){
        colafin = NULL;
    }
    delete aux;
    return ret;
}

void mostrarPedidosPendientes(NodoPedidos* &colafte, NodoPedidos* &colafin){
    NodoPedidos* colafteAux = NULL;
    NodoPedidos* colafinAux = NULL;
    infoPedidos pedido;
    cout << "-------------------- Pedidos pendientes --------------------" << endl;
    while(colafte != NULL){
        pedido = desencolar(colafte, colafin);
        encolar(colafteAux, colafinAux, pedido);
        cout << "=========================================================" << endl;
        cout << "ID del pedido: " << pedido.id << endl;
        cout << "ID del cliente: " << pedido.idCliente << endl;
        cout << "ID del plato: " << pedido.idPlato << endl;
        cout << "Cantidad de platos: " << pedido.cantidad << endl;
        cout << "=========================================================" << endl;
    }
    colafte = colafteAux;
    colafin = colafinAux;
}

void mostrarPedidosCompletados(NodoPedidos* &pila){
    NodoPedidos* pilaAux = NULL;
    infoPedidos pedido;
    cout << "-------------------- Pedidos Completados --------------------" << endl;
    while(pila != NULL){
        pedido = pop(pila);
        push(pilaAux, pedido);
        cout << "=========================================================" << endl;
        cout << "ID del pedido: " << pedido.id << endl;
        cout << "ID del cliente: " << pedido.idCliente << endl;
        cout << "ID del plato: " << pedido.idPlato << endl;
        cout << "Cantidad de platos: " << pedido.cantidad << endl;
        cout << "=========================================================" << endl;
    }
    while(pilaAux != NULL){
        push(pila, pop(pilaAux));
    }
}



// ----------- GESTION PEDIDOS -----------

void facturacionDePedidos(NodoPedidos* &pila, NodoCliente* listaCliente, NodoMenu* listaMenu, const char* nombreArchivo){
    NodoPedidos* pilaAux = NULL;
    infoPedidos pedido;
    infoCliente cliente;
    infoMenu plato;
    factura datos;
    float precioTotal;
    while(pila != NULL){
        pedido = pop(pila);
        push(pilaAux, pedido);
        cliente.id = pedido.idCliente;
        plato.nroPlato = pedido.idPlato;
        NodoCliente* clienteDelPedido = buscarCliente(listaCliente, cliente);
        NodoMenu* platoDelPedido = buscar(listaMenu, plato);

        strcpy(datos.nombre, clienteDelPedido->info.nombre);
        strcpy(datos.plato, platoDelPedido->info.descripcion);
        datos.cantidad = pedido.cantidad;
        datos.precio = platoDelPedido->info.precio;
        precioTotal = datos.precio * datos.cantidad;
        datos.precioTotal = precioTotal;

        // ACA GENERO EL ARCHIVO CON EL PRECIO Y LOS DATOS DEL CLIENTE
        FILE* arch = fopen(nombreArchivo, "w");
        fwrite(&datos, sizeof(factura), 1, arch);
        fclose(arch);
    }
    while(pilaAux != NULL){
        push(pila, pop(pilaAux));
    }
}

void visualizarDatosDeFacturacion(const char* nombreArchivo){
        factura datos;
        FILE* arch = fopen(nombreArchivo, "r");
        rewind(arch);
        fread(&datos, sizeof(factura), 1, arch);
        cout << "-------------------- Facturacion --------------------" << endl;
        while(!feof(arch)){
            cout << "=========================================================" << endl;
            cout << "Nombre del cliente: " << datos.nombre << endl;
            cout << "Descripcion del plato: " << datos.plato << endl;
            cout << "Cantidad de platos: " << datos.cantidad << endl;
            cout << "Precio Unitario: $" << datos.precio << endl;
            cout << "Precio Total: $" <<datos.precioTotal << endl;
            cout << "=========================================================" << endl;
            fread(&datos, sizeof(factura), 1, arch);
        }
        fclose(arch);
}