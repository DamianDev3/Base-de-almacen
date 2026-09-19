#include "../include/Productos.h"
#include "../include/GestorBaseDatos.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
Productos::Productos()
{
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
    _idProducto = 0;
    _idCategoria = 0;
    _idSubcategoria = 0;
}

Productos::Productos(string eanProducto,string Nombreproducto,string marcaProducto,string variantes,string contenido,int unidades,float precioVenta,int stockActual,int stockMinimo,int stockObjetivo,int idCategoria,int idSubcategoria,int idPdoructo)
{
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
    _idProducto = idPdoructo;
    _idCategoria = idCategoria;
    _idSubcategoria = idSubcategoria;
}

/// SETTERS

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

void Productos::setIdProducto(int idProducto) {
    _idProducto = idProducto;
}

/// GETTERS

string Productos::getEan() {
    return _eanProductos;
}

string Productos::getNombreProducto() {
    return _Nombreproductos;
}

string Productos::getMarcaProducto() {
    return _marcaProducto;
}

string Productos::getVariantes() {
    return _variantes;
}

string Productos::getContenido() {
    return _contenido;
}

int Productos::getUnidades() {
    return _unidades;
}

float Productos::getPrecio() {
    return _precioVenta;
}

int Productos::getStockminimo() {
    return _stockMinimo;
}

int Productos::getStockObjetivo() {
    return _stockObjetivo;
}

int Productos::getStockActual() {
    return _stockActual;
}

int Productos::getIdCategoria() {
    return _idCategoria;
}

int Productos::getIdSubcategoria() {
    return _idSubcategoria;
}

int Productos::getIdProducto() {
    return _idProducto;
}
void Productos::lecturaProducto()
{
    int idBuscado;
    GestorBaseDatos datos;
    if(!datos.conectar("db/Almacen.db")) 
    {
        cout << "No se pudo conectar a la base de datos:" <<endl;
        return;
    }
    cout << "ingresar el id a buscar:" <<endl;
    cin >>idBuscado;
     if (cin.fail())
        {
         cin.clear();
         cin.ignore(10000, '\n');
             }
    datos.buscarCategoria(idBuscado);
    datos.desconectar(); 
}