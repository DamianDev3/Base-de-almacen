#include "Categorias.h"
#include "subCategoria.h"
#include "ArchivoCategoria.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Constructor por defecto:
Categorias::Categorias() {
    _idCategoria = 0;
    strcpy(_nombreCategoria,"Sin_Categoria");
    _estadoCategoria = true;
}

// Constructor con parámetros:
Categorias::Categorias(int id, const char* nombre, bool estado) {
    _idCategoria = id;
    strcpy(_nombreCategoria,nombre);
    _estadoCategoria = estado;
}

void Categorias::setIdCategoria(int id) {

    _idCategoria = id;
}
void Categorias::setNombreCategoria(const char* nombreCategoria) {
 strcpy(_nombreCategoria, nombreCategoria);
}
void Categorias::setEstadoCategoria(bool estadoCategoria) {
    _estadoCategoria = estadoCategoria;
}
int Categorias::getIdCategoria() {
    return _idCategoria;
}
const char* Categorias::getNombreCategoria() {
    return _nombreCategoria;
}
bool Categorias::getEstadoCategoria() {
    return _estadoCategoria;
}
void Categorias::listaCategorias() {
    ArchivoCategoria saveCat;
    int idGenerado;
    int cantidad;
    const char* categoriaAlimento [] ={
        "Aceites y vinagres",
        "Arroz",
        "Pastas",
        "Harinas y premezclas",
        "Legumbres",
        "Conservas",
        "Salsas y aderezos",
        "Mermeladas y dulces",
        "Azucar y edulcorantes",
        "Sal y condimentos",
        "Caldos, sopas y pures",
        "Cereales y desayuno",
        "Galletitas",
        "Snacks",
        "Panificados",
        "Reposteria y postres",
        "Untables",
    };

    const char *categoriaNombre;
    categoriaNombre = _nombreCategoria;
    idGenerado = _idCategoria;
    const char* nombre;
    const char* listaCategorias[] = {
        "Alimentos",
        "Bebidas sin alcohol",
        "Infusiones",
        "Bebidas alcoholicas",
        "Golosinas",
        "Lacteos y refrigerados",
        "Frescos",
        "Congelados",
        "Limpieza",
        "Cuidado personal e higiene",
        "Papel y descartables",
        "Bebes",
        "Mascotas",
        "Hogar y bazar",
        "Otros"
    };

///el total de la lista se divide por la cantidad de categorias.
     cantidad = sizeof(listaCategorias) / sizeof(listaCategorias[0]);

    for (int i = 0; i < cantidad; i++) {
     idGenerado = i + 1; 
         nombre = listaCategorias[i];
        Categorias category(idGenerado, nombre, true);
       saveCat.guardadoListacategorias(category); 
        cout << "ID: " << category.getIdCategoria()
             << " | Nombre: " << category.getNombreCategoria() << endl;
            }
            system("pause");
}