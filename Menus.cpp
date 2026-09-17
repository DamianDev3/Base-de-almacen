#include "Menus.h"
#include "Categorias.h"
#include "subCategoria.h"
#include "BasedeAlmacen.h"
#include "GestorBaseDatos.h"
#include "Productos.h"
#include "windows.h"
#include <iostream>
using namespace std;

void Menus::Menugeneral()
{
    /// porto menu todavia no esta listo.
    int opciones;
    bool condicion = false;
    BasedeAlmacen almacen;
    Categorias cat;
    Productos productin;
    subCategoria subCat;
    GestorBaseDatos bd;
    do 
    {
        system("cls");
        
        cout << "Menu General:" <<endl;
        cout << "Ingresar opcion deseada:" << endl;
        cout << "1- Base de Almacen:" <<endl;
        cout << "2- buscar en base de datos por id:" <<endl;
        cout << "3- Categorias guardadas:" <<endl;
        cout << "4- Sub categorias guardadas:" <<endl;
        cout << "5- Base de datos almacen:" <<endl;
        cout << "0- Salir del programa:" <<endl; 
        cin >> opciones;
         cin.ignore();
     if (cin.fail())
        {
         cin.clear();
         cin.ignore(10000, '\n');
         opciones=-1;
             }

        switch (opciones)
        {
        case 1:
            almacen.MostrarBaseAlmacen();
            break;
            case 2:
           productin.lecturaProducto();
         break;
            case 3:
            break;
    
            case 4:
            break;
            case 5:
            
            break; 
        case 0:
        cout << "SALIENDO DEL PROGRAMA:" <<endl;
        system("pause");
        condicion = true;
        break;
        default:
        cout << "ERROR: solo se permiten numeros:" <<endl; 
            break;
        }
    }while (!condicion);
        
    


}
