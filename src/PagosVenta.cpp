#include "PagosVenta.h"
#include "../include/Formato.h"
#include <string>
#include <iostream>
using namespace std;


PagosVenta::PagosVenta()
{
    _idPago = 0;
    _idVentaGenerada = 0;
    _medioPago = "";
    _subtotalVTA = 0.0;

}

PagosVenta::PagosVenta(int idPago, int idVenta, string medioPago, double subTotal)
{
    _idPago = idPago;
    _idVentaGenerada = idVenta;
    _medioPago = medioPago;
    _subtotalVTA = subTotal;
}

/// SETTERS

void PagosVenta::setIdPago(int idPago)
{
    _idPago = idPago;
}

void PagosVenta::setIdVTA(int idVenta)
{
    _idVentaGenerada = idVenta;
}

void PagosVenta::setMediodePago(string medioPago)
{
    _medioPago = medioPago;
}

void PagosVenta::setSubtotal(double subTotal)
{
    _subtotalVTA = subTotal;
}

/// GETTERS

int PagosVenta::getIdPago() const
{
    return _idPago;
}

int PagosVenta::getIdVTA() const
{
    return _idVentaGenerada;
}

string PagosVenta::getMediodePago() const
{
    return _medioPago;
}

double PagosVenta::getSubtotal() const
{
    return _subtotalVTA;
}

/// Genera el pago de la venta (medio de pago e importe) y lo muestra.
void PagosVenta::generarPagodeVenta(Ventas & ventaGenerada)
{
    _idVentaGenerada = ventaGenerada.getIdVenta();
    if (_medioPago.empty())
    {
        _medioPago = "EFECTIVO";
    }
    _subtotalVTA = ventaGenerada.getTotalPagado();

    cout << "Pago de Venta:" << endl;
    cout << "ID de venta: " << _idVentaGenerada << endl;
    cout << "Medio de pago: " << _medioPago << endl;
    cout << "Importe: $" << dinero(_subtotalVTA) << endl;
}

/// Muestra el pago (lo usa la pantalla "Ultimo pago de venta").
void PagosVenta::pagoVTAgenerado()
{
    cout << " Pago N°  : " << _idPago << endl;
    cout << " Venta N° : " << _idVentaGenerada << endl;
    cout << " ---------------------------------------------------------" << endl;
    cout << " Medio de pago : " << _medioPago << endl;
    cout << " Importe       : $" << dinero(_subtotalVTA) << endl;
}
