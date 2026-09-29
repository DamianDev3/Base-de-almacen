#pragma once
#include "../lib/sqlite/sqlite3.h"
#include "../include/ClaseUsuarios.h"
#include <iostream>

using namespace std;

class GestorBaseDatos
{
public:
GestorBaseDatos();
~GestorBaseDatos();
bool conectar(const char* nombreArchivo);
void desconectar();
bool buscarPorProducto(const char* eanBuscado);
void mostrarBD(int limite = 30);
void AlmacenInventario();
void buscarCategoria(int);
ClaseUsuarios validarUsuario();
void ModificarStockGeneral();
void SubcategoriasMod();
void CategoriasMod();
void comprarProducto();
void registrarVenta();
void mostrarUltimaVenta();
int elegirCategoria(const std::string& titulo);
void AltaDeUsuario(std::string,std::string,std::string,std::string);




private:
sqlite3* _db;
};

