#include "../include/GestorBaseDatos.h"
#include "../include/Productos.h"
#include "../include/EanProductos.h"
#include "../include/subCategoria.h"
#include "../include/Categorias.h"
#include "../include/ClaseUsuarios.h"
#include "../include/Ventas.h"
#include "../include/DetalleVenta.h"
#include "../include/PagosVenta.h"
#include "../include/CorreccionStock.h"
#include "../include/MovimientoStock.h"
#include "../include/Comparador.h"
#include "../include/ListasDeSistema.h"
#include "../include/Selector.h"
#include "../include/Formato.h"
#include "../include/EanProductos.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include "../lib/sqlite_orm/sqlite_orm.h"

using namespace std;
using namespace sqlite_orm;
namespace
{
    
    vector<string> separarLista(const string& valores)
    {
        vector<string> resultado;
        string actual = "";

        for (size_t i = 0; i <= valores.size(); i++)
        {
            if (i == valores.size() || valores[i] == ',')
            {
                size_t inicio = actual.find_first_not_of(" \t");
                if (inicio != string::npos)
                {
                    size_t fin = actual.find_last_not_of(" \t");
                    resultado.push_back(actual.substr(inicio, fin - inicio + 1));
                }
                actual = "";
            }
            else
            {
                actual += valores[i];
            }
        }

        return resultado;
    }

    MovimientoStock armarMovimiento(const string& fechaHora,
                                    const Productos& producto,
                                    const string& ean,
                                    const string& tipoMovimiento,
                                    const string& motivo,
                                    int cantidad,
                                    int impactoStock,
                                    const string& usuario,
                                    const string& referencia)
    {
        MovimientoStock movimiento;
        movimiento.setIdMovimiento(0);
        movimiento.setFechaHora(fechaHora);
        movimiento.setCodigoInterno(producto.getIdProducto());
        movimiento.setEanLeido(ean);
        movimiento.setProducto(producto.getNombreProducto());
        movimiento.setTipoMovimiento(tipoMovimiento);
        movimiento.setMotivo(motivo);
        movimiento.setCantidad(cantidad);
        movimiento.setImpactoStock(impactoStock);
        movimiento.setUsuario(usuario);
        movimiento.setReferencia(referencia);
        return movimiento;
    }

    string fechaHoraActual()
    {
        time_t ahora = std::time(nullptr);
        std::tm* fechaLocal = std::localtime(&ahora);
        if (fechaLocal == nullptr)
        {
            return "";
        }
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fechaLocal);
        return string(buffer);
    }

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
        double totalVenta = 0;
        double totalPagado = 0;
        double diferenciaPago = 0;
        string estadoVenta;
        string tipoMovimiento;
        string anuladaPor;
        string fechaHoraAnulacion;
        string motivoAnulacion;
        string observacion;
    };

    auto crearStorageAlmacen()
    {
        return make_storage("db/Almacen.db",
            make_table("Productos",
                make_column("id_producto", &Productos::getIdProducto, &Productos::setIdProducto, primary_key()),
                make_column("nombreProductos", &Productos::getNombreProducto, &Productos::setNombreProducto),
                make_column("MarcaProductos", &Productos::getMarcaProducto, &Productos::setMarcaProducto),
                make_column("variantes", &Productos::getVariantes, &Productos::setVariantes),
                make_column("caracteristicas", &Productos::getCaracteristicas, &Productos::setCaracteristicas),
                make_column("envase", &Productos::getEnvase, &Productos::setEnvase),
                make_column("contenido", &Productos::getContenido, &Productos::setContenido),
                make_column("unidad", &Productos::getUnidad, &Productos::setUnidad),
                make_column("unidades_pack", &Productos::getUnidades, &Productos::setUnidades),
                make_column("precio_venta", &Productos::getPrecio, &Productos::setPrecio),
                make_column("stock_minimo", &Productos::getStockMinimo, &Productos::setStockMinimo),
                make_column("stock_objetivo", &Productos::getStockObjetivo, &Productos::setStockObjetivo),
                make_column("stock_actual", &Productos::getStockActual, &Productos::setStockActual),
                make_column("id_subcategoria", &Productos::getIdSubcategoria, &Productos::setIdSubcategoria),
                make_column("observacion", &Productos::getObservacion, &Productos::setObservacion)),
            make_table("EAN_Productos",
                make_column("id_ean", &EanProductos::getIdEanProduct, &EanProductos::setIdEanProduct, primary_key(), autoincrement()),
                make_column("ean", &EanProductos::getEanProductos, &EanProductos::setEanProductos, unique()),
                make_column("id_producto", &EanProductos::getIdProductoorigen, &EanProductos::setIdProductoorigen),
                make_column("es_principal", &EanProductos::getEanEsPrincipal, &EanProductos::setEanEsPrincipal),
                make_column("es_adicional", &EanProductos::getEanEsAdicional, &EanProductos::setEanEsAdicional)),
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
                make_column("tipo_movimiento", &VentaORM::tipoMovimiento),
                make_column("anulada_por", &VentaORM::anuladaPor),
                make_column("fecha_hora_anulacion", &VentaORM::fechaHoraAnulacion),
                make_column("motivo_anulacion", &VentaORM::motivoAnulacion),
                make_column("observacion", &VentaORM::observacion)),
            make_table("Detalle_Ventas",
                make_column("id_detalle", &DetalleVenta::getIdDetalle, &DetalleVenta::setIdDetalle, primary_key(), autoincrement()),
                make_column("id_venta", &DetalleVenta::getIdVenta, &DetalleVenta::setIdVenta),
                make_column("codigo_interno", &DetalleVenta::getCodigoInterno, &DetalleVenta::setCodigoInterno),
                make_column("ean_detectado", &DetalleVenta::getEanD, &DetalleVenta::setEanD),
                make_column("producto", &DetalleVenta::getProductoSnapshot, &DetalleVenta::setProductoSnapshot),
                make_column("precio", &DetalleVenta::getPrecio, &DetalleVenta::setPrecio),
                make_column("cantidad", &DetalleVenta::getCantidadP, &DetalleVenta::setCantidadP),
                make_column("subtotal", &DetalleVenta::getSubTotal, &DetalleVenta::setSubTotal)),
            make_table("Pagos_Venta",
                make_column("id_pago", &PagosVenta::getIdPago, &PagosVenta::setIdPago, primary_key(), autoincrement()),
                make_column("id_venta", &PagosVenta::getIdVTA, &PagosVenta::setIdVTA),
                make_column("medio_pago", &PagosVenta::getMediodePago, &PagosVenta::setMediodePago),
                make_column("importe", &PagosVenta::getSubtotal, &PagosVenta::setSubtotal)),
            make_table("lista_sistema",
                make_column("rol_del_sistema", &ListasDeSistema::getRolsistema, &ListasDeSistema::setRoldeSistema),
                make_column("revision_precio", &ListasDeSistema::getRevisionPrecio, &ListasDeSistema::setRevicionPrecio),
                make_column("estado_compra", &ListasDeSistema::getEstadoCompra, &ListasDeSistema::setEstadoCompra),
                make_column("direccion_stock", &ListasDeSistema::getDireccionstock, &ListasDeSistema::setDirecionstock),
                make_column("tipo_movimiento", &ListasDeSistema::getTipoMovimiento, &ListasDeSistema::settipoMovimiento),
                make_column("motivo_correccion", &ListasDeSistema::getmotivoCorreccion, &ListasDeSistema::setmotivoCorreccion),
                make_column("medio_de_pago", &ListasDeSistema::getMediodePago, &ListasDeSistema::setMediodePago),
                make_column("estado_de_venta", &ListasDeSistema::getEstadoVenta, &ListasDeSistema::setEstadodeVenta),
                make_column("unidad_de_medicion", &ListasDeSistema::getUnidadMedicon, &ListasDeSistema::setUnidadMedicion)),
            make_table("Correccion_Stock",
                make_column("id_correccion", &CorreccionStock::getIdCorreccion, &CorreccionStock::setIdCorreccion, primary_key(), autoincrement()),
                make_column("fecha_hora", &CorreccionStock::getFechayHoracorreccion, &CorreccionStock::setFehcayHora),
                make_column("codigo_interno", &CorreccionStock::getCodigoInterno, &CorreccionStock::setCodigoInterno),
                make_column("ean_leido", &CorreccionStock::getProductoEan, &CorreccionStock::setProductoEan),
                make_column("producto", &CorreccionStock::getProductoCorregido, &CorreccionStock::setProductoCorregido),
                make_column("stock_actual", &CorreccionStock::getStockactual, &CorreccionStock::setStockActual),
                make_column("motivo", &CorreccionStock::getListaSistema, &CorreccionStock::setListaDeSistemas),
                make_column("cantidad", &CorreccionStock::getCatnidadcorregida, &CorreccionStock::setCantidadCorregida),
                make_column("direccion", &CorreccionStock::getDireccion, &CorreccionStock::setDireccion),
                make_column("stock_resultante", &CorreccionStock::getStockResultante, &CorreccionStock::setStockResultante),
                make_column("usuario", &CorreccionStock::getUsuarioCorreccion, &CorreccionStock::setUsuarioCorreccion),
                make_column("id_movimiento", &CorreccionStock::getIdMovimiento, &CorreccionStock::setIdMovimiento)),
            make_table("Movimientos_Stock",
                make_column("id_movimiento", &MovimientoStock::getIdMovimiento, &MovimientoStock::setIdMovimiento, primary_key(), autoincrement()),
                make_column("fecha_hora", &MovimientoStock::getFechaHora, &MovimientoStock::setFechaHora),
                make_column("codigo_interno", &MovimientoStock::getCodigoInterno, &MovimientoStock::setCodigoInterno),
                make_column("ean_leido", &MovimientoStock::getEanLeido, &MovimientoStock::setEanLeido),
                make_column("producto", &MovimientoStock::getProducto, &MovimientoStock::setProducto),
                make_column("tipo_movimiento", &MovimientoStock::getTipoMovimiento, &MovimientoStock::setTipoMovimiento),
                make_column("motivo", &MovimientoStock::getMotivo, &MovimientoStock::setMotivo),
                make_column("cantidad", &MovimientoStock::getCantidad, &MovimientoStock::setCantidad),
                make_column("impacto_stock", &MovimientoStock::getImpactoStock, &MovimientoStock::setImpactoStock),
                make_column("usuario", &MovimientoStock::getUsuario, &MovimientoStock::setUsuario),
                make_column("referencia", &MovimientoStock::getReferencia, &MovimientoStock::setReferencia)),
            make_table("Comparador",
                make_column("Código / EAN SEPA", &Comparador::getCodigoEanSepa, &Comparador::setCodigoEanSepa),
                make_column("Producto", &Comparador::getProducto, &Comparador::setProducto),
                make_column("Marca", &Comparador::getMarca, &Comparador::setMarca),
                make_column("Makro Benavídez", &Comparador::getMakroBenavidez, &Comparador::setMakroBenavidez),
                make_column("Yaguar Maschwitz", &Comparador::getYaguarMaschwitz, &Comparador::setYaguarMaschwitz),
                make_column("Maxiconsumo Pacheco", &Comparador::getMaxiconsumoPacheco, &Comparador::setMaxiconsumoPacheco),
                make_column("Vital El Talar", &Comparador::getVitalElTalar, &Comparador::setVitalElTalar),
                make_column("Mejor precio", &Comparador::getMejorPrecio, &Comparador::setMejorPrecio),
                make_column("Mayorista más barato", &Comparador::getMayoristaMasBarato, &Comparador::setMayoristaMasBarato),
                make_column("Cant. precios", &Comparador::getCantPrecios, &Comparador::setCantPrecios),
                make_column("Diferencia máx.-mín.", &Comparador::getDiferenciaMaxMin, &Comparador::setDiferenciaMaxMin),
                make_column("Ahorro máximo %", &Comparador::getAhorroMaximo, &Comparador::setAhorroMaximo)));
    }

    /// Devuelve el EAN principal de un producto ("" si no tiene).
    string eanPrincipalDeProducto(int idProducto)
    {
        auto storage = crearStorageAlmacen();

        auto eans = storage.get_all<EanProductos>(
            where(c(&EanProductos::getIdProductoorigen) == idProducto));

        for (auto &e : eans)
        {
            if (e.getEanEsPrincipal())
            {
                return e.getEanProductos();
            }
        }

        return "";
    }
}

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

void GestorBaseDatos::AlmacenInventario()
{
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

    const int elementosPorPagina = 10;
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
                 << " | $" << dinero(get<4>(fila))
                 << " | Stock min: " << get<5>(fila)
                 << " | Stock obj: " << get<6>(fila) << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
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

    auto eans = storage.get_all<EanProductos>(
        where(c(&EanProductos::getEanProductos) == string(eanBuscado)));
    if (eans.empty())
    {
        cout << endl << "[!] No se encontro un producto con el EAN " << eanBuscado << endl;
        system("pause");
        return false;
    }

    auto productos = storage.get_all<Productos>(
        where(c(&Productos::getIdProducto) == eans.front().getIdProductoorigen()));

    for (auto &prod : productos)
    {
        cout << endl << "----------------------------------------" << endl;
        cout << "Producto : " << prod.getNombreProducto() << endl;
        cout << "Marca    : " << prod.getMarcaProducto() << endl;
        cout << "Precio   : $" << dinero(prod.getPrecio()) << endl;
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
        cout << " [" << eanPrincipalDeProducto(prod.getIdProducto()) << "] " << prod.getNombreProducto()
             << " | $" << dinero(prod.getPrecio())
             << " | Stock: " << prod.getStockActual() << endl;
    }

    cout << "================================================================================" << endl;
    system("pause");
}

void GestorBaseDatos::buscarCategoria(int idBuscadocat)
{
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
            cout << "     * [" << eanPrincipalDeProducto(prod.getIdProducto()) << "] "
                 << prod.getNombreProducto()
                 << " | $" << dinero(prod.getPrecio())
                 << " | Stock: " << prod.getStockActual() << endl;
        }
    }

    cout << "=======================================================" << endl << endl;
    system("pause");
}

int GestorBaseDatos::elegirCategoria(const std::string& titulo)
{
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

int GestorBaseDatos::elegirSubcategoria(int idCategoria)
{
    auto storage = crearStorageAlmacen();

    auto subcategorias = storage.get_all<SubcategoriaORM>(
        where(c(&SubcategoriaORM::idCategoria) == idCategoria),
        order_by(&SubcategoriaORM::id));

    if (subcategorias.empty())
    {
        cout << "La categoria elegida no tiene subcategorias cargadas." << endl;
        system("pause");
        return Selector::CANCELADO;
    }

    std::vector<std::pair<int, std::string>> lista;
    for (auto &sub : subcategorias)
    {
        lista.push_back(std::make_pair(sub.id, sub.nombre));
    }

    return Selector::elegirDeLista("Alta de producto - Elegir subcategoria", lista);
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
            return ClaseUsuarios();
        }

        cout << "Apellido: ";
        cin >> apellidoUser;
        cout << "Contraseña: ";
        cin >> contraseniaUser;
        cout << "" <<endl;
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
            ClaseUsuarios usuarioLogueado = ususarioPermisos.front();
            cout << "USUARIO INGRESADO CON EXITO!!" <<endl;
            system ("pause");
            return usuarioLogueado;
        }
        
    } while (!encontrado);

    return ClaseUsuarios();
}

void GestorBaseDatos::correccionStockGeneral()
{
    ClaseUsuarios userActual = ClaseUsuarios::getUsuarioLogeado();
    
    if (userActual.getRolUsuario() != "ADMINISTRADOR" && userActual.getRolUsuario() != "LOGISTICA")
    {
        cout << "======= USUARIO INVALIDO =======" << endl;
        cout << "Usted no tiene permisos para corregir el stock:" << endl;
        cout << "Usuario: " << userActual.getNombreUsuario() << endl;
        cout << "Su rol de " << userActual.getRolUsuario() << " no esta autorizado:" << endl;
        cout << "==============================" << endl;
        system("pause");
        return;
    }

    auto storage = crearStorageAlmacen();

    system("cls");
    cout << endl << "=========== CORREGIR STOCK  ===========" << endl;

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

    int idCategoria = Selector::elegirDeLista(
        "Corregir stock  | Elegir categoria",
        listaCategorias);

    if (idCategoria == Selector::CANCELADO)
    {
        cout << "Correccion cancelada." << endl;
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

    int idSubcategoria = Selector::elegirDeLista(
        "Corregir stock | Elegir subcategoria",
        listaSubcategorias);

    if (idSubcategoria == Selector::CANCELADO)
    {
        cout << "Correccion cancelada." << endl;
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

    auto productos = storage.get_all<Productos>(
        where(c(&Productos::getIdSubcategoria) == idSubcategoria),
        multi_order_by(order_by(&Productos::getStockActual), order_by(&Productos::getNombreProducto)));

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
              << " | Precio: $" << dinero(prod.getPrecio())
              << " | Stock: " << prod.getStockActual();
        listaProductos.push_back(std::make_pair(prod.getIdProducto(), texto.str()));
    }

    int idProducto = Selector::elegirDeLista(
        "Corregir stock | " + categoriaElegida.nombre + " / " + subcategoriaElegida.nombre,
        listaProductos);

    if (idProducto == Selector::CANCELADO)
    {
        cout << "Correccion cancelada." << endl;
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

    auto listaSistema = storage.get_all<ListasDeSistema>();

    std::vector<std::string> motivos;
    if (!listaSistema.empty())
    {
        motivos = separarLista(listaSistema.front().getmotivoCorreccion());
    }
    if (motivos.empty())
    {
        motivos = {"ROTURA", "VENCIMIENTO", "DIFERENCIA DE INVENTARIO",
                   "ERROR DE CARGA", "PÉRDIDA / ROBO", "OTRO"};
    }

    std::vector<std::pair<int, std::string>> opcionesMotivo;
    for (size_t i = 0; i < motivos.size(); i++)
    {
        opcionesMotivo.push_back(std::make_pair((int)i + 1, motivos[i]));
    }

    std::string motivo = "OTRO";
    int motivoElegido = Selector::elegirOpcion("Corregir stock - Motivo", opcionesMotivo);
    if (motivoElegido >= 1 && motivoElegido <= (int)motivos.size())
    {
        motivo = motivos[motivoElegido - 1];
    }

    cout << endl << "Producto: " << producto.getNombreProducto() << endl;
    cout << "Stock actual: " << producto.getStockActual() << " unidades." << endl;

    int cantidad = 0;
    while (true)
    {
        cout << "Cantidad a corregir (0 para cancelar): ";
        cin >> cantidad;

        if (cin.fail())
        {
            if (cin.eof())
            {
                cout << endl << "Sin entrada. Correccion cancelada." << endl;
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
            cout << "Correccion cancelada." << endl;
            system("pause");
            return;
        }

        if (cantidad < 0)
        {
            cout << "Cantidad invalida (debe ser mayor a cero)." << endl;
            continue;
        }

        break;
    }

    std::vector<std::string> direcciones;
    if (!listaSistema.empty())
    {
        direcciones = separarLista(listaSistema.front().getDireccionstock());
    }
    if (direcciones.empty())
    {
        direcciones = {"SUMA", "RESTA"};
    }

    std::vector<std::pair<int, std::string>> opcionesDireccion;
    for (size_t i = 0; i < direcciones.size(); i++)
    {
        opcionesDireccion.push_back(std::make_pair((int)i + 1, direcciones[i]));
    }

    std::string direccion = "SUMA";
    int direccionElegida = Selector::elegirOpcion("Corregir stock - Direccion", opcionesDireccion);
    if (direccionElegida >= 1 && direccionElegida <= (int)direcciones.size())
    {
        direccion = direcciones[direccionElegida - 1];
    }

    int stockAnterior = producto.getStockActual();
    int stockResultante = (direccion == "RESTA")
        ? stockAnterior - cantidad
        : stockAnterior + cantidad;

    if (stockResultante < 0)
    {
        cout << "Atencion: el stock quedaria negativo (" << stockResultante << ")." << endl;
        if (!Selector::confirmar("¿Desea continuar igual?"))
        {
            cout << "Correccion cancelada." << endl;
            system("pause");
            return;
        }
    }

    CorreccionStock correccion;
    correccion.setIdCorreccion(0);
    correccion.ingresarFechaHoraActual();
    correccion.setCodigoInterno(producto.getIdProducto());
    string eanProducto = eanPrincipalDeProducto(producto.getIdProducto());
    correccion.setProductoEan(eanProducto);
    correccion.setProductoCorregido(producto.getNombreProducto());
    correccion.setStockActual(stockAnterior);
    correccion.setListaDeSistemas(motivo);
    correccion.setCantidadCorregida(cantidad);
    correccion.setDireccion(direccion);
    correccion.setStockResultante(stockResultante);
    correccion.setUsuarioCorreccion(userActual.getNombreUsuario() + " " + userActual.getApellidoUsuario());
    correccion.setIdMovimiento(0);

    try
    {
        storage.transaction([&]() mutable {

            producto.setStockActual(stockResultante);
            storage.update(producto);

            int idCorreccion = storage.insert(correccion);

            int impacto = (direccion == "RESTA") ? -cantidad : cantidad;
            MovimientoStock movimiento = armarMovimiento(
                correccion.getFechayHoracorreccion(),
                producto,
                eanProducto,
                "CORRECCIÓN",
                motivo,
                cantidad,
                impacto,
                correccion.getUsuarioCorreccion(),
                "CORRECCIÓN N° " + to_string(idCorreccion));
            int idMovimiento = storage.insert(movimiento);

            correccion.setIdCorreccion(idCorreccion);
            correccion.setIdMovimiento(idMovimiento);
            storage.update(correccion);

            return true;
        });

        cout << endl << "=================== CORRECCION GUARDADA ===================" << endl;
        cout << " Fecha    : " << correccion.getFechaFormateada() << "  Hora: " << correccion.getHoraFormateada() << endl;
        cout << " Producto : " << correccion.getProductoCorregido() << endl;
        cout << " Motivo   : " << correccion.getListaSistema() << endl;
        cout << " Cantidad : " << correccion.getCatnidadcorregida() << " (" << correccion.getDireccion() << ")" << endl;
        cout << " Stock    : " << stockAnterior << " -> " << correccion.getStockResultante() << endl;
        cout << " Usuario  : " << correccion.getUsuarioCorreccion() << endl;
        cout << " Movimiento N°: " << correccion.getIdMovimiento() << endl;
        cout << "===========================================================" << endl;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al guardar la correccion: " << e.what() << endl;
    }

    system("pause");
}

void GestorBaseDatos::SubcategoriasMod()
{
        ClaseUsuarios usuarioLogueado = ClaseUsuarios::getUsuarioLogeado();
    if (usuarioLogueado.getRolUsuario() == "ADMINISTRADOR" || usuarioLogueado.getRolUsuario() == "LOGISTICA")
    {
       cout <<"PERMISOS PARA MODIFICAR EL STOCK:"<<endl;
    }
    else
    {
       cout << "======= USUARIO INVALIDO =======" << endl;
        cout << "Usted no tiene permisos para comprar:" <<endl;
        cout << "Usuario:" << usuarioLogueado.getNombreUsuario() << endl; 
        cout << "Su rol de " << "" << usuarioLogueado.getRolUsuario() << "" << " no esta autorizado:" << endl;
        cout << "==============================" <<endl;
        system("pause");
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
    ClaseUsuarios usuarioLogueado = ClaseUsuarios::getUsuarioLogeado();
    if (usuarioLogueado.getRolUsuario() != "ADMINISTRADOR")
    {
        cout << "======= USUARIO INVALIDO =======" << endl;
        cout << "Usted no tiene permisos para comprar:" <<endl;
        cout << "Usuario:" << usuarioLogueado.getNombreUsuario() << endl; 
        cout << "Su rol de " << "" << usuarioLogueado.getRolUsuario() << "" << " no esta autorizado:" << endl;
        cout << "==============================" <<endl;
        system("pause");
        return;
    }

    do
    {
        int opcion = Selector::elegirOpcion(
            "Gestion de categorias:",
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
                    nuevaCategoria.id = 0;
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
    ClaseUsuarios usuarioLogeado = ClaseUsuarios::getUsuarioLogeado();
    if (usuarioLogeado.getRolUsuario() != "ADMINISTRADOR")
    {
          cout << "======= USUARIO INVALIDO =======" << endl;
        cout << "Usted no tiene permisos para comprar:" <<endl;
        cout << "Usuario:" << usuarioLogeado.getNombreUsuario() << endl; 
        cout << "Su rol de " << "" << usuarioLogeado.getRolUsuario() << "" << " no esta autorizado:" << endl;
        cout << "==============================" <<endl;
        system("pause");
        return;
    }

    if (nombreu.empty() || apellidou.empty() || password.empty())
    {
        cout << "ERROR: nombre, apellido y contrasena son obligatorios." << endl;
        return;
    }

    if (roluser != "ADMINISTRADOR" && roluser != "LOGISTICA" && roluser != "VENDEDOR")
    {
        cout << "ERROR: el rol indicado no es valido." << endl;
        return;
    }

    auto storage = crearStorageAlmacen();

    try
    {
        auto existentes = storage.get_all<ClaseUsuarios>(
            where(c(&ClaseUsuarios::getNombreUsuario) == nombreu));
        if (!existentes.empty())
        {
            cout << "Ya existe un usuario con el nombre \"" << nombreu << "\"." << endl;
            return;
        }

        ClaseUsuarios usuario;
        usuario.setNombreUsuario(nombreu);
        usuario.setApellidoUsuario(apellidou);
        usuario.setPassword(password);
        usuario.setRolUsuario(roluser);

        storage.insert(usuario);
        cout << "USUARIO AGREGADO: " << nombreu << " " << apellidou
             << " (" << roluser << ")" << endl;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR AL INGRESAR AL USUARIO: " << e.what() << endl;
    }
}

bool GestorBaseDatos::AltaDeProducto(Productos& producto, const std::string& eanPrincipal)
{
    ClaseUsuarios usuarioLogeado = ClaseUsuarios::getUsuarioLogeado();
    if (usuarioLogeado.getRolUsuario() != "ADMINISTRADOR")
    {
        cout << "Solo un ADMINISTRADOR puede dar de alta productos." << endl;
        return false;
    }

    if (eanPrincipal.empty() || producto.getNombreProducto().empty())
    {
        cout << "ERROR: el EAN y el nombre del producto son obligatorios." << endl;
        return false;
    }

    auto storage = crearStorageAlmacen();

    auto mismoEan = storage.get_all<EanProductos>(
        where(c(&EanProductos::getEanProductos) == eanPrincipal));
    if (!mismoEan.empty())
    {
        cout << "Ya existe un producto con el EAN " << eanPrincipal << "." << endl;
        return false;
    }

    auto productos = storage.get_all<Productos>(order_by(&Productos::getIdProducto));
    int nuevoId = productos.empty() ? 1 : productos.back().getIdProducto() + 1;
    producto.setIdProducto(nuevoId);

    try
    {
        storage.transaction([&]() mutable {
            storage.insert(producto);

            /// El EAN con el que se da de alta queda como principal.
            EanProductos ean;
            ean.setEanProductos(eanPrincipal);
            ean.setIdProductoorigen(producto.getIdProducto());
            ean.setEanEsPrincipal(true);
            ean.setEanEsAdicional(false);
            storage.insert(ean);

            if (producto.getStockActual() > 0)
            {
                MovimientoStock movimiento = armarMovimiento(
                    fechaHoraActual(),
                    producto,
                    eanPrincipal,
                    "ALTA INICIAL",
                    "ALTA DE PRODUCTO",
                    producto.getStockActual(),
                    producto.getStockActual(),
                    usuarioLogeado.getNombreUsuario() + " " + usuarioLogeado.getApellidoUsuario(),
                    "ALTA PRODUCTO N° " + to_string(producto.getIdProducto()));
                storage.insert(movimiento);
            }

            return true;
        });
        return true;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al guardar el producto: " << e.what() << endl;
        return false;
    }
}

void GestorBaseDatos::venderProducto()
{

    
    ClaseUsuarios userComplete = ClaseUsuarios::getUsuarioLogeado();

    if(userComplete.getRolUsuario() != "ADMINISTRADOR" && userComplete.getRolUsuario() != "VENDEDOR")
    {
        cout << "======= USUARIO INVALIDO =======" << endl;
        cout << "Usted no tiene permisos para comprar:" <<endl;
        cout << "Usuario:" << userComplete.getNombreUsuario() << endl; 
        cout << "Su rol de " << "" << userComplete.getRolUsuario() << "" << " no esta autorizado:" << endl;
        cout << "==============================" <<endl;
        system("pause");
        return;
    }

    /////bool cancelarCarga = false;
    auto storage = crearStorageAlmacen();

    system ("cls");
    cout << endl << "=========== VENDER PRODUCTO  ===========" << endl;
    
    

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
    int idCategoria = Selector::elegirDeLista(
        "Comprar producto | Elegir categoria",
        listaCategorias);
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

    int idSubcategoria = Selector::elegirDeLista(
        "Comprar producto | Elegir subcategoria",
        listaSubcategorias);
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
              << " | Precio: $" << dinero(prod.getPrecio())
              << " | Stock: " << prod.getStockActual();
        listaProductos.push_back(std::make_pair(prod.getIdProducto(), texto.str()));
    }

    int idProducto = Selector::elegirDeLista(
        "Comprar producto | " + categoriaElegida.nombre + " / " + subcategoriaElegida.nombre,
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

    auto productoVerificado = storage.get<Productos>(producto.getIdProducto());

    cout << endl << "Stock actualizado: " << stockAnterior
         << " -> " << productoVerificado.getStockActual()
         << "  (-" << cantidad << ")" << endl;

    Ventas venta;
    venta.realizarVenta(productoVerificado, cantidad);

    venta.setVendedor(userComplete.getNombreUsuario() + " " + userComplete.getApellidoUsuario());
    cout << "Vendedor: " << venta.getVendedor() << endl;

    venta.setTipoMovimiento("VENTA");

    venta.registrarPagoCliente();

    auto listaSistema = storage.get_all<ListasDeSistema>();

    string medioDePago = "EFECTIVO";
    if (!listaSistema.empty())
    {
        vector<string> mediosDePago = separarLista(listaSistema.front().getMediodePago());
        if (mediosDePago.size() == 1)
        {
            medioDePago = mediosDePago[0];
        }
        else if (mediosDePago.size() >= 2)
        {
            vector<pair<int, string>> opcionesMedio;
            for (size_t i = 0; i < mediosDePago.size(); i++)
            {
                opcionesMedio.push_back(make_pair((int)i + 1, mediosDePago[i]));
            }

            int medioElegido = Selector::elegirOpcion("Medio de pago", opcionesMedio);
            if (medioElegido >= 1 && medioElegido <= (int)mediosDePago.size())
            {
                medioDePago = mediosDePago[medioElegido - 1];
            }
        }
    }

    string eanProducto = eanPrincipalDeProducto(productoVerificado.getIdProducto());

    DetalleVenta detalleVenta;
    detalleVenta.generarDetalleVTA(productoVerificado, cantidad, eanProducto);

    int idVentaGuardada = 0;
    int idMovimientoVenta = 0;
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
            ventaORM.tipoMovimiento = venta.getTipoMovimiento();
            ventaORM.anuladaPor = venta.getAnuladaPor();
            ventaORM.fechaHoraAnulacion = venta.getFechaHoraAnulacion();
            ventaORM.motivoAnulacion = venta.getMotivoAnulacion();
            ventaORM.observacion = venta.getObservacion();

            idVentaGuardada = storage.insert(ventaORM);

            detalleVenta.setIdVenta(idVentaGuardada);
            storage.insert(detalleVenta);

            venta.setIdVenta(idVentaGuardada);

            PagosVenta pago;
            pago.setMediodePago(medioDePago);
            pago.generarPagodeVenta(venta);
            storage.insert(pago);

            MovimientoStock movimiento = armarMovimiento(
                venta.getFechaHoraSQL(),
                productoVerificado,
                eanProducto,
                "VENTA",
                "",
                cantidad,
                -cantidad,
                venta.getVendedor(),
                "VENTA N° " + to_string(idVentaGuardada));
            idMovimientoVenta = storage.insert(movimiento);

            return true;
        });

        cout << endl << "[Venta guardada en la base de datos - N° " << idVentaGuardada << "]" << endl;
        cout << "[Movimiento de stock N° " << idMovimientoVenta << " - VENTA]" << endl;
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al guardar la venta en la base: " << e.what() << endl;
    }

    venta.mostrarTicket(productoVerificado, cantidad);

    if (userComplete.getRolUsuario() == "ADMINISTRADOR" && idVentaGuardada > 0)
    {
        if (Selector::confirmar("¿Desea anular la venta?"))
        {
            vector<string> motivos;
            if (!listaSistema.empty())
            {
                motivos = separarLista(listaSistema.front().getmotivoCorreccion());
            }
            if (motivos.empty())
            {
                motivos = {"ROTURA", "VENCIMIENTO", "DIFERENCIA DE INVENTARIO",
                           "ERROR DE CARGA", "PÉRDIDA / ROBO", "OTRO"};
            }

            vector<pair<int, string>> opcionesMotivo;
            for (size_t i = 0; i < motivos.size(); i++)
            {
                opcionesMotivo.push_back(make_pair((int)i + 1, motivos[i]));
            }

            string motivo = "OTRO";
            int motivoElegido = Selector::elegirOpcion("Motivo de anulacion", opcionesMotivo);
            if (motivoElegido >= 1 && motivoElegido <= (int)motivos.size())
            {
                motivo = motivos[motivoElegido - 1];
            }

            string tipoAnulacion = "ANULACIÓN VENTA";
            if (!listaSistema.empty())
            {
                vector<string> tipos = separarLista(listaSistema.front().getTipoMovimiento());
                for (auto &tipo : tipos)
                {
                    if (tipo == "ANULACIÓN VENTA")
                    {
                        tipoAnulacion = tipo;
                        break;
                    }
                }
            }

            venta.anular(userComplete.getNombreUsuario() + " " + userComplete.getApellidoUsuario(), motivo);
            venta.setTipoMovimiento(tipoAnulacion);

            int idMovimientoAnulacion = 0;
            try
            {
                storage.transaction([&]() mutable {

                    VentaORM ventaAnuladaORM = storage.get<VentaORM>(idVentaGuardada);
                    ventaAnuladaORM.estadoVenta = "ANULADA";
                    ventaAnuladaORM.tipoMovimiento = tipoAnulacion;
                    ventaAnuladaORM.anuladaPor = venta.getAnuladaPor();
                    ventaAnuladaORM.fechaHoraAnulacion = venta.getFechaHoraAnulacion();
                    ventaAnuladaORM.motivoAnulacion = venta.getMotivoAnulacion();
                    ventaAnuladaORM.observacion = venta.getObservacion();
                    storage.update(ventaAnuladaORM);

                    productoVerificado.setStockActual(productoVerificado.getStockActual() + cantidad);
                    storage.update(productoVerificado);

                    MovimientoStock movimiento = armarMovimiento(
                        venta.getFechaHoraAnulacion(),
                        productoVerificado,
                        eanProducto,
                        tipoAnulacion,
                        motivo,
                        cantidad,
                        cantidad,
                        venta.getAnuladaPor(),
                        "ANULACIÓN VENTA N° " + to_string(idVentaGuardada));
                    idMovimientoAnulacion = storage.insert(movimiento);

                    return true;
                });

                cout << endl << "=======================================================" << endl;
                cout << " Venta N° " << idVentaGuardada << " anulada. Motivo: " << motivo << endl;
                cout << " Anulada por: " << venta.getAnuladaPor() << endl;
                cout << " Stock devuelto - Stock actual: " << productoVerificado.getStockActual() << endl;
                cout << " Movimiento N°: " << idMovimientoAnulacion << endl;
                cout << "=======================================================" << endl;
            }
            catch (const std::exception &e)
            {
                cout << "ERROR al anular la venta: " << e.what() << endl;
            }
        }
    }

    cout << "Recordatorio: los ajustes manuales de stock los realiza aparte" << endl;
    cout << "un usuario con permisos (ADMINISTRADOR / LOGISTICA)." << endl;
    system("pause");
}

void GestorBaseDatos::mostrarUltimaVenta()
{
    auto storage = crearStorageAlmacen();

    auto ventas = storage.get_all<VentaORM>(order_by(&VentaORM::idVenta));
    if (ventas.empty())
    {
        cout << endl << "[!] No hay ventas registradas en la base de datos." << endl;
        system("pause");
        return;
    }

    VentaORM ultima = ventas.back();

    auto detalles = storage.get_all<DetalleVenta>(
        where(c(&DetalleVenta::getIdVenta) == ultima.idVenta));
    auto pagos = storage.get_all<PagosVenta>(
        where(c(&PagosVenta::getIdVTA) == ultima.idVenta));

    cout << endl;
    cout << "================= ULTIMA VENTA REGISTRADA =================" << endl;
    cout << " Venta N° : " << ultima.idVenta << endl;
    cout << " Fecha    : " << ultima.fechaHora << endl;
    cout << " Vendedor : " << ultima.vendedor << endl;
    cout << " ---------------------------------------------------------" << endl;

    for (auto &det : detalles)
    {
        cout << " Producto : " << det.getProductoSnapshot() << endl;
        cout << " Cantidad : " << det.getCantidadP() << endl;
        cout << " Precio   : $" << dinero(det.getPrecio()) << endl;
        cout << " Subtotal : $" << dinero(det.getSubTotal()) << endl;
        cout << " ---------------------------------------------------------" << endl;
    }

    cout << " TOTAL    : $" << dinero(ultima.totalVenta) << endl;
    cout << " Pagado   : $" << dinero(ultima.totalPagado) << endl;
    if (ultima.diferenciaPago >= 0.0)
    {
        cout << " Diferencia de pago: $" << dinero(ultima.diferenciaPago) << " (vuelto)" << endl;
    }
    else
    {
        cout << " Diferencia de pago: $" << dinero(-ultima.diferenciaPago) << " (falta)" << endl;
    }
    if (!pagos.empty())
    {
        cout << " Pago     : " << pagos.front().getMediodePago() << endl;
    }
    cout << " Estado   : " << ultima.estadoVenta << endl;
    cout << " Movimiento: " << ultima.tipoMovimiento << endl;

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

void GestorBaseDatos::mostrarUltimoDetalle()
{
    auto storage = crearStorageAlmacen();

    auto detalles = storage.get_all<DetalleVenta>(order_by(&DetalleVenta::getIdDetalle));
    if (detalles.empty())
    {
        cout << endl << "[!] No hay detalles de venta registrados en la base de datos." << endl;
        system("pause");
        return;
    }

    DetalleVenta ultimo = detalles.back();

    cout << endl;
    cout << "================= ULTIMO DETALLE DE VENTA =================" << endl;
    cout << " Detalle N° : " << ultimo.getIdDetalle() << endl;
    cout << " Venta N°   : " << ultimo.getIdVenta() << endl;
    cout << " ---------------------------------------------------------" << endl;
    cout << " Codigo interno : " << ultimo.getCodigoInterno() << endl;
    cout << " EAN            : " << ultimo.getEanD() << endl;
    cout << " Producto       : " << ultimo.getProductoSnapshot() << endl;
    cout << " Cantidad       : " << ultimo.getCantidadP() << endl;
    cout << " Precio         : $" << dinero(ultimo.getPrecio()) << endl;
    cout << " Subtotal       : $" << dinero(ultimo.getSubTotal()) << endl;
    cout << "============================================================" << endl;

    system("pause");
}

void GestorBaseDatos::mostrarUltimoPago()
{
    auto storage = crearStorageAlmacen();

    auto pagos = storage.get_all<PagosVenta>(order_by(&PagosVenta::getIdPago));
    if (pagos.empty())
    {
        cout << endl << "[!] No hay pagos de venta registrados en la base de datos." << endl;
        system("pause");
        return;
    }

    PagosVenta ultimo = pagos.back();

    cout << endl;
    cout << "=================== ULTIMO PAGO DE VENTA ===================" << endl;
    ultimo.pagoVTAgenerado();
    cout << "============================================================" << endl;

    system("pause");
}

void GestorBaseDatos::MovimientosStock()
{
    
    auto storage = crearStorageAlmacen();

    auto movimientos = storage.get_all<MovimientoStock>(order_by(&MovimientoStock::getIdMovimiento));
    if (movimientos.empty())
    {
        cout << endl << "[!] No hay movimientos de stock registrados." << endl;
        system("pause");
        return;
    }

    const int ultimos = 30;
    int inicio = (int)movimientos.size() - ultimos;
    if (inicio < 0)
    {
        inicio = 0;
    }

    system("cls");
    cout << endl;
    cout << "=================== MOVIMIENTOS DE STOCK ===================" << endl;
    for (int i = inicio; i < (int)movimientos.size(); i++)
    {
        MovimientoStock &mov = movimientos[i];
        cout << " ID mov.   : " << mov.getIdMovimiento() << endl;
        cout << " Fecha     : " << mov.getFechaHora() << endl;
        cout << " Tipo      : " << mov.getTipoMovimiento() << endl;
        cout << " -----------------------------------------------------------" << endl;
        cout << " Producto  : " << mov.getProducto() << endl;
        cout << " EAN       : " << mov.getEanLeido() << endl;
        cout << " Codigo    : " << mov.getCodigoInterno() << endl;
        if (!mov.getMotivo().empty())
        {
            cout << " Motivo    : " << mov.getMotivo() << endl;
        }
        cout << " Cantidad  : " << mov.getCantidad() << endl;
        cout << " Impacto   : " << (mov.getImpactoStock() > 0 ? "+" : "") << mov.getImpactoStock() << endl;
        cout << " Usuario   : " << mov.getUsuario() << endl;
        cout << " Referencia: " << mov.getReferencia() << endl;
        cout << " -----------------------------------------------------------" << endl;
    }
    cout << "============================================================" << endl;

    system("pause");
}

bool GestorBaseDatos::consultarStock()
{
    auto abrirAlmacen = crearStorageAlmacen();

    auto cantidad = abrirAlmacen.count<Productos>(
        where(c(&Productos::getStockActual) < &Productos::getStockMinimo));
        

    return cantidad > 0;
}

bool GestorBaseDatos::generarCompraDehoy()
{
    ClaseUsuarios usuarioLogueado = ClaseUsuarios::getUsuarioLogeado();
    MovimientoStock compraAutomatica;
    if (usuarioLogueado.getRolUsuario() != "ADMINISTRADOR")
    {
        cout << "======= USUARIO INVALIDO =======" << endl;
        cout << "Usted no tiene permisos para comprar:" <<endl;
        cout << "Usuario:" << usuarioLogueado.getNombreUsuario() << endl; 
        cout << "Su rol de " << "" << usuarioLogueado.getRolUsuario() << "" << " no esta autorizado:" << endl;
        cout << "==============================" <<endl;
        system("pause");
        return false;
    } 
    bool compraGenerada = false;
    auto abrirAlmacen = crearStorageAlmacen();
    auto comprarHoy = abrirAlmacen.get_all<Productos>(order_by(&Productos::getIdProducto)); 
    auto comparador = abrirAlmacen.get_all<Comparador>(order_by(&Comparador::getMejorPrecio)); 
    auto listaSistemasOpc = abrirAlmacen.get_all<ListasDeSistema>(order_by(&ListasDeSistema::getEstadoCompra));
    
    /*
    auto subCateto = abrirAlmacen.get_all<SubcategoriaORM>(order_by(&SubcategoriaORM::id));
    auto category = abrirAlmacen.get_all<CategoriaORM>(order_by(&CategoriaORM::id));
     */
    vector<ListasDeSistema>listaDeOpcionesSistema;
    vector<Productos>reposicionDeproductos;
    vector<Comparador>listaPreciosCompradaror;
    for (auto &recorrer : comprarHoy)
    {

                    if (recorrer.getStockActual() < recorrer.getStockMinimo())
                    {
                        reposicionDeproductos.push_back(recorrer); 
                        cout << "Producto /s con stock bajo:" <<endl;
                        recorrer.getNombreProducto();
                        cout << "Stock:" << recorrer.getStockActual() <<endl; 
                    }
                
            }
            
            if(reposicionDeproductos.empty())
            {
                cout << "No hay productos para reponer:" <<endl;
                system("pause");
                return false; 
            }
            
            for (auto &mejorPrecio : comparador)
            {
                listaPreciosCompradaror.push_back(mejorPrecio);
            }
            for (auto cicloLista : listaSistemasOpc)
            {
                listaDeOpcionesSistema.push_back(cicloLista);
                
                
            }
            
           /*  cout << "¿Desea generar una compra de este producto?" <<endl;
            system("pause"); */
    
        ListasDeSistema opcionesCargadas = listaDeOpcionesSistema.front();
        int idcodigoInterno, stockActual, stockMinimo, stockObjetivo;
        int cantidadSugerida, cantidadDecidida;
        double preciominimoComparardor, precioMaxcomparador, diferencia;
        string eanProducto, producto, marcaProducto, mejorProveedor;
        string revisionPrecio, detalleRevision, estadoCompra;
        bool eanDetectados = false;

for (auto &stockBajo : reposicionDeproductos)
{
    eanDetectados = false;
    eanProducto = eanPrincipalDeProducto(stockBajo.getIdProducto());
    preciominimoComparardor = 0.0;
    precioMaxcomparador = 0.0;
    diferencia = 0.0;
    mejorProveedor = "-";
    for (auto &datosComp : comparador)
    {
        if (datosComp.getCodigoEanSepa() == eanProducto){
            eanDetectados = true;
            preciominimoComparardor = datosComp.getMejorPrecio();
            mejorProveedor = datosComp.getMayoristaMasBarato();
            diferencia = datosComp.getDiferenciaMaxMin();
            precioMaxcomparador = preciominimoComparardor + diferencia;
            break;
        }
       
    }
    if(eanDetectados)
    {
    revisionPrecio = opcionesCargadas.getRevisionPrecio();
    detalleRevision = "Proveedor asignado por comparador"; 
}
else
{
    mejorProveedor = "SIN COMPARADOR";
    revisionPrecio = "REVISAR";
    detalleRevision = "EAN no figura en comparador";
}

idcodigoInterno = stockBajo.getIdProducto();
    producto = stockBajo.getNombreProducto();
    marcaProducto = stockBajo.getMarcaProducto();
    stockActual = stockBajo.getStockActual();
    stockMinimo = stockBajo.getStockMinimo();
    stockObjetivo = stockBajo.getStockObjetivo();
    
    cantidadSugerida = stockObjetivo - stockActual;
    cantidadDecidida = cantidadSugerida;
    estadoCompra = opcionesCargadas.getEstadoCompra();  
    stockBajo.setStockActual(stockBajo.getStockActual() + cantidadDecidida);
    
    string referenciaCompra = "COMPRA HOY - " + mejorProveedor;
    if (eanDetectados)
    {
        referenciaCompra += " - $" + dinero(preciominimoComparardor);
    }

    compraAutomatica = armarMovimiento(
        fechaHoraActual(),
        stockBajo,
        eanProducto,
        "INGRESO",
        "COMPRA AUTOMATICA",
        cantidadDecidida,
        cantidadDecidida,
        usuarioLogueado.getNombreUsuario() + " " + usuarioLogueado.getApellidoUsuario(),
        referenciaCompra);

    try
    {
        abrirAlmacen.transaction([&]() mutable {
            abrirAlmacen.update(stockBajo);
            abrirAlmacen.insert(compraAutomatica);
            return true;
        });
    }
    catch (const std::exception &e)
    {
        cout << "ERROR al registrar la compra de hoy: " << e.what() << endl;
        continue;
    }
    cout << "============================"<<endl;
    cout << "Compra de hoy del producto generada: " << producto 
    << " | Cantidad repuesta: " << cantidadDecidida 
    << " | Nuevo Stock (en memoria): " << stockBajo.getStockActual() << endl;
    cout << "============================"<<endl;
    
    cout << "Compra generada" <<endl;
    compraGenerada = true;
    
    /* compraAutomatica.comprarHoyHistorial(stockBajo); */
    
    system("pause"); 
}

return compraGenerada;
}

void GestorBaseDatos::compraHoyHistorial()
{
    auto storage = crearStorageAlmacen();

    auto movimientos = storage.get_all<MovimientoStock>(order_by(&MovimientoStock::getIdMovimiento));

    vector<MovimientoStock> compras;
    for (auto &mov : movimientos)
    {
        if (mov.getTipoMovimiento() == "INGRESO" && mov.getMotivo() == "COMPRA AUTOMATICA")
        {
            compras.push_back(mov);
        }
    }

    if (compras.empty())
    {
        cout << endl << "[!] No hay compras automaticas registradas." << endl;
        system("pause");
        return;
    }

    const int ultimas = 30;
    int inicio = (int)compras.size() - ultimas;
    if (inicio < 0)
    {
        inicio = 0;
    }

    system("cls");
    cout << endl;
    cout << "============= HISTORIAL DE COMPRAS AUTOMATICAS =============" << endl;
    for (int i = inicio; i < (int)compras.size(); i++)
    {
        MovimientoStock &mov = compras[i];
        cout << " ID mov.   : " << mov.getIdMovimiento() << endl;
        cout << " Fecha     : " << mov.getFechaHora() << endl;
        cout << " Producto  : " << mov.getProducto() << endl;
        cout << " EAN       : " << mov.getEanLeido() << endl;
        cout << " Cantidad  : " << mov.getCantidad() << endl;
        cout << " Impacto   : +" << mov.getImpactoStock() << endl;
        cout << " Usuario   : " << mov.getUsuario() << endl;
        cout << " Referencia: " << mov.getReferencia() << endl;
        cout << " -----------------------------------------------------------" << endl;
    }
    cout << " Total de compras registradas: " << compras.size() << endl;
    cout << "============================================================" << endl;

    system("pause");
}

bool GestorBaseDatos::compararEan(std::string eanAcomparar)
{
 

    bool existe = false;
    EanProductos miniEan;
    Productos product;
    auto apertura = crearStorageAlmacen();
    auto traerDatos = apertura.get_all<EanProductos>(order_by(&EanProductos::getIdEanProduct)); 
    for (auto& ciclo : traerDatos)
    {
        if (ciclo.getEanProductos() == eanAcomparar)
        {
            existe = true;
        }
        if(ciclo.getEanProductos() != eanAcomparar || ciclo.getIdProductoorigen() == product.getIdProducto())
        {
            miniEan.setEanEsAdicional(true);
            miniEan.setEanEsPrincipal(false);
        }
        
    }
    if (existe == true)
    {
        miniEan.setEanEsPrincipal(false);
    }
    else {
        miniEan.setEanEsPrincipal(true);
    }

return existe;
}



