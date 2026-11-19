#include "../include/DetalleVenta.h"
#include <cmath>
#include <string>

using namespace std;

namespace
{
    double redondearCentavos(double importe)
    {
        return std::round(importe * 100.0) / 100.0;
    }
}


DetalleVenta::DetalleVenta()
{
    _idDetalle = 0;
    _idVenta = 0;
    _codigoInterno = "";
    _eanDetectado = "";
    _precio = 0.0;
    _cantiadaProdcut = 0;
    _subTotal = 0.0;
}

DetalleVenta::DetalleVenta(int idDetalle, string codigointerno, string eanDetected, Productos producteitor, double precioVenta, int cantidadTotal, double subTotal)
{
    _idDetalle = idDetalle;
    _idVenta = 0;
    _codigoInterno = codigointerno;
    _eanDetectado = eanDetected;
    _productin = producteitor;
    _precio = precioVenta;
    _cantiadaProdcut = cantidadTotal;
    _subTotal = subTotal;
}

DetalleVenta::~DetalleVenta()
{
}


void DetalleVenta::setIdDetalle(int idDetalle)
{
    _idDetalle = idDetalle;
}

void DetalleVenta::setIdVenta(int idVenta)
{
    _idVenta = idVenta;
}

void DetalleVenta::setCodigoInterno(string codigoInterno)
{
    _codigoInterno = codigoInterno;
}

void DetalleVenta::setEanD(string eanDetectado)
{
    _eanDetectado = eanDetectado;
}

void DetalleVenta::setProducto(Productos producto)
{
    _productin = producto;
}

void DetalleVenta::setPrecio(double precio)
{
    _precio = precio;
}

void DetalleVenta::setCantidadP(int cantidadProducto)
{
    _cantiadaProdcut = cantidadProducto;
}

void DetalleVenta::setSubTotal(double subTotal)
{
    _subTotal = subTotal;
}


int DetalleVenta::getIdDetalle() const
{
    return _idDetalle;
}

int DetalleVenta::getIdVenta() const
{
    return _idVenta;
}

string DetalleVenta::getCodigoInterno() const
{
    return _codigoInterno;
}

string DetalleVenta::getEanD() const
{
    return _eanDetectado;
}

const Productos& DetalleVenta::getProducto() const
{
    return _productin;
}

double DetalleVenta::getPrecio() const
{
    return _precio;
}

int DetalleVenta::getCantidadP() const
{
    return _cantiadaProdcut;
}

double DetalleVenta::getSubTotal() const
{
    return _subTotal;
}


string DetalleVenta::getProductoSnapshot() const
{
    return _productin.getNombreProducto();
}

void DetalleVenta::setProductoSnapshot(string nombreProducto)
{
    _productin.setNombreProducto(nombreProducto);
}

void DetalleVenta::generarDetalleVTA(Productos& producto, int cantidad, const std::string& ean)
{
    _productin = producto;
    _codigoInterno = std::to_string(producto.getIdProducto());
    _eanDetectado = ean;
    _precio = producto.getPrecio();
    _cantiadaProdcut = cantidad;
    _subTotal = redondearCentavos(producto.getPrecio() * cantidad);

    cout << "Detalle de venta:" << endl;
    cout << " Producto : " << getProductoSnapshot() << endl;
    cout << " Cantidad : " << getCantidadP() << endl;
    cout << " Precio   : $" << getPrecio() << endl;
    cout << " Subtotal : $" << getSubTotal() << endl;
    cout << " -------------------------------------------------------" << endl;
}
