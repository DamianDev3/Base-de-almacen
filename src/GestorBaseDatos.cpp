#include "../include/GestorBaseDatos.h"
#include "../include/Productos.h"
#include "../include/subCategoria.h"
#include "../include/Categorias.h"
#include "../include/ClaseUsuarios.h"
#include <iostream>
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
        cout << " [N] Siguiente | [P] Anterior | [0] Volver al menu: ";
        cin >> comando;
        comando = static_cast<char>(std::toupper(comando));

        if (comando == 'N')
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
        else if (comando == 'P')
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

        char modificar = 'n';
        cout << "¿Desea cambiar el stock de este producto? (s/n): ";
        cin >> modificar;

        if (modificar == 's' || modificar == 'S')
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

        char opcion = 'n';
        cout << "¿Desea renombrar esta subcategoria? (s/n): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S')
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
    
        system("cls");
        cout << "========================================" << endl;
        cout << "       GESTION DE CATEGORIAS            " << endl;
        cout << "========================================" << endl;
        cout << "ADMINISTRADOR: " << usuarioLogueado.getNombreUsuario() << " " << usuarioLogueado.getApellidoUsuario() << endl;
    
        cout << "1 - Modificar una categoria existente" << endl;
        cout << "2 - Crear una nueva categoria" << endl;
        cout << "0 - Volver al menu principal" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
    
        int opcion = 0;
        cin >> opcion;
    
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida." << endl;
            system("pause");
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
                system ("cls");
                cout << "\n=========== CATEGORIAS ACTUALES ===========" << endl;
                cout << "  [ID]" <<endl;
                for (const auto &cat : categorias)
                {
                    cout << "  [" << cat.id << "] " << cat.nombre << endl;
                }
                cout << "===========================================" << endl;
    
                int idCategoria = 0;
                cout << "Ingrese el ID de la categoria a modificar: ";
                cin >> idCategoria;
    
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "ID invalido." << endl;
                    system("pause");
                    return;
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
                    return;
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
    /// Repone stock: elige categoria, subcategoria y producto, y guarda la compra con el ORM.


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

    cout << "Categorias disponibles:" << endl;
    for (auto &cat : categorias)
    {
        cout << "  " << cat.id << " - " << cat.nombre << endl;
    }

    int idCategoria = 0;
    cout << "Ingrese el ID de la categoria: ";
    cin >> idCategoria;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida." << endl;
        system("pause");
        return;
    }

    CategoriaORM categoriaElegida;
    bool categoriaEncontrada = false;
    for (auto &cat : categorias)
    {
        if (cat.id == idCategoria)
        {
            categoriaElegida = cat;
            categoriaEncontrada = true;
            break;
        }
    }
    if (!categoriaEncontrada)
    {
        cout << "No existe una categoria con ID " << idCategoria << endl;
        system("pause");
        return;
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

    cout << endl << "Subcategorias disponibles:" << endl;
    for (auto &sub : subcategorias)
    {
        cout << "  " << sub.id << " - " << sub.nombre << endl;
    }

    int idSubcategoria = 0;
    cout << "Ingrese el ID de la subcategoria: ";
    cin >> idSubcategoria;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida." << endl;
        system("pause");
        return;
    }

    SubcategoriaORM subcategoriaElegida;
    bool subcategoriaEncontrada = false;
    for (auto &sub : subcategorias)
    {
        if (sub.id == idSubcategoria)
        {
            subcategoriaElegida = sub;
            subcategoriaEncontrada = true;
            break;
        }
    }
    if (!subcategoriaEncontrada)
    {
        cout << "La subcategoria no pertenece a la categoria elegida." << endl;
        system("pause");
        return;
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
    system ("cls");
    cout << endl << "Productos de la Categoria '" << categoriaElegida.nombre
         << "' / Subcategoria '" << subcategoriaElegida.nombre << "':" << endl;
    for (auto &prod : productos)
    {
        cout << "  ID " << prod.getIdProducto()
             << " | " << prod.getNombreProducto()
             << " | Precio: $" << prod.getPrecio()
             << " | Stock: " << prod.getStockActual() << endl;
    }

    /// --- 4) Elegir el producto a comprar ---
    int idProducto = 0;
    cout << endl << "Ingrese el ID del producto que desea comprar: ";
    cin >> idProducto;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida." << endl;
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
        cout << "El ID ingresado no pertenece a esa subcategoria." << endl;
        system("pause");
        return;
    }

    /// --- 5) Cantidad a comprar ---
    int cantidad = 0;
    cout << "Cantidad a comprar: ";
    cin >> cantidad;
    if (cin.fail() || cantidad <= 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Cantidad invalida (debe ser mayor a cero)." << endl;
        system("pause");
        return;
    }

    /// --- 6) Opcion de actualizar el precio de venta ---
    char actualizarPrecio = 'n';
    cout << "Precio de venta actual: $" << producto.getPrecio()
         << " - Desea actualizarlo? (s/n): ";
    cin >> actualizarPrecio;

    if (actualizarPrecio == 's' || actualizarPrecio == 'S')
    {
        float nuevoPrecio = 0.0;
        cout << "Ingrese el nuevo precio de venta: ";
        cin >> nuevoPrecio;
        if (cin.fail() || nuevoPrecio < 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Precio invalido." << endl;
            system("pause");
            return;
        }
        producto.setPrecio(nuevoPrecio);
    }

    /// --- 7) Modificar las propiedades del producto y guardar con el ORM ---
    int stockAnterior = producto.getStockActual();
    producto.setStockActual(stockAnterior + cantidad);

    try
    {
        storage.update(producto);
        cout << endl << "[Compra guardada en la base de datos]" << endl;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al guardar la compra: " << e.what() << endl;
        system("pause");
        return;
    }

    /// --- 8) Confirmacion leyendo de nuevo la base ---
    auto productoVerificado = storage.get<Productos>(producto.getIdProducto());

    cout << endl << "=================== COMPRA REGISTRADA ===================" << endl;
    cout << "Producto : " << productoVerificado.getNombreProducto() << endl;
    cout << "Stock    : " << stockAnterior << " -> " << productoVerificado.getStockActual()
         << "  (+" << cantidad << ")" << endl;
    cout << "Precio   : $" << productoVerificado.getPrecio() << endl;
    cout << "=========================================================" << endl;
    system("pause");
}

void GestorBaseDatos::registrarVenta()
{
    /// Carga los productos de una venta (por EAN) y descuenta el stock con el ORM.
    /// (El registro de la venta en las tablas se hara desde la clase Ventas.)
    auto storage = crearStorageAlmacen();

    cout << endl << "================= NUEVA VENTA =================" << endl;

    /// --- 1) Carga de productos (por EAN, como un escaner) ---
    struct LineaVenta
    {
        int idProducto;
        string ean;
        string nombre;
        float precio;
        int cantidad;
        float subtotal;
    };

    vector<LineaVenta> lineas;
    float total = 0.0;

    while (true)
    {
        string ean;
        cout << endl << "Ingrese el EAN del producto (0 para terminar la carga): ";
        cin >> ean;

        if (cin.eof())
        {
            cout << endl << "Se termino la entrada de datos. Venta cancelada." << endl;
            system("pause");
            return;
        }

        if (ean == "0")
        {
            break;
        }

        /// Buscar el producto por EAN con el ORM
        auto encontrados = storage.get_all<Productos>(where(c(&Productos::getEan) == ean));
        if (encontrados.empty())
        {
            cout << "No existe un producto con el EAN " << ean << endl;
            continue;
        }

        Productos producto = encontrados.front();
        cout << "Producto: " << producto.getNombreProducto() << endl;
        cout << "Precio: $" << producto.getPrecio() << " | Stock: " << producto.getStockActual() << endl;

        int cantidad = 0;
        cout << "Cantidad: ";
        cin >> cantidad;
        if (cin.fail() || cantidad <= 0)
        {
            if (cin.eof())
            {
                cout << endl << "Se termino la entrada de datos. Venta cancelada." << endl;
                system("pause");
                return;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Cantidad invalida." << endl;
            continue;
        }

        /// Si el producto ya esta en la venta, se acumula la cantidad
        int indice = -1;
        int cantidadYaCargada = 0;
        for (int i = 0; i < (int)lineas.size(); i++)
        {
            if (lineas[i].idProducto == producto.getIdProducto())
            {
                indice = i;
                cantidadYaCargada = lineas[i].cantidad;
            }
        }

        if (cantidadYaCargada + cantidad > producto.getStockActual())
        {
            cout << "Stock insuficiente: hay " << producto.getStockActual()
                 << " y la venta lleva " << (cantidadYaCargada + cantidad) << endl;
            continue;
        }

        if (indice >= 0)
        {
            lineas[indice].cantidad += cantidad;
            lineas[indice].subtotal = lineas[indice].precio * lineas[indice].cantidad;
        }
        else
        {
            LineaVenta nueva;
            nueva.idProducto = producto.getIdProducto();
            nueva.ean = producto.getEan();
            nueva.nombre = producto.getNombreProducto();
            nueva.precio = producto.getPrecio();
            nueva.cantidad = cantidad;
            nueva.subtotal = producto.getPrecio() * cantidad;
            lineas.push_back(nueva);
        }

        total += producto.getPrecio() * cantidad;
        cout << "Agregado. Total parcial: $" << total << endl;
    }

    if (lineas.empty())
    {
        cout << "No se cargo ningun producto. Venta cancelada." << endl;
        system("pause");
        return;
    }

    /// --- 2) Resumen de la venta ---
    cout << endl << "================ RESUMEN DE LA VENTA ================" << endl;
    for (int i = 0; i < (int)lineas.size(); i++)
    {
        cout << "  " << lineas[i].cantidad << " x " << lineas[i].nombre
             << " ($" << lineas[i].precio << ") = $" << lineas[i].subtotal << endl;
    }
    cout << "  TOTAL: $" << total << endl;

    /// --- 3) Confirmacion ---
    char confirmar = 'n';
    cout << "Confirmar la venta y descontar del stock? (s/n): ";
    cin >> confirmar;
    if (confirmar != 's' && confirmar != 'S')
    {
        cout << "Venta cancelada." << endl;
        system("pause");
        return;
    }

    /// --- 4) Descontar el stock con el ORM (todo en una transaccion) ---
    try
    {
        storage.transaction([&]() mutable {
            for (int i = 0; i < (int)lineas.size(); i++)
            {
                Productos producto = storage.get<Productos>(lineas[i].idProducto);
                producto.setStockActual(producto.getStockActual() - lineas[i].cantidad);
                storage.update(producto);
            }
            return true;
        });
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al descontar el stock: " << e.what() << endl;
        system("pause");
        return;
    }

    /// --- 5) Mostrar el resultado ---
    cout << endl << "=============== STOCK ACTUALIZADO ===============" << endl;
    for (int i = 0; i < (int)lineas.size(); i++)
    {
        Productos producto = storage.get<Productos>(lineas[i].idProducto);
        cout << lineas[i].nombre << endl;
        cout << "  Se vendieron: " << lineas[i].cantidad
             << " | Stock ahora: " << producto.getStockActual() << endl;
    }
    cout << "TOTAL DE LA VENTA: $" << total << endl;
    cout << "=================================================" << endl;
    system("pause");
}
