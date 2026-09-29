#include "../include/GestorBaseDatos.h"
#include "../include/Productos.h"
#include "../include/subCategoria.h"
#include "../include/Categorias.h"
#include "../include/ClaseUsuarios.h"
#include "../include/Ventas.h"
#include "../include/Selector.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include "../lib/sqlite_orm/sqlite_orm.h"

using namespace std;
using namespace sqlite_orm;

/// Mapeo ORM de las tablas de la base de datos.
/// Todas las funciones del gestor trabajan con este storage.
namespace
{
    struct CategoriaORM
    {
        int id;
        string nombre;
    };

    struct SubcategoriaORM
    {
        int id;
        string nombre;
        int idCategoria;
    };

    struct VentaORM
    {
        int idVenta = 0;
        string fechaHora;
        string vendedor;
        float totalVenta = 0;
        float totalPagado = 0;
        float diferenciaPago = 0;
        string estadoVenta;
        string anuladaPor;
        string fechaHoraAnulacion;
        string motivoAnulacion;
        string observacion;
    };

    struct DetalleVentaORM
    {
        int idDetalle = 0;
        int idVenta = 0;
        int codigoInterno = 0;
        string eanLeido;
        string productoSnapshot;
        float precioVendido = 0;
        int cantidad = 0;
        float subtotal = 0;
    };

    struct PagoVentaORM
    {
        int idPago = 0;
        int idVenta = 0;
        string medioPago;
        float importe = 0;
    };

    auto crearStorageAlmacen()
    {
        return make_storage("db/Almacen.db",
            make_table("Productos",
                make_column("id_producto", &Productos::getIdProducto, &Productos::setIdProducto, primary_key()),
                make_column("eanProductos", &Productos::getEan, &Productos::setEan, unique()),
                make_column("nombreProductos", &Productos::getNombreProducto, &Productos::setNombreProducto),
                make_column("MarcaProductos", &Productos::getMarcaProducto, &Productos::setMarcaProducto),
                make_column("variantes", &Productos::getVariantes, &Productos::setVariantes),
                make_column("contenido", &Productos::getContenido, &Productos::setContenido),
                make_column("unidades_pack", &Productos::getUnidades, &Productos::setUnidades),
                make_column("precio_venta", &Productos::getPrecio, &Productos::setPrecio),
                make_column("stock_minimo", &Productos::getStockMinimo, &Productos::setStockMinimo),
                make_column("stock_objetivo", &Productos::getStockObjetivo, &Productos::setStockObjetivo),
                make_column("stock_actual", &Productos::getStockActual, &Productos::setStockActual),
                make_column("id_subcategoria", &Productos::getIdSubcategoria, &Productos::setIdSubcategoria)),
            make_table("Categorias",
                make_column("id", &CategoriaORM::id, primary_key(), autoincrement()),
                make_column("nombre_categorias", &CategoriaORM::nombre)),
            make_table("Subcategorias",
                make_column("id", &SubcategoriaORM::id, primary_key()),
                make_column("nombre_subcategorias", &SubcategoriaORM::nombre),
                make_column("id_categoria", &SubcategoriaORM::idCategoria)),
            make_table("Usuarios",
                make_column("id_usuarios", &ClaseUsuarios::getIdUsuario, &ClaseUsuarios::setIdUsuario, primary_key(), autoincrement()),
                make_column("Nombre_usuario", &ClaseUsuarios::getNombreUsuario, &ClaseUsuarios::setNombreUsuario, unique()),
                make_column("Apellido_usuario", &ClaseUsuarios::getApellidoUsuario, &ClaseUsuarios::setApellidoUsuario),
                make_column("Password_usuario", &ClaseUsuarios::getPassword, &ClaseUsuarios::setPassword),
                make_column("Rol_usuario", &ClaseUsuarios::getRolUsuario, &ClaseUsuarios::setRolUsuario)),
            make_table("Ventas",
                make_column("id_venta", &VentaORM::idVenta, primary_key(), autoincrement()),
                make_column("fecha_hora", &VentaORM::fechaHora),
                make_column("vendedor", &VentaORM::vendedor),
                make_column("total_venta", &VentaORM::totalVenta),
                make_column("total_pagado", &VentaORM::totalPagado),
                make_column("diferencia_pago", &VentaORM::diferenciaPago),
                make_column("estado_venta", &VentaORM::estadoVenta),
                make_column("anulada_por", &VentaORM::anuladaPor),
                make_column("fecha_hora_anulacion", &VentaORM::fechaHoraAnulacion),
                make_column("motivo_anulacion", &VentaORM::motivoAnulacion),
                make_column("observacion", &VentaORM::observacion)),
            make_table("Detalle_Ventas",
                make_column("id_detalle", &DetalleVentaORM::idDetalle, primary_key(), autoincrement()),
                make_column("id_venta", &DetalleVentaORM::idVenta),
                make_column("codigo_interno", &DetalleVentaORM::codigoInterno),
                make_column("ean_leido", &DetalleVentaORM::eanLeido),
                make_column("producto_snapshot", &DetalleVentaORM::productoSnapshot),
                make_column("precio_vendido", &DetalleVentaORM::precioVendido),
                make_column("cantidad", &DetalleVentaORM::cantidad),
                make_column("subtotal", &DetalleVentaORM::subtotal)),
            make_table("Pagos_Venta",
                make_column("id_pago", &PagoVentaORM::idPago, primary_key(), autoincrement()),
                make_column("id_venta", &PagoVentaORM::idVenta),
                make_column("medio_pago", &PagoVentaORM::medioPago),
                make_column("importe", &PagoVentaORM::importe)));
    }
}

GestorBaseDatos::GestorBaseDatos() {
    _db = nullptr;
}

GestorBaseDatos::~GestorBaseDatos() {
    desconectar();
}

/// Conexion directa a sqlite (se mantiene por compatibilidad con las otras clases)
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

void GestorBaseDatos::AlmacenInventario()
{
    /// Muestra todos los productos con su categoria y subcategoria (inner join)
    auto storage = crearStorageAlmacen();

    auto inventario = storage.select(
        columns(&Productos::getIdProducto,
                &Productos::getNombreProducto,
                &CategoriaORM::nombre,
                &SubcategoriaORM::nombre,
                &Productos::getPrecio,
                &Productos::getStockMinimo,
                &Productos::getStockObjetivo),
        inner_join<SubcategoriaORM>(on(c(&Productos::getIdSubcategoria) == &SubcategoriaORM::id)),
        inner_join<CategoriaORM>(on(c(&SubcategoriaORM::idCategoria) == &CategoriaORM::id)),
        multi_order_by(order_by(&CategoriaORM::id), order_by(&SubcategoriaORM::id), order_by(&Productos::getNombreProducto)));

    if (inventario.empty())
    {
        system("cls");
        cout << "================================================================================" << endl;
        cout << "                             BASE DE ALMACEN - PRODUCTOS                        " << endl;
        cout << "================================================================================" << endl;
        cout << " No hay productos cargados en la base de datos." << endl;
        system("pause");
        return;
    }

    const int elementosPorPagina = 20;
    int totalRegistros = static_cast<int>(inventario.size());
    int totalPaginas = (totalRegistros + elementosPorPagina - 1) / elementosPorPagina;
    int paginaActual = 0;

    char comando = ' ';

    while (comando != '0')
    {
        system("cls");
        cout << "================================================================================" << endl;
        cout << "                             BASE DE ALMACEN - PRODUCTOS                        " << endl;
        cout << " Pagina " << (paginaActual + 1) << " de " << totalPaginas 
             << " | Total productos: " << totalRegistros << endl;
        cout << "================================================================================" << endl;

        int inicio = paginaActual * elementosPorPagina;
        int fin = std::min(inicio + elementosPorPagina, totalRegistros);

        for (int i = inicio; i < fin; ++i)
        {
            auto &fila = inventario[i];
            cout << " ID " << get<0>(fila)
                 << " | " << get<1>(fila)
                 << " | Categoria: " << get<2>(fila)
                 << " | Subcategoria: " << get<3>(fila)
                 << " | $" << get<4>(fila)
                 << " | Stock min: " << get<5>(fila)
                 << " | Stock obj: " << get<6>(fila) << endl;
        }

        cout << "================================================================================" << endl;
        cout << " [N] o [->] Siguiente | [P] o [<-] Anterior | [0] o [Enter] Volver al menu" << endl;
        cout << " Opcion: ";

        int tecla = Selector::leerTecla();

        if (tecla == 'n' || tecla == 'N' || tecla == Selector::TECLA_DERECHA || tecla == Selector::TECLA_ABAJO)
        {
            if (paginaActual + 1 < totalPaginas)
            {
                paginaActual++;
            }
            else
            {
                cout << "\n Ya estas en la ultima pagina." << endl;
                system("pause");
            }
        }
        else if (tecla == 'p' || tecla == 'P' || tecla == Selector::TECLA_IZQUIERDA || tecla == Selector::TECLA_ARRIBA)
        {
            if (paginaActual > 0)
            {
                paginaActual--;
            }
            else
            {
                cout << "\n Ya estas en la primera pagina." << endl;
                system("pause");
            }
        }
        else if (tecla == '0' || tecla == Selector::TECLA_ENTER || tecla == Selector::TECLA_ESCAPE || tecla == Selector::TECLA_FIN)
        {
            comando = '0';
        }
        else
        {
            cout << "\n Tecla no valida. Usa N, P, 0 o las flechas." << endl;
            system("pause");
        }
    }
}

bool GestorBaseDatos::buscarPorProducto(const char* eanBuscado)
{
    auto storage = crearStorageAlmacen();

    auto productos = storage.get_all<Productos>(where(c(&Productos::getEan) == string(eanBuscado)));
    if (productos.empty())
    {
        cout << endl << "[!] No se encontro un producto con el EAN " << eanBuscado << endl;
        system("pause");
        return false;
    }

    for (auto &prod : productos)
    {
        cout << endl << "----------------------------------------" << endl;
        cout << "Producto : " << prod.getNombreProducto() << endl;
        cout << "Marca    : " << prod.getMarcaProducto() << endl;
        cout << "Precio   : $" << prod.getPrecio() << endl;
        cout << "Stock    : " << prod.getStockActual() << endl;
        cout << "----------------------------------------" << endl;
    }
    system("pause");
    return true;
}

void GestorBaseDatos::mostrarBD(int limite)
{
    auto storage = crearStorageAlmacen();

    auto productos = storage.get_all<Productos>(
        order_by(&Productos::getNombreProducto),
        limit(limite));

    cout << "================================================================================" << endl;
    cout << "                             BASE DE ALMACEN - PRODUCTOS                        " << endl;
    cout << "================================================================================" << endl;

    if (productos.empty())
    {
        cout << " No hay productos cargados en la base de datos." << endl;
    }

    for (auto &prod : productos)
    {
        cout << " [" << prod.getEan() << "] " << prod.getNombreProducto()
             << " | $" << prod.getPrecio()
             << " | Stock: " << prod.getStockActual() << endl;
    }

    cout << "================================================================================" << endl;
    system("pause");
}

void GestorBaseDatos::buscarCategoria(int idBuscadocat)
{
    /// Busca la categoria por ID y muestra sus subcategorias y productos.
    auto storage = crearStorageAlmacen();

    auto categorias = storage.get_all<CategoriaORM>(where(c(&CategoriaORM::id) == idBuscadocat));
    if (categorias.empty())
    {
        cout << endl << "[!] No se encontro la categoria con ID: " << idBuscadocat << endl;
        system("pause");
        return;
    }

    CategoriaORM categoria = categorias.front();

    cout << endl << "=======================================================" << endl;
    cout << " CATEGORIA: " << categoria.nombre << " (ID: " << idBuscadocat << ")" << endl;
    cout << "=======================================================" << endl;

    auto subcategorias = storage.get_all<SubcategoriaORM>(
        where(c(&SubcategoriaORM::idCategoria) == idBuscadocat),
        order_by(&SubcategoriaORM::nombre));

    if (subcategorias.empty())
    {
        cout << "  (La categoria no tiene subcategorias cargadas)" << endl;
    }

    for (auto &sub : subcategorias)
    {
        cout << endl << "  -- Subcategoria: " << sub.nombre << endl;

        auto productos = storage.get_all<Productos>(
            where(c(&Productos::getIdSubcategoria) == sub.id),
            order_by(&Productos::getNombreProducto));

        if (productos.empty())
        {
            cout << "     (No hay productos registrados en esta subcategoria)" << endl;
        }

        for (auto &prod : productos)
        {
            cout << "     * [" << prod.getEan() << "] "
                 << prod.getNombreProducto()
                 << " | $" << prod.getPrecio()
                 << " | Stock: " << prod.getStockActual() << endl;
        }
    }

    cout << "=======================================================" << endl << endl;
    system("pause");
}

int GestorBaseDatos::elegirCategoria(const std::string& titulo)
{
    /// Devuelve el ID de la categoria elegida por el usuario, o Selector::CANCELADO.
    auto storage = crearStorageAlmacen();

    auto categorias = storage.get_all<CategoriaORM>(order_by(&CategoriaORM::id));
    if (categorias.empty())
    {
        cout << "No hay categorias cargadas en la base de datos." << endl;
        system("pause");
        return Selector::CANCELADO;
    }

    std::vector<std::pair<int, std::string>> lista;
    for (auto &cat : categorias)
    {
        lista.push_back(std::make_pair(cat.id, cat.nombre));
    }

    return Selector::elegirDeLista(titulo, lista);
}

ClaseUsuarios GestorBaseDatos::validarUsuario()
{
    string nombreUser, contraseniaUser, apellidoUser;
    bool encontrado = false;

    do
    {
        system("cls");
        cout << "---------------------------------------------------------------------" << endl;
        cout << "INICIO DE SESION / VALIDACION DE CREDENCIALES" << endl;
        cout << "Para cancelar oprima 0 (cero)" <<endl;
        cout << "---------------------------------------------------------------------" << endl;    
        cout << "Nombre: ";
        cin >> nombreUser;

        if (cin.eof())
        {
            cout << "Inicio de sesion cancelado." << endl;
            system("pause");
            return ClaseUsuarios();
        }

        if (nombreUser == "0")
        {
            cout << "Inicio de sesion cancelado:" <<endl;
            system ("pause");
            return ClaseUsuarios(); // Retorna un objeto vacío para cancelar
        }

        cout << "Apellido: ";
        cin >> apellidoUser;
        cout << "Contraseña: ";
        cin >> contraseniaUser;
        cin.ignore(10000, '\n');
        
        auto rolUsuario = crearStorageAlmacen();
        auto ususarioPermisos = rolUsuario.get_all<ClaseUsuarios>(
            where(c(&ClaseUsuarios::getNombreUsuario) == nombreUser and 
                  c(&ClaseUsuarios::getApellidoUsuario) == apellidoUser and 
                  c(&ClaseUsuarios::getPassword) == contraseniaUser)
        );
        
        if (ususarioPermisos.empty())
        {
            cout << "\nError: usuario o contrasenia no corresponde a uno registrado." << endl;
            cout << "Vuelva a intentar..." << endl;
            system("pause");
        }
        else
        {
            // Se extrae la instancia completa encontrada
            ClaseUsuarios usuarioLogueado = ususarioPermisos.front();

            cout << "\nUSUARIO ENCONTRADO:" << endl;
            cout << "Nombre: " << usuarioLogueado.getNombreUsuario() << endl;
            cout << "Apellido: " << usuarioLogueado.getApellidoUsuario() << endl;
            cout << "Rol asignado: " << usuarioLogueado.getRolUsuario() << endl;
            
            system("pause");
            return usuarioLogueado; // Retorna el objeto completo
        }
        
    } while (!encontrado);

    return ClaseUsuarios();
}

void GestorBaseDatos::ModificarStockGeneral()
{
    ClaseUsuarios usuarioLogueado = validarUsuario();
    if (usuarioLogueado.getRolUsuario() == "ADMINISTRADOR" || usuarioLogueado.getRolUsuario() == "LOGISTICA")
    {
       cout <<"PERMISOS PARA MODIFICAR EL STOCK:"<<endl;
    }
    else
    {
         cout << "Usted no tiene los permisos para corregir el stock:" <<endl;
        system ("pause");
        return;
    }

    auto storage = crearStorageAlmacen();

    auto productos = storage.get_all<Productos>(order_by(&Productos::getNombreProducto));
    if (productos.empty())
    {
        cout << "No hay productos cargados en la base de datos." << endl;
        return;
    }

    for (auto &prod : productos)
    {
        cout << "\n----------------------------------------" << endl;
        cout << "Producto: " << prod.getNombreProducto() << endl;
        cout << "Stock actual registrado: " << prod.getStockActual() << endl;

        if (Selector::confirmar("¿Desea cambiar el stock de este producto?"))
        {
            int nuevoStock = 0;
            cout << "Ingrese el nuevo stock actual: ";
            cin >> nuevoStock;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "[Error al guardar en BD]" << endl;
                continue;
            }

            prod.setStockActual(nuevoStock);

            try
            {
                storage.update(prod);
                cout << "[Guardado en BD con exito]" << endl;
            }
            catch (const std::exception &e)
            {
                cout << "[Error al guardar en BD] " << e.what() << endl;
            }
        }
    }
}

void GestorBaseDatos::SubcategoriasMod()
{
        ClaseUsuarios usuarioLogueado = validarUsuario();
    if (usuarioLogueado.getRolUsuario() == "ADMINISTRADOR" || usuarioLogueado.getRolUsuario() == "LOGISTICA")
    {
       cout <<"PERMISOS PARA MODIFICAR EL STOCK:"<<endl;
    }
    else
    {
         cout << "Usted no tiene los permisos para corregir el stock:" <<endl;
        system ("pause");
        return;
    }


    auto storage = crearStorageAlmacen();

    auto subcategorias = storage.get_all<SubcategoriaORM>(order_by(&SubcategoriaORM::id));

    for (auto &sub : subcategorias)
    {
        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << sub.id << " | Subcategoria actual: " << sub.nombre << endl;

        if (Selector::confirmar("¿Desea renombrar esta subcategoria?"))
        {
            string modificarNombre;
            cout << "Ingrese el nuevo nombre: ";
            cin >> ws;
            getline(cin, modificarNombre);

            sub.nombre = modificarNombre;

            try
            {
                storage.update(sub);
                cout << "[Guardado con exito en la base de datos]" << endl;
            }
            catch (const std::exception &e)
            {
                cout << "Error al actualizar: " << e.what() << endl;
            }
        }
    }
}

void GestorBaseDatos::CategoriasMod()
{
    bool modificado = false;
    /// 1) Validación de permisos: solo Administrador
    ClaseUsuarios usuarioLogueado = validarUsuario();
    if (usuarioLogueado.getRolUsuario() != "ADMINISTRADOR")
    {
        cout << "Usted no tiene los permisos para modificar las categorias." << endl;
        system("pause");
        return;
    }

    /// 2) Menú inicial de decisión
    do
    {
        int opcion = Selector::elegirOpcion(
            "Gestion de categorias - ADMINISTRADOR: " + usuarioLogueado.getNombreUsuario() + " " + usuarioLogueado.getApellidoUsuario(),
            {
                {1, "Modificar una categoria existente"},
                {2, "Crear una nueva categoria"},
                {0, "Volver al menu principal"}
            });

        if (opcion == Selector::CANCELADO)
        {
            return;
        }

        auto storage = crearStorageAlmacen();

        switch (opcion)
        {
            case 1:
            {
                /// --- Modificar categoría existente ---
                auto categorias = storage.get_all<CategoriaORM>(order_by(&CategoriaORM::id));
                if (categorias.empty())
                {
                    cout << "\nNo hay categorias cargadas en la base de datos para modificar." << endl;
                    system("pause");
                    return;
                }

                std::vector<std::pair<int, std::string>> listaCategorias;
                for (const auto &cat : categorias)
                {
                    listaCategorias.push_back(std::make_pair(cat.id, cat.nombre));
                }

                int idCategoria = Selector::elegirDeLista("Modificar categoria - Elegir cual", listaCategorias);
                if (idCategoria == Selector::CANCELADO)
                {
                    break;
                }

                // Buscar la categoría por su ID
                CategoriaORM categoriaElegida;
                bool encontrada = false;
                for (const auto &cat : categorias)
                {
                    if (cat.id == idCategoria)
                    {
                        categoriaElegida = cat;
                        encontrada = true;
                        break;
                    }
                }

                if (!encontrada)
                {
                    cout << "No existe ninguna categoria con ID " << idCategoria << endl;
                    system("pause");
                    break;
                }
    
                cout << "Nombre actual: " << categoriaElegida.nombre << endl;
                cout << "Ingrese el nuevo nombre: ";
                string nuevoNombre;
                cin >> ws;
                getline(cin, nuevoNombre);
    
                if (nuevoNombre.empty())
                {
                    cout << "El nombre no puede quedar vacio." << endl;
                    system("pause");
                    return;
                }
    
                categoriaElegida.nombre = nuevoNombre;
    
                try
                {
                    storage.update(categoriaElegida);
                    cout << "Categoria modificada con exito." << endl;
                }
                catch (const std::exception &e)
                {
                    cout << "Error al actualizar los datos: " << e.what() << endl;
                }
                system("pause");
                break;
            }
    
            case 2:
            {
                system("cls");
                /// --- Crear una nueva categoría ---
                cout << "\nIngrese el nombre de la nueva categoria: ";
                string nuevoNombre;
                cin >> ws;
                getline(cin, nuevoNombre);
    
                if (nuevoNombre.empty())
                {
                    cout << "El nombre no puede quedar vacio." << endl;
                    system("pause");
                    return;
                }
    
                try
                {
                    CategoriaORM nuevaCategoria;
                    nuevaCategoria.id = 0; // SQLite asigna el autoincrement
                    nuevaCategoria.nombre = nuevoNombre;
                    storage.insert(nuevaCategoria);
                    cout << "Categoria creada con exito." << endl;
                }
                catch (const std::exception &e)
                {
                    cout << "Error al crear la categoria: " << e.what() << endl;
                }
                system("pause");
                break;
            }
    
            case 0:
                return;
    
            default:
                cout << "Opcion no valida." << endl;
                system("pause");
                break;
        }
    } while (!modificado);
    
}

void GestorBaseDatos::AltaDeUsuario(string nombreu, string apellidou, string roluser, string password)
{
    auto storage = crearStorageAlmacen();

    try
    {
        ClaseUsuarios usuario;
        usuario.setNombreUsuario(nombreu);
        usuario.setApellidoUsuario(apellidou);
        usuario.setPassword(password);
        usuario.setRolUsuario(roluser);

        storage.insert(usuario);
        cout << "USUARIO AGREGADO!!" << endl;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR AL INGRESAR AL USUARIO: " << e.what() << endl;
    }
}

void GestorBaseDatos::comprarProducto()
{
    ClaseUsuarios userComplete = validarUsuario();

    if(userComplete.getRolUsuario() != "ADMINISTRADOR" && userComplete.getRolUsuario() != "VENDEDOR")
    {
        cout << "Usted no tiene permisos para comprar:" <<endl;
        system("pause");
        return;
    }
    /////bool cancelarCarga = false;
    auto storage = crearStorageAlmacen();

    system ("cls");
    cout << endl << "=========== COMPRAR PRODUCTO  ===========" << endl;

    /// --- 1) Elegir la categoria ---
    auto categorias = storage.get_all<CategoriaORM>(order_by(&CategoriaORM::id));
    if (categorias.empty())
    {
        cout << "No hay categorias cargadas en la base de datos." << endl;
        system("pause");
        return;
    }

    std::vector<std::pair<int, std::string>> listaCategorias;
    for (auto &cat : categorias)
    {
        listaCategorias.push_back(std::make_pair(cat.id, cat.nombre));
    }

    int idCategoria = Selector::elegirDeLista("Comprar producto - Elegir categoria", listaCategorias);
    if (idCategoria == Selector::CANCELADO)
    {
        cout << "Compra cancelada." << endl;
        system("pause");
        return;
    }

    CategoriaORM categoriaElegida;
    for (auto &cat : categorias)
    {
        if (cat.id == idCategoria)
        {
            categoriaElegida = cat;
            break;
        }
    }

    /// --- 2) Elegir la subcategoria de esa categoria ---
    auto subcategorias = storage.get_all<SubcategoriaORM>(
        where(c(&SubcategoriaORM::idCategoria) == idCategoria),
        order_by(&SubcategoriaORM::id));

    if (subcategorias.empty())
    {
        cout << "La categoria elegida no tiene subcategorias cargadas." << endl;
        system("pause");
        return;
    }

    std::vector<std::pair<int, std::string>> listaSubcategorias;
    for (auto &sub : subcategorias)
    {
        listaSubcategorias.push_back(std::make_pair(sub.id, sub.nombre));
    }

    int idSubcategoria = Selector::elegirDeLista("Comprar producto - Elegir subcategoria", listaSubcategorias);
    if (idSubcategoria == Selector::CANCELADO)
    {
        cout << "Compra cancelada." << endl;
        system("pause");
        return;
    }

    SubcategoriaORM subcategoriaElegida;
    for (auto &sub : subcategorias)
    {
        if (sub.id == idSubcategoria)
        {
            subcategoriaElegida = sub;
            break;
        }
    }

    /// --- 3) Mostrar los productos de esa subcategoria ---
    auto productos = storage.get_all<Productos>(
        where(c(&Productos::getIdSubcategoria) == idSubcategoria),
        order_by(&Productos::getNombreProducto));

    if (productos.empty())
    {
        cout << "No hay productos cargados en esa subcategoria." << endl;
        system("pause");
        return;
    }
    std::vector<std::pair<int, std::string>> listaProductos;
    for (auto &prod : productos)
    {
        std::ostringstream texto;
        texto << prod.getNombreProducto()
              << " | Precio: $" << prod.getPrecio()
              << " | Stock: " << prod.getStockActual();
        listaProductos.push_back(std::make_pair(prod.getIdProducto(), texto.str()));
    }

    /// --- 4) Elegir el producto a comprar ---
    int idProducto = Selector::elegirDeLista(
        "Comprar producto - " + categoriaElegida.nombre + " / " + subcategoriaElegida.nombre,
        listaProductos);

    if (idProducto == Selector::CANCELADO)
    {
        cout << "Compra cancelada." << endl;
        system("pause");
        return;
    }

    Productos producto;
    bool productoEncontrado = false;
    for (auto &prod : productos)
    {
        if (prod.getIdProducto() == idProducto)
        {
            producto = prod;
            productoEncontrado = true;
            break;
        }
    }
    if (!productoEncontrado)
    {
        cout << "No se encontro el producto elegido." << endl;
        system("pause");
        return;
    }

    /// --- 5) Cantidad a comprar (se descuenta automaticamente del stock) ---
    int cantidad = 0;
    bool cantidadValida = false;

    while (!cantidadValida)
    {
        cout << endl << "Stock actual: " << producto.getStockActual() << " unidades." << endl;
        cout << "Cantidad a comprar (0 para cancelar): ";
        cin >> cantidad;

        if (cin.fail())
        {
            if (cin.eof())
            {
                cout << endl << "Sin entrada. Compra cancelada." << endl;
                system("pause");
                return;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Cantidad invalida." << endl;
            continue;
        }

        if (cantidad == 0)
        {
            cout << "Compra cancelada." << endl;
            system("pause");
            return;
        }

        if (cantidad < 0)
        {
            cout << "Cantidad invalida (debe ser mayor a cero)." << endl;
            continue;
        }

        if (cantidad > producto.getStockActual())
        {
            cout << "Stock insuficiente: quedan " << producto.getStockActual() << " unidades." << endl;
            continue;
        }

        cantidadValida = true;
    }

    /// --- 6) Descontar la cantidad del stock y guardar con el ORM ---
    int stockAnterior = producto.getStockActual();
    producto.setStockActual(stockAnterior - cantidad);

    try
    {
        storage.update(producto);
        cout << endl << "[Stock actualizado en la base de datos]" << endl;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al guardar el descuento: " << e.what() << endl;
        system("pause");
        return;
    }

    /// --- 7) Venta: se completan los datos (vendedor y pago) ---
    auto productoVerificado = storage.get<Productos>(producto.getIdProducto());

    cout << endl << "Stock actualizado: " << stockAnterior
         << " -> " << productoVerificado.getStockActual()
         << "  (-" << cantidad << ")" << endl;

    Ventas venta;
    venta.realizarVenta(productoVerificado, cantidad);

    /// --- 8) Guardar la venta en la base: Ventas + Detalle_Ventas + Pagos_Venta ---
    int idVentaGuardada = 0;
    try
    {
        storage.transaction([&]() mutable {

            VentaORM ventaORM;
            ventaORM.fechaHora = venta.getFechaHoraSQL();
            ventaORM.vendedor = venta.getVendedor();
            ventaORM.totalVenta = venta.getTotalVenta();
            ventaORM.totalPagado = venta.getTotalPagado();
            ventaORM.diferenciaPago = venta.getDiferenciaPago();
            ventaORM.estadoVenta = venta.getEstadoVenta() ? "CONFIRMADA" : "ANULADA";
            ventaORM.anuladaPor = "";
            ventaORM.fechaHoraAnulacion = "";
            ventaORM.motivoAnulacion = "";
            ventaORM.observacion = "";

            idVentaGuardada = storage.insert(ventaORM);

            DetalleVentaORM detalle;
            detalle.idVenta = idVentaGuardada;
            detalle.codigoInterno = productoVerificado.getIdProducto();
            detalle.eanLeido = productoVerificado.getEan();
            detalle.productoSnapshot = productoVerificado.getNombreProducto();
            detalle.precioVendido = productoVerificado.getPrecio();
            detalle.cantidad = cantidad;
            detalle.subtotal = productoVerificado.getPrecio() * cantidad;
            storage.insert(detalle);

            PagoVentaORM pago;
            pago.idVenta = idVentaGuardada;
            pago.medioPago = "EFECTIVO";
            pago.importe = venta.getTotalPagado();
            storage.insert(pago);

            return true;
        });

        venta.setIdVenta(idVentaGuardada);
        cout << endl << "[Venta guardada en la base de datos - N° " << idVentaGuardada << "]" << endl;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al guardar la venta en la base: " << e.what() << endl;
    }

    /// --- 9) Ticket de la venta ---
    venta.mostrarTicket(productoVerificado, cantidad);

    cout << "Recordatorio: los ajustes manuales de stock los realiza aparte" << endl;
    cout << "un usuario con permisos (ADMINISTRADOR / LOGISTICA)." << endl;
    system("pause");
}

void GestorBaseDatos::registrarVenta()
{
    
   auto snapshotVenta = crearStorageAlmacen();
   auto datosDeVenta = snapshotVenta.get_all<VentaORM>(order_by(&VentaORM::idVenta));
   char porsiOporno;

   cout << "===== TICKET DE VENTA ======" <<endl;
   cout << "Vendedor: " << endl;
   cout << "Total pagado: "<< endl;
   cout << "Diferencia de pago: "<< endl;
   cout << "Estado de venta: " << endl;
  /*  
   cout << "¿Desea cancelar la venta?:" <<endl;
 if(porsiOporno == 's'|| porsiOporno == 'S')
 {
       cout << "===== Datos de Anulacion ====" << endl;
       cout << "Anulada por: "<< endl;
       cout << "Fecha y hora de anulacion: " << endl;
       cout << "Motivo de anulacion: " << endl;
       cout << "Observacion: "  << endl;
       cout << "Venta temrinada, gracias por comprar:" << endl; 

 }
 */
    system ("pause");
   }

void GestorBaseDatos::mostrarUltimaVenta()
{
    /// Muestra la ultima venta guardada en la base de datos (con su detalle y pago).
    auto storage = crearStorageAlmacen();

    auto ventas = storage.get_all<VentaORM>(order_by(&VentaORM::idVenta));
    if (ventas.empty())
    {
        cout << endl << "[!] No hay ventas registradas en la base de datos." << endl;
        system("pause");
        return;
    }

    VentaORM ultima = ventas.back();

    auto detalles = storage.get_all<DetalleVentaORM>(
        where(c(&DetalleVentaORM::idVenta) == ultima.idVenta));
    auto pagos = storage.get_all<PagoVentaORM>(
        where(c(&PagoVentaORM::idVenta) == ultima.idVenta));

    cout << endl;
    cout << "================= ULTIMA VENTA REGISTRADA =================" << endl;
    cout << " Venta N° : " << ultima.idVenta << endl;
    cout << " Fecha    : " << ultima.fechaHora << endl;
    cout << " Vendedor : " << ultima.vendedor << endl;
    cout << " ---------------------------------------------------------" << endl;

    for (auto &det : detalles)
    {
        cout << " Producto : " << det.productoSnapshot << endl;
        cout << " Cantidad : " << det.cantidad << endl;
        cout << " Precio   : $" << det.precioVendido << endl;
        cout << " Subtotal : $" << det.subtotal << endl;
        cout << " ---------------------------------------------------------" << endl;
    }

    cout << " TOTAL    : $" << ultima.totalVenta << endl;
    cout << " Pagado   : $" << ultima.totalPagado << endl;
    if (ultima.diferenciaPago >= 0.0f)
    {
        cout << " Vuelto   : $" << ultima.diferenciaPago << endl;
    }
    else
    {
        cout << " Falta    : $" << -ultima.diferenciaPago << endl;
    }
    if (!pagos.empty())
    {
        cout << " Pago     : " << pagos.front().medioPago << endl;
    }
    cout << " Estado   : " << ultima.estadoVenta << endl;

    if (ultima.estadoVenta != "CONFIRMADA")
    {
        cout << " ------- Datos de anulacion -------" << endl;
        cout << " Anulada por : " << ultima.anuladaPor << endl;
        cout << " Fecha/hora  : " << ultima.fechaHoraAnulacion << endl;
        cout << " Motivo      : " << ultima.motivoAnulacion << endl;
    }

    cout << " Observacion : " << ultima.observacion << endl;
    cout << "============================================================" << endl;

    system("pause");
}

   
