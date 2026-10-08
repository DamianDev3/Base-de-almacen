#include "ListasDeSistema.h"
#include <iostream>
#include <string>
using namespace std;


ListasDeSistema::ListasDeSistema()
{

    _rolDelsistema = "Sin_rol:";
    _RevisionPrecio = "Sin_revision_precio:";
    _EstadoCompra = "Sin_estado_compra:";
    _direccionStock = "Sin_direccion_stock:";
    _tipoMovimiento = "Sin_tipo_movimiento:";
    _motivoCorreccion = "Sin_motivo_correccion:";
    _medioDePago = "Sin_medio_de_pago:";
    _estadoDeVenta = "Sin_estado_de_venta:";
    _unidadDeMedicion = "Sin_unidad_de_medicion:";
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

void ListasDeSistema::setRoldeSistema(std::string rolSistema)
{
    _rolDelsistema = rolSistema;

}

void ListasDeSistema::setRevicionPrecio(std::string RevicionPrecio)
{
    _RevisionPrecio = RevicionPrecio;
}

void ListasDeSistema::setEstadoCompra(std::string estadoCompra)
{
    _EstadoCompra = estadoCompra;
}

void ListasDeSistema::setDirecionstock(std::string direccionStock)
{
    _direccionStock = direccionStock;
}

void ListasDeSistema::settipoMovimiento(std::string tipoMovimiento)
{
    _tipoMovimiento = tipoMovimiento;
}

void ListasDeSistema::setmotivoCorreccion(std::string motivoCorreccion)
{
    _motivoCorreccion = motivoCorreccion;
}

void ListasDeSistema::setMediodePago(std::string medioPago)
{
    _medioDePago = medioPago;
}

void ListasDeSistema::setEstadodeVenta(std::string estadoDeVenta)
{
    _estadoDeVenta = estadoDeVenta;
}

void ListasDeSistema::setUnidadMedicion(std::string UnidadMedicion)
{
    _unidadDeMedicion = UnidadMedicion;
}

string ListasDeSistema::getRolsistema() const
{
    return _rolDelsistema;
}
string ListasDeSistema::getRevisionPrecio() const
{
    return _RevisionPrecio;
}

std::string ListasDeSistema::getEstadoCompra() const
{
    return _EstadoCompra;
}

std::string ListasDeSistema::getDireccionstock() const
{
    return _direccionStock;
}

std::string ListasDeSistema::getTipoMovimiento() const
{
    return _tipoMovimiento;
}

std::string ListasDeSistema::getmotivoCorreccion() const
{
    return _motivoCorreccion;
}

std::string ListasDeSistema::getMediodePago() const
{
    return _medioDePago;
}
string ListasDeSistema::getEstadoVenta() const
{
    return _estadoDeVenta;
}

std::string ListasDeSistema::getUnidadMedicon() const
{
    return _unidadDeMedicion;
}
