#include "../include/Menus.h"
#include "Ventas.h"
#include "../include/Categorias.h"
#include "../include/subCategoria.h"
#include "../include/BasedeAlmacen.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Productos.h"
#include "../include/ClaseUsuarios.h"
#include "../include/Selector.h"
#include "windows.h"
#include <iostream>
using namespace std;

void Menus::Menugeneral()
{
    bool condicion = false;
    Ventas venta;
    BasedeAlmacen almacen;
    Categorias cat;
    Productos productin;
    subCategoria subCat;
    GestorBaseDatos bd;
    ClaseUsuarios altaUser;

    const std::vector<std::pair<int, std::string>> opcionesDelMenu =
    {
        {1, "Alta de usuario"},
        {2, "Mostrar Almacen"},
        {3, "Leer producto"},
        {4, "Comprar producto"},
        {5, "Modificar categorias"},
        {6, "Ultima venta realizada"},
        {7, "Ultimo detalle de venta"},
        {8, "Ultimo pago de venta"},
        {0, "Salir del programa"}
    };

    do
    {
        int opciones = Selector::elegirOpcion("Menu General", opcionesDelMenu);

        if (opciones == Selector::CANCELADO)
        {
            // Sin entrada (fin de archivo) o cancelado: se sale del programa.
            condicion = true;
            break;
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
            bd.CategoriasMod();
            break;
        case 6:
            bd.mostrarUltimaVenta();
            break;
        case 7:
            bd.mostrarUltimoDetalle();
            break;
        case 8:
            bd.mostrarUltimoPago();
            break;
        case 0:
            cout << "SALIENDO DEL PROGRAMA:" << endl;
            system("pause");
            condicion = true;
            break;
        default:
            break;
        }
    } while (!condicion);
}
