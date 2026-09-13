#pragma once
#include "sqlite3.h"
#include <iostream>

using namespace std;

class GestorBaseDatos
{
public:
GestorBaseDatos();
~GestorBaseDatos();
bool conectar(const char* nombreArchivo);
void desconectar();
bool buscarPorEan(const char* eanBuscado);
void mostrarBD(int limite = 30);
private:
sqlite3* _db;
};

