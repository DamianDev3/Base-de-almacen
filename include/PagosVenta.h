#pragma once
#include <iostream>
#include "../include/Ventas.h"
class PagosVenta
{
public:
    PagosVenta();
    PagosVenta(int,int,std::string,double);
    void setIdPago(int);
    void setIdVTA(int);
    void setMediodePago(std::string);
    void setSubtotal(double);

    int getIdPago() const;
    int getIdVTA() const;
    std::string getMediodePago() const;
    double getSubtotal() const;

    void generarPagodeVenta(Ventas&);
    void pagoVTAgenerado();

private:
int _idPago;
int _idVentaGenerada;
std::string _medioPago;
double _subtotalVTA;

};
