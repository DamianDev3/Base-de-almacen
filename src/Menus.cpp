#include "../include/Menus.h"
#include "Ventas.h"
#include "../include/Categorias.h"
#include "../include/subCategoria.h"
#include "../include/BasedeAlmacen.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Productos.h"
#include "../include/ClaseUsuarios.h"
#include "windows.h"
#include <iostream>
using namespace std;

void Menus::Menugeneral()
{
    /// porto menu todavia no esta listo.
    int opciones;
    bool condicion = false;
    Ventas venta;
    BasedeAlmacen almacen;
    Categorias cat;
    Productos productin;
    subCategoria subCat;
    GestorBaseDatos bd;
    ClaseUsuarios altaUser;
    
    do 
    {
        system("cls");
        
        cout << "Menu General:" <<endl;
        cout << "Ingresar opcion deseada:" << endl;
        cout << "1- Alta de usuario:" <<endl;
        cout << "2- Mostrar Almacen:" <<endl;
        cout << "3- Leer producto:" <<endl;
        cout << "4- Comprar producto:" <<endl;
        cout << "5- Ventas:" <<endl;
        cout << "6- Modificar categorias:" <<endl;
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
        altaUser.cargaDeUsuario();
        break;
        case 2:
        bd.AlmacenInventario();
        break;
        case 3:
        productin.lecturaProducto();
            break;
            case 4:
            bd.comprarProducto();
            break;
            case 5:
            bd.registrarVenta();
            break; 
            case 6:
            bd.CategoriasMod();
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
