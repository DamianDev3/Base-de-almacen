#include "../include/Menus.h"
#include "Ventas.h"
#include "../include/Categorias.h"
#include "../include/subCategoria.h"
#include "../include/BasedeAlmacen.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Productos.h"
#include "../include/ClaseUsuarios.h"
#include "../include/Selector.h"
#include "../include/MovimientoStock.h"
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
    MovimientoStock movimiento;

    ClaseUsuarios usuarioLogeado = bd.validarUsuario();
    ClaseUsuarios::setUsuarioLogeado(usuarioLogeado);
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
        {9, "Modificar stock"},
        {10, "Movimientos de stock"},
        {11,"Comprar hoy generado"},
        {12,"Modificar subcategoria"},
        {0, "Salir del programa"}
    };

    do
    {
       /// cout << "Usuario: " << "" << ClaseUsuarios::getUsuarioLogeado().getNombreUsuario() <<endl;
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
            bd.venderProducto();
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
            case 9:
            bd.correccionStockGeneral();
            break;
        case 10:
            bd.MovimientosStock();
            break;
       
        case 11:
            movimiento.comprarHoy();
            break;
       
        case 12:
            bd.SubcategoriasMod();
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
