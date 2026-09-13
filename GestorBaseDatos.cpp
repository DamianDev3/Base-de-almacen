#include "GestorBaseDatos.h"
#include <iostream>

using namespace std;
GestorBaseDatos::GestorBaseDatos() {
    _db = nullptr;
}

GestorBaseDatos::~GestorBaseDatos() {
    desconectar();
}
bool GestorBaseDatos::conectar(const char* nombreArchivo) {
    int res = sqlite3_open(nombreArchivo, &_db);
    return (res == SQLITE_OK);
}

void GestorBaseDatos::desconectar() {
    if (_db != nullptr) {
        sqlite3_close(_db);
        _db = nullptr;
    }
}
bool GestorBaseDatos::buscarPorEan(const char* eanBuscado) {
    if (_db == nullptr) return false;

    // Consulta SQL con el nombre exacto de las columnas del CSV importado
    const char* sql = "SELECT Producto, Marca, [Mejor precio] FROM Comparador WHERE [Código / EAN SEPA] = ? LIMIT 1;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error SQL: " << sqlite3_errmsg(_db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, eanBuscado, -1, SQLITE_STATIC);

    bool encontrado = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* nombre = (const char*)sqlite3_column_text(stmt, 0);
        const char* marca  = (const char*)sqlite3_column_text(stmt, 1);
        const char* precio = (const char*)sqlite3_column_text(stmt, 2);

        cout << "\n================ PRODUCTO ENCONTRADO ================" << endl;
        cout << "EAN:          " << eanBuscado << endl;
        cout << "Descripcion:  " << (nombre ? nombre : "N/A") << endl;
        cout << "Marca:        " << (marca ? marca : "N/A") << endl;
        cout << "Mejor precio: $" << (precio ? precio : "0.00") << endl;
        cout << "=====================================================\n" << endl;
        encontrado = true;
    } else {
        cout << "\nNo se encontro producto para el EAN: " << eanBuscado << endl;
    }

    sqlite3_finalize(stmt);
    return encontrado;
}
void GestorBaseDatos::mostrarBD(int limite) {
   if (_db == nullptr)
   {
    conectar("almacen.db");
   }

    if (_db == nullptr) {
        cout << "Base de datos no conectada." << endl;
        system("pause"); 
        return;
    }

    const char* sql = "SELECT \"Código / EAN SEPA\", Producto, Marca, \"Mejor precio\" FROM Comparador LIMIT ?;";
    
    // 1. La variable stmt debe declararse aca, en el ambito principal de la funcion
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error SQL: " << sqlite3_errmsg(_db) << endl;
        system("pause");
        return;
    }

    sqlite3_bind_int(stmt, 1, limite);
    system("cls"); 
    cout << "\n============================== CATALOGO EN BASE DE DATOS ==============================\n";
    
    int nro = 1;
    // 2. Aca el while ya reconoce stmt sin problemas
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* ean    = (const char*)sqlite3_column_text(stmt, 0);
        const char* nombre = (const char*)sqlite3_column_text(stmt, 1);
        const char* marca  = (const char*)sqlite3_column_text(stmt, 2);
        const char* precio = (const char*)sqlite3_column_text(stmt, 3);

        cout << nro << ". [" << (ean ? ean : "SIN EAN") << "] "
             << (nombre ? nombre : "N/A") << " | "
             << (marca ? marca : "-") << " | $"
             << (precio ? precio : "0.00") << "\n";
        nro++;
    }

    cout << "=======================================================================================\n\n";
    system("pause");
    
    sqlite3_finalize(stmt);
}