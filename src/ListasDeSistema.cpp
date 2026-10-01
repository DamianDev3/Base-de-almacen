#include "ListasDeSistema.h"
#include <iostream>
#include <string>
using namespace std;


ListasDeSistema::ListasDeSistema()
{

}

ListasDeSistema::ListasDeSistema(std::string rolDeSistema, std::string revisionPrecio, std::string estadoCompra, std::string direccionstock, std::string tipoMovimiento, std::string motivoCorreccion, std::string MediodePago, std::string EstadoVenta, std::string unidadMedicion)
{
    _rolDelsistema = rolDeSistema;
    _RevisionPrecio = revisionPrecio;
    _EstadoCompra = estadoCompra;
    _direccionStock = direccionstock;
    _tipoMovimiento = tipoMovimiento;
    _motivoCorreccion = motivoCorreccion;
    _medioDePago = MediodePago;
    _estadoDeVenta = EstadoVenta;
    _unidadDeMedicion = unidadMedicion;
}

void ListasDeSistema::setRoldeSistema(std::string)
{
}

void ListasDeSistema::setRevicionPrecio(std::string)
{
}
