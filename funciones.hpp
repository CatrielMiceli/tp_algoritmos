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

struct infoPedidos{
    int id;
    int idPlato;
    int cantidad;
    int idCliente;
};

struct NodoPedidos{
    infoPedidos info;
    NodoPedidos* sgte;
};

struct infoCliente{
    int id;
    char nombre[20];
    char direccion[40];
    int telefono;
    //NodoPedidos* pedidosAnteriores; CUANDO SE GENERA UN PEDIDO TIENE QUE MACHEAR Y GUARDARLO ACA
};

struct NodoCliente{
    infoCliente info;
    NodoCliente* sgte;
};

struct factura{
    char nombre[20];
    char plato[40];
    int cantidad;
    float precio;
    float precioTotal;
};



void agrearPlatoAArchivo(infoMenu plato, const char* nombreArchivo);
void cargarDatosDePruebaEnArchivo(const char* nombreArchivo);
void traerDatosDeArchivo(NodoMenu* &lista, const char* nombreArchivo);
void actualizarArchivo(NodoMenu* lista, const char* nombreArchivo);


NodoMenu* insertarOrdenado(NodoMenu* &lista, infoMenu v);
void mostrarMenu(NodoMenu* lista);
bool modificarMenu(NodoMenu* &lista, int nroPlato);
void eliminarMenu(NodoMenu* &lista, infoMenu v);



void agrearClienteAArchivo(infoCliente cliente, const char* nombreArchivo);
void cargarClienteDePruebaEnArchivo(const char* nombreArchivo);
void traerClientesDeArchivo(NodoCliente* &lista, const char* nombreArchivo);
void actualizarArchivoClientes(NodoCliente* lista, const char* nombreArchivo);


NodoCliente* insertarOrdenadoCliente(NodoCliente* &lista, infoCliente v);
void mostrarClientes(NodoCliente* lista);
bool modificarCliente(NodoCliente* &lista, int idCliente);
void eliminarCliente(NodoCliente* &lista, infoCliente v);


void push(NodoPedidos* &pila, infoPedidos v);
infoPedidos pop(NodoPedidos* &pila);
void encolar(NodoPedidos* &colafte, NodoPedidos* &colafin, infoPedidos v);
infoPedidos desencolar(NodoPedidos* &colafte, NodoPedidos* &colafin);
void mostrarPedidosPendientes(NodoPedidos* &colafte, NodoPedidos* &colafin);
void mostrarPedidosCompletados(NodoPedidos* &pila);



void facturacionDePedidos(NodoPedidos* &pila, NodoCliente* listaCliente, NodoMenu* listaMenu, const char* nombreArchivo);
void visualizarDatosDeFacturacion(const char* nombreArchivo);