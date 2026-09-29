#include "../include/Productos.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Selector.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
Productos::Productos()
{
    _idProducto = 0;
    _eanProductos = "sin_ean"; 
    _Nombreproductos = "sin_nombre"; 
    _marcaProducto = "sin_marca";
    _variantes = "sin_variantes";
    _contenido = "sin_contenido";
    _unidades = 0;
    _precioVenta = 0.0;
    _stockActual = 0;
    _stockMinimo = 0;
    _stockObjetivo = 0;
    _idCategoria = 0;
    _idSubcategoria = 0;
}

Productos::Productos(int idProducto,string eanProducto,string Nombreproducto,string marcaProducto,string variantes,string contenido,int unidades,float precioVenta,int stockActual,int stockMinimo,int stockObjetivo,int idCategoria,int idSubcategoria)
{
    _idProducto = idProducto;
    _eanProductos = eanProducto;
    _Nombreproductos = Nombreproducto;
    _marcaProducto = marcaProducto;
    _variantes = variantes;
    _contenido = contenido;
    _unidades = unidades;
    _precioVenta = precioVenta;
    _stockActual = stockActual;
    _stockMinimo = stockMinimo;
    _stockObjetivo = stockObjetivo;
    _idCategoria = idCategoria;
    _idSubcategoria = idSubcategoria;
}

/// SETTERS
void Productos::setIdProducto(int idProducto)
{
    _idProducto = idProducto;
}

void Productos::setEan(string ean) {
    _eanProductos = ean;
}

void Productos::setNombreProducto(string nombreProducto) {
    _Nombreproductos = nombreProducto;
}

void Productos::setMarcaProducto(string marcaProducto) {
    _marcaProducto = marcaProducto;
}

void Productos::setVariantes(string variantes) {
    _variantes = variantes;
}

void Productos::setContenido(string contenido) {
    _contenido = contenido;
}

void Productos::setUnidades(int unidades) {
    _unidades = unidades;
}

void Productos::setPrecio(float precio) {
    _precioVenta = precio;
}

void Productos::setStockMinimo(int stockMinimo) {
    _stockMinimo = stockMinimo;
}

void Productos::setStockObjetivo(int stockObjetivo) {
    _stockObjetivo = stockObjetivo;
}

void Productos::setStockActual(int stockActual) {
    _stockActual = stockActual;
}

void Productos::setIdCategoria(int idCategoria) {
    _idCategoria = idCategoria;
}

void Productos::setIdSubcategoria(int idSubcategoria) {
    _idSubcategoria = idSubcategoria;
}

/// GETTERS
int Productos::getIdProducto() const
{
    return _idProducto;
}

string Productos::getEan() const {
    return _eanProductos;
}

string Productos::getNombreProducto() const {
    return _Nombreproductos;
}

string Productos::getMarcaProducto() const {
    return _marcaProducto;
}

string Productos::getVariantes() const {
    return _variantes;
}

string Productos::getContenido() const {
    return _contenido;
}

int Productos::getUnidades() const {
    return _unidades;
}

float Productos::getPrecio() const {
    return _precioVenta;
}

int Productos::getStockMinimo() const {
    return _stockMinimo;
}

int Productos::getStockObjetivo() const {
    return _stockObjetivo;
}

int Productos::getStockActual() const {
    return _stockActual;
}

int Productos::getIdCategoria() const {
    return _idCategoria;
}

int Productos::getIdSubcategoria() const {
    return _idSubcategoria;
}

void Productos::lecturaProducto()
{
    GestorBaseDatos datos;
    if(!datos.conectar("db/Almacen.db")) 
    {
        cout << "No se pudo conectar a la base de datos:" <<endl;
        return;
    }

    int idBuscado = datos.elegirCategoria("Leer producto - Elegir categoria");
    if (idBuscado != Selector::CANCELADO)
    {
        datos.buscarCategoria(idBuscado);
    }
    datos.desconectar(); 
}
