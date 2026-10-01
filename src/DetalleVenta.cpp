#include "../include/DetalleVenta.h"
#include <cmath>
#include <string>

using namespace std;

namespace
{
    /// Redondea un importe a 2 decimales (centavos).
    double redondearCentavos(double importe)
    {
        return std::round(importe * 100.0) / 100.0;
    }
}

/// CONSTRUCTORES

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

/// SETTERS

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

/// GETTERS

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

/// Puente con la columna producto de la base.

string DetalleVenta::getProductoSnapshot() const
{
    return _productin.getNombreProducto();
}

void DetalleVenta::setProductoSnapshot(string nombreProducto)
{
    _productin.setNombreProducto(nombreProducto);
}

/// Genera el detalle a partir de un producto y una cantidad: completa sus
/// datos (codigo interno, EAN, precio y subtotal) y lo muestra con el mismo
/// formato que usa el ticket de venta.
void DetalleVenta::generarDetalleVTA(Productos& producto, int cantidad)
{
    _productin = producto;
    _codigoInterno = std::to_string(producto.getIdProducto());
    _eanDetectado = producto.getEan();
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
