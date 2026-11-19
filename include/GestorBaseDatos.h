#pragma once
#include "../lib/sqlite/sqlite3.h"
#include "../include/ClaseUsuarios.h"
#include "../include/Productos.h"
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
void correccionStockGeneral();
void SubcategoriasMod();
void CategoriasMod();
void venderProducto();
void registrarVenta();
void mostrarUltimaVenta();
void mostrarUltimoDetalle();
void mostrarUltimoPago();
int elegirCategoria(const std::string& titulo);
int elegirSubcategoria(int idCategoria);
bool AltaDeProducto(Productos& producto, const std::string& eanPrincipal);
void AltaDeUsuario(std::string,std::string,std::string,std::string);
void CompraAutomatica(Productos);
void MovimientosStock();
bool consultarStock();
bool generarCompraDehoy();
void compraHoyHistorial();
bool compararEan(std::string);

private:
sqlite3* _db;
};

