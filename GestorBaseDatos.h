#pragma once
#include "sqlite3.h"
#include <iostream>

using namespace std;

class GestorBaseDatos
{
    /// HACER UNA FUNCION QUE BUSQUE POR CATEGORIA PARA QUE MUESTRE LAS SUBCATEGORIAS Y CONSECUENTEMENTE EL PRODUCTO Y SUS PROPIEDADES, LUEGO RELACIONARLOS CON LOS SETTERS DE LA CLASE PRODUCTO
public:
GestorBaseDatos();
~GestorBaseDatos();
bool conectar(const char* nombreArchivo);
void desconectar();
bool buscarPorProducto(const char* eanBuscado);
void mostrarBD(int limite = 30);
void buscarCategoria(int);
void ModificarStockGeneral();
void SubcategoriasMod();
void CategoriasMod();

private:
sqlite3* _db;
};

