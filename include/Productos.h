#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "../lib/sqlite/sqlite3.h"

class Productos {
public:
    Productos();
    Productos(int,std::string, std::string, std::string, std::string, std::string, int, float, int, int, int, int, int);

    /// SETTERS
    void setIdProducto(int);
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

    /// GETTERS
    int getIdProducto() const;
    std::string getEan() const;
    std::string getNombreProducto() const;
    std::string getMarcaProducto() const;
    std::string getVariantes() const;
    std::string getContenido() const;
    int getUnidades() const;
    float getPrecio() const;
    int getStockMinimo() const;
    int getStockObjetivo() const;
    int getStockActual() const;
    int getIdCategoria() const;
    int getIdSubcategoria() const;
    void lecturaProducto();

private:
    /// Propiedades del producto
    int _idProducto;
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
    int _idSubcategoria;
    int _idCategoria;
};
