#include "../include/Categorias.h"
#include "../include/GestorBaseDatos.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

Categorias::Categorias() {
    _idCategoria = 0;
    _nombreCategoria = "SIN_CATEGORIA";
    _estadoCategoria = true;
}

Categorias::Categorias(int id, string nombreCategoria, bool estado) {
    _idCategoria = id;
    _nombreCategoria = nombreCategoria;
    _estadoCategoria = estado;
}

void Categorias::setIdCategoria(int id) {

    _idCategoria = id;
}
void Categorias::setNombreCategoria(string nombreCategoria) {
 _nombreCategoria = nombreCategoria;
}
void Categorias::setEstadoCategoria(bool estadoCategoria) {
    _estadoCategoria = estadoCategoria;
}
int Categorias::getIdCategoria() {
    return _idCategoria;
}
string Categorias::getNombreCategoria() {
    return _nombreCategoria;
}
bool Categorias::getEstadoCategoria() {
    return _estadoCategoria;
}
void Categorias::listaCategorias() {
}