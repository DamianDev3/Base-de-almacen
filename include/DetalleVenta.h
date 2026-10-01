#pragma once
#include <string>
#include <iostream>
#include "../include/Productos.h"
class DetalleVenta
{
public:

    /// CONSTRUCTORES
    DetalleVenta();
    DetalleVenta(int, std::string, std::string, Productos, double, int, double);
    ~DetalleVenta();

    ////SETTERS
    void setIdDetalle(int);
    void setIdVenta(int);
    void setCodigoInterno(std::string);
    void setEanD(std::string);
    void setProducto(Productos);
    void setPrecio(double);
    void setCantidadP(int);
    void setSubTotal(double);

    ////GETTERS
    int getIdDetalle() const;
    int getIdVenta() const;
    std::string getCodigoInterno() const;
    std::string getEanD() const;
    const Productos& getProducto() const;
    double getPrecio() const;
    int getCantidadP() const;
    double getSubTotal() const;

    /// Puente con la base de datos: la tabla guarda una "foto" del nombre del
    /// producto (columna producto), no el objeto Productos completo.
    std::string getProductoSnapshot() const;
    void setProductoSnapshot(std::string);
    void generarDetalleVTA(Productos&,int);

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
