#pragma once
#include <string>
#include <iostream>
#include "../include/Productos.h"
class DetalleVenta
{
public:

    DetalleVenta();
    DetalleVenta(int, std::string, std::string, Productos, double, int, double);
    ~DetalleVenta();

    void setIdDetalle(int);
    void setIdVenta(int);
    void setCodigoInterno(std::string);
    void setEanD(std::string);
    void setProducto(Productos);
    void setPrecio(double);
    void setCantidadP(int);
    void setSubTotal(double);

    int getIdDetalle() const;
    int getIdVenta() const;
    std::string getCodigoInterno() const;
    std::string getEanD() const;
    const Productos& getProducto() const;
    double getPrecio() const;
    int getCantidadP() const;
    double getSubTotal() const;

    std::string getProductoSnapshot() const;
    void setProductoSnapshot(std::string);
    void generarDetalleVTA(Productos&,int,const std::string& ean);

private:
    int _idDetalle;
    int _idVenta;
    std::string _codigoInterno;
    std::string _eanDetectado;
    Productos _productin;
    double _precio;
    int _cantiadaProdcut;
    double _subTotal;
};
