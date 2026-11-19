#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "../lib/sqlite/sqlite3.h"

class Productos {
public:
    Productos();
    Productos(int,std::string, std::string, std::string, std::string, std::string, std::string, std::string, int, double, int, int, int, int, int, std::string);

    void setIdProducto(int);
    void setNombreProducto(std::string);
    void setMarcaProducto(std::string);
    void setVariantes(std::string);
    void setCaracteristicas(std::string);
    void setEnvase(std::string);
    void setContenido(std::string);
    void setUnidad(std::string);
    void setUnidades(int);
    void setPrecio(double);
    void setStockMinimo(int);
    void setStockObjetivo(int);
    void setStockActual(int);
    void setIdCategoria(int);
    void setIdSubcategoria(int);
    void setObservacion(std::string);

    int getIdProducto() const;
    std::string getNombreProducto() const;
    std::string getMarcaProducto() const;
    std::string getVariantes() const;
    std::string getCaracteristicas() const;
    std::string getEnvase() const;
    std::string getContenido() const;
    std::string getUnidad() const;
    int getUnidades() const;
    double getPrecio() const;
    int getStockMinimo() const;
    int getStockObjetivo() const;
    int getStockActual() const;
    int getIdCategoria() const;
    int getIdSubcategoria() const;
    std::string getObservacion() const;
    void lecturaProducto();
    void altaProducto();

private:
    int _idProducto;
    std::string _Nombreproducto;
    std::string _marcaProducto;
    std::string _variantes;
    std::string _caracteristicas;
    std::string _envase;
    std::string _contenidoXunidad;
    std::string _unidad;
    int _unidades;
    double _precioVenta;
    int _stockMinimo;
    int _stockObjetivo;
    int _stockActual;
    int _idSubcategoria;
    int _idCategoria;
    std::string _observacion;
};
