#include "BasedeAlmacen.h"
#include "GestorBaseDatos.h"
#include <iostream>
#include <cstring>
#include <string> 

using namespace std;
void BasedeAlmacen::MostrarBaseAlmacen()
{
    system("cls");
cout << "================================================================================" << endl;
    cout << "                             BASE DE ALMACEN - PRODUCTOS                        " << endl;
    cout << "================================================================================" << endl;
    cout << " [ Codigo: ] | EAN Principal: " << endl;
    cout << " -------------------------------------------------------------------------------" << endl;
    cout << "  Categoria      : " << endl;
    cout << "  Subcategoria   : " << endl;
    cout << "  Producto       : " << endl;
    cout << "  Marca          : " << endl;
    cout << "  Variante       : " << endl;
    cout << "  Caracteristicas: " << endl;
    cout << "  Envase         : " << endl;
    cout << "  Contenido      : " << endl;
    cout << "  Unidad         : " << endl;
    cout << "  Unidades x pack: " << endl;
    cout << "  Precio Venta   : $ " << endl;
    cout << "  Stock Minimo   : " << endl;
    cout << "  Stock Objetivo : " << endl;
    cout << "  Stock Actual   : " << endl;
    cout << "  Observacion    : " << endl;
    cout << "================================================================================" << endl;

    system("pause");

}