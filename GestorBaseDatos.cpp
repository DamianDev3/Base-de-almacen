#include "GestorBaseDatos.h"
#include "Productos.h"
#include "subCategoria.h"
#include "Categorias.h"
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

void GestorBaseDatos::buscarCategoria(int idBuscadocat) {
    //// FUNCION QUE BUSCA POR EL ID DE LA CATEGORIA Y MUESTRA LA CATEGORIA, LA SUBCATEGORIA Y LOS PRODUCTOS QUE CONTIENE ESTA.
    if (_db == nullptr) {
        cerr << "Error: Base de datos no conectada." << endl;
        return;
    }

    const char* sql = 
        "SELECT "
        "    cat.nombre_categorias, "
        "    subCat.nombre_subcategorias, "
        "    prod.eanProductos, "
        "    prod.nombreProductos, "
        "    prod.precio_venta, "
        "    prod.stock_actual "
        "FROM Categorias cat "
        "LEFT JOIN Subcategorias subCat ON subCat.id_categoria = cat.id "
        "LEFT JOIN Productos prod       ON prod.id_subcategoria = subCat.id "
        "WHERE cat.id = ? "
        "ORDER BY subCat.nombre_subcategorias, prod.nombreProductos;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar consulta: " << sqlite3_errmsg(_db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, idBuscadocat);

    string subCatActual = "";
    bool encontrado = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (!encontrado) {
            const char* txtCat = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            cout << endl << "=======================================================" << endl;
            cout << " CATEGORIA: " << (txtCat ? txtCat : "Sin Nombre") << " (ID: " << idBuscadocat << ")" << endl;
            cout << "=======================================================" << endl;
            encontrado = true;
        }

        const char* txtSub  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* txtEan  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* txtProd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        string sub = txtSub ? txtSub : "Sin Subcategorias asignadas";

        if (sub != subCatActual) {
            subCatActual = sub;
            cout << endl << "  -- Subcategoria: " << subCatActual << endl;
        }

        if (txtEan == nullptr) {
            cout << "     (No hay productos registrados en esta subcategoria)" << endl;
        } else {
            float precio = static_cast<float>(sqlite3_column_double(stmt, 4));
            int stock    = sqlite3_column_int(stmt, 5);

            cout << "     * [" << txtEan << "] "
                 << (txtProd ? txtProd : "Sin Nombre")
                 << " | $" << precio 
                 << " | Stock: " << stock << endl;
        }
    }

    if (!encontrado) {
        cout << endl << "[!] No se encontro la categoria con ID: " << idBuscadocat << endl;
    } else {
        cout << "=======================================================" << endl << endl;
    }
    system("pause");

    sqlite3_finalize(stmt);
}

void GestorBaseDatos::ModificarStockGeneral() {
    if (_db == nullptr) {
        cout << "ERROR: Base de datos no conectada." << endl;
        return;
    }

    const char* sqlSelect = 
        "SELECT eanProductos, nombreProductos, stock_minimo, stock_actual, stock_objetivo "
        "FROM Productos;";

    sqlite3_stmt* stmtSelect = nullptr;
    if (sqlite3_prepare_v2(_db, sqlSelect, -1, &stmtSelect, nullptr) != SQLITE_OK) {
        cout << "Error al preparar consulta: " << sqlite3_errmsg(_db) << endl;
        return;
    }

    const char* sqlUpdate = "UPDATE Productos SET stock_actual = ? WHERE eanProductos = ?;";
    sqlite3_stmt* stmtUpdate = nullptr;
    sqlite3_prepare_v2(_db, sqlUpdate, -1, &stmtUpdate, nullptr);

    Productos prod;

    while (sqlite3_step(stmtSelect) == SQLITE_ROW) {
        const char* ean = reinterpret_cast<const char*>(sqlite3_column_text(stmtSelect, 0));
        const char* nom = reinterpret_cast<const char*>(sqlite3_column_text(stmtSelect, 1));

        prod.setEan(ean ? ean : "");
        prod.setNombreProducto(nom ? nom : "");
        prod.setStockMinimo(sqlite3_column_int(stmtSelect, 2));
        prod.setStockActual(sqlite3_column_int(stmtSelect, 3));
        prod.setStockObjetivo(sqlite3_column_int(stmtSelect, 4));

        cout << "\n----------------------------------------" << endl;
        cout << "Producto: " << prod.getNombreProducto() << endl;
        cout << "Stock actual registrado: " << prod.getStockActual() << endl;
        
        char modificar;
        cout << "¿Desea cambiar el stock de este producto? (s/n): ";
        cin >> modificar;

        if (modificar == 's' || modificar == 'S') {
            int nuevoStock;
            cout << "Ingrese el nuevo stock actual: ";
            cin >> nuevoStock;

            prod.setStockActual(nuevoStock);

            sqlite3_bind_int(stmtUpdate, 1, prod.getStockActual());
            sqlite3_bind_text(stmtUpdate, 2, prod.getEan().c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmtUpdate) == SQLITE_DONE) {
                cout << "[Guardado en BD con exito]" << endl;
            } else {
                cout << "[Error al guardar en BD]" << endl;
            }

            sqlite3_reset(stmtUpdate);
            sqlite3_clear_bindings(stmtUpdate);
        }
    }

    sqlite3_finalize(stmtSelect);
    sqlite3_finalize(stmtUpdate);
}

void GestorBaseDatos::SubcategoriasMod()
{
    if (_db == nullptr)
    {
        cout << "ERROR: base de datos no conectada." << endl;
        return;
    }

    const char* sqlSelect = 
        "SELECT "
        "    id, "
        "    nombre_subcategorias "
        "FROM Subcategorias;";

    sqlite3_stmt* stmtSelect = nullptr;

    if (sqlite3_prepare_v2(_db, sqlSelect, -1, &stmtSelect, nullptr) != SQLITE_OK) {
        cout << "Error al preparar la consulta de seleccion: " << sqlite3_errmsg(_db) << endl;
        return;
    }

    const char* sqlUpdate = "UPDATE Subcategorias SET nombre_subcategorias = ? WHERE id = ?;";
    sqlite3_stmt* stmtUpdate = nullptr;

    if (sqlite3_prepare_v2(_db, sqlUpdate, -1, &stmtUpdate, nullptr) != SQLITE_OK) {
        cout << "Error al preparar la consulta de actualizacion: " << sqlite3_errmsg(_db) << endl;
        sqlite3_finalize(stmtSelect);
        return; 
    }

    subCategoria subCat;
    string modificarNombre;

    while (sqlite3_step(stmtSelect) == SQLITE_ROW)
    {
        // 2. Extraer ID (índice 0) y Nombre (índice 1) correctamente
        int idSub = sqlite3_column_int(stmtSelect, 0);
        const char* currentName = reinterpret_cast<const char*>(sqlite3_column_text(stmtSelect, 1));

        subCat.setIdSubcategoria(idSub);
        subCat.setnombreSubcategoria(currentName ? currentName : "");

        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << subCat.getIdSubcategoria() 
             << " | Subcategoria actual: " << subCat.getNombreSubcategoria() << endl;

        char opcion;
        cout << "¿Desea renombrar esta subcategoria? (s/n): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') {
            cout << "Ingrese el nuevo nombre: ";
            cin >> ws; 
            getline(cin, modificarNombre);

            subCat.setnombreSubcategoria(modificarNombre);

            
            sqlite3_bind_text(stmtUpdate, 1, subCat.getNombreSubcategoria().c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmtUpdate, 2, subCat.getIdSubcategoria());

          
            if (sqlite3_step(stmtUpdate) == SQLITE_DONE) {
                cout << "[Guardado con exito en la base de datos]" << endl;
            } else {
                cout << "Error al actualizar: " << sqlite3_errmsg(_db) << endl;
            }

           
            sqlite3_reset(stmtUpdate);
            sqlite3_clear_bindings(stmtUpdate);
        }
    }

    sqlite3_finalize(stmtSelect);
    sqlite3_finalize(stmtUpdate);
}

void GestorBaseDatos::CategoriasMod()
{
    Categorias objCat;
    if (_db == nullptr)
    {
        cout << "Error: Base de datos no conectada:" <<endl;
        return;
    }
    const char* sqlSelect = "SELECT id, nombre_categorias FROM Categorias";

    sqlite3_stmt* stmtSelect = nullptr;
    if (sqlite3_prepare_v2(_db,sqlSelect,-1,&stmtSelect,nullptr) != SQLITE_OK)
    {
        cout << "Error al preparar la consulta:" <<sqlite3_errmsg(_db) <<endl;
        return;
    }
    const char* sqlUpdate = "UPDATE Categorias SET nombre_categorias =? WHERE id = ?;"; 
    sqlite3_stmt* stmtUpdate = nullptr;
    if (sqlite3_prepare_v2(_db,sqlUpdate,-1,&stmtUpdate,nullptr) !=SQLITE_OK)
    {
        cout << "Error al preparar la consulta" << sqlite3_errmsg(_db) <<endl;
        sqlite3_finalize(stmtUpdate);
        return;
    }
    string newNameCategoria;
    while (sqlite3_step(stmtSelect) == SQLITE_ROW)
    {
        int idCat = sqlite3_column_int(stmtSelect,0);
        const char* rawText = reinterpret_cast<const char*>(sqlite3_column_text(stmtSelect, 1));
        newNameCategoria = rawText ? rawText : "";

        objCat.setIdCategoria(idCat);
        objCat.setNombreCategoria(newNameCategoria);

        cout << "\n----------------------------------------" << endl;
        cout << "Id" << objCat.getIdCategoria();
        cout << "Categoria actual:" << objCat.getNombreCategoria() <<endl;
        cout << "\n----------------------------------------" << endl;

        cout << "Ingrese el nuevo nombre de la categoria:" <<endl;
        cin >> ws;
        getline(cin,newNameCategoria);
        objCat.setNombreCategoria(newNameCategoria); 
        sqlite3_bind_text(stmtUpdate,1,objCat.getNombreCategoria().c_str(),-1,SQLITE_STATIC); 
        sqlite3_bind_int (stmtSelect,2,objCat.getIdCategoria()); 
        if (sqlite3_step(stmtUpdate) == SQLITE_DONE)
        {
            cout << "Cambios guardados:" <<endl;
            system ("pause");
        } else
        {
            cout << "Error al actualizar los datos:" <<endl;
            system ("pause");
        }
        sqlite3_reset(stmtUpdate);
        sqlite3_clear_bindings(stmtUpdate);
    }

    sqlite3_finalize(stmtSelect);
    sqlite3_finalize(stmtUpdate);
    
}

void GestorBaseDatos::AltaDeUsuario(string nombreu,string roluser,string password)
{
 if (_db == nullptr) {
    cout << "Base de datos no conectada:" << endl;
    return; 
 }
    const char* sqlSelect = "SELECT id_usuario, Nombre_usuario, Password_usuario, Rol_usuario FROM Usuarios ;";
sqlite3_stmt* sqlSelectUser  = nullptr;

 
}