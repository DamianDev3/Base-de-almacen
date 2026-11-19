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

    do
    {
        std::vector<std::pair<int, std::string>> opcionesDelMenu =
        {
            {1, "Alta de usuario"},
            {2, "Mostrar Almacen"},
            {3, "Leer producto"},
            {4, "Vender producto"},
            {5, "Modificar categorias"},
            {6, "Ultima venta realizada"},
            {7, "Ultimo detalle de venta"},
            {8, "Ultimo pago de venta"},
            {9, "Modificar stock"},
            {10, "Movimientos de stock"},
            {12, "Modificar subcategoria"},
            {13, "Alta de producto"},
            {15, "Historial compras automaticas"},
            {0, "Salir del programa"}
        };

      
        if (usuarioLogeado.getRolUsuario() == "ADMINISTRADOR" && bd.consultarStock())
        {
            opcionesDelMenu.push_back({99, "Generar compra de hoy (stock bajo)"});
           /*  bd.generarCompraDehoy(); */
        }

        int opciones = Selector::elegirOpcion("Menu General", opcionesDelMenu);

        if (opciones == Selector::CANCELADO)
        {
  
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
       
       
        case 12:
            bd.SubcategoriasMod();
            break;

        case 13:
            productin.altaProducto();
            break;

        case 14:
            cout << endl;
            cout << "=======================================================" << endl;
            cout << " Compra de hoy: la funcion todavia no esta conectada." << endl;
            cout << " (Opcion disponible para el Administrador)" << endl;
            cout << "=======================================================" << endl;
            system("pause");
            break;

        case 15:
            bd.compraHoyHistorial();
            break;

        case 99:
            bd.generarCompraDehoy();
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
