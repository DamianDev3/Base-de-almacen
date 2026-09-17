#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "sqlite3.h"

class Productos {
public:
    Productos();
    Productos(std::string, std::string, std::string, std::string, std::string, int, float, int, int, int, int, int, int);

    /// SETTERS
    void setEan(std::string);
    void setNombreProducto(std::string);
    void setMarcaProducto(std::string);
    void setVariantes(std::string);
    void setContenido(std::string);
    void setUnidades(int);
    void setPrecio(float);
    void setStockMinimo(int);
    void setStockObjetivo(int);
    void setStockActual(int);
    void setIdCategoria(int);
    void setIdSubcategoria(int);
    void setIdProducto(int);

    /// GETTERS
    std::string getEan();
    std::string getNombreProducto();
    std::string getMarcaProducto();
    std::string getVariantes();
    std::string getContenido();
    int getUnidades();
    float getPrecio();
    int getStockminimo();
    int getStockObjetivo();
    int getStockActual();
    int getIdCategoria();
    int getIdSubcategoria();
    int getIdProducto();
    void lecturaProducto();

private:
    /// Propiedades del producto
    std::string _eanProductos;
    std::string _Nombreproductos;
    std::string _marcaProducto;
    std::string _variantes;
    std::string _contenido;
    int _unidades;
    float _precioVenta;
    int _stockMinimo;
    int _stockObjetivo;
    int _stockActual;

    /// IDS
    int _idProducto;
    int _idSubcategoria;
    int _idCategoria;
};
