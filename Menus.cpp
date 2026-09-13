#include "Menus.h"
#include "Categorias.h"
#include "ArchivoCategoria.h"
#include "ArchivoSubcategoria.h"
#include "subCategoria.h"
#include "BasedeAlmacen.h"
#include "GestorBaseDatos.h"
#include <iostream>
using namespace std;
////CREAR LA RELACION ENTRE CADA PRODUCTOS Y CATEGORIAS Y GENERAR LOS PRECIOS PARA CADA PRODUCTO, DESPUES GENERAR LOS MOVIMIENTOS AUTOMATICOS JUNTO SUS CLASES
////GENERAR MAS TABLAS EN LA BASE DE DATOS

void Menus::Menugeneral()
{
    /// porto menu todavia no esta listo.
    int opciones;
    bool condicion = false;
    BasedeAlmacen almacen;
    Categorias cat;
    subCategoria subCat;
    ArchivoCategoria archiCat;
    ArchivoSubcategoria archiSubC;
    GestorBaseDatos bd;
    do 
    {
        system("cls");
        
        cout << "Menu General:" <<endl;
        cout << "Ingresar opcion deseada:" << endl;
        cout << "1- Base de Almacen:" <<endl;
        cout << "2- Lista de Subcategorias:" <<endl;
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
           subCat.mostrarCatalogoInicial();
         break;
            case 3:
            archiCat.Categoriasguardadas();
            break;
    
            case 4:
            archiSubC.subCategoriaGuardada();
            break;
            case 5:
            bd.mostrarBD();
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
