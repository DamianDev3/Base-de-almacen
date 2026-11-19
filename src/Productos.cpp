#include "../include/Productos.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Selector.h"
#include "../include/ClaseUsuarios.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
Productos::Productos()
{
    _idProducto = 0;
    _Nombreproducto = "sin_nombre"; 
    _marcaProducto = "sin_marca";
    _variantes = "sin_variantes";
    _caracteristicas = "sin_caracteristicas";
    _envase = "sin_envase";
    _contenidoXunidad = "sin_contenido";
    _unidad = "sin_unidad";
    _unidades = 0;
    _precioVenta = 0.0;
    _stockActual = 0;
    _stockMinimo = 0;
    _stockObjetivo = 0;
    _idCategoria = 0;
    _idSubcategoria = 0;
    _observacion = "sin_observacion";
}

Productos::Productos(int idProducto, string Nombreproducto, string marcaProducto, string variantes, string caracteristicas, string envase, string contenido, string unidad, int unidades, double precioVenta, int stockActual, int stockMinimo, int stockObjetivo, int idCategoria, int idSubcategoria, string observacion)
{
    _idProducto = idProducto;
    _Nombreproducto = Nombreproducto;
    _marcaProducto = marcaProducto;
    _variantes = variantes;
    _caracteristicas = caracteristicas;
    _envase = envase;
    _contenidoXunidad = contenido;
    _unidad = unidad;
    _unidades = unidades;
    _precioVenta = precioVenta;
    _stockActual = stockActual;
    _stockMinimo = stockMinimo;
    _stockObjetivo = stockObjetivo;
    _idCategoria = idCategoria;
    _idSubcategoria = idSubcategoria;
    _observacion = observacion;
}

void Productos::setIdProducto(int idProducto)
{
    _idProducto = idProducto;
}

void Productos::setNombreProducto(string nombreProducto) {
    _Nombreproducto = nombreProducto;
}

void Productos::setMarcaProducto(string marcaProducto) {
    _marcaProducto = marcaProducto;
}

void Productos::setVariantes(string variantes) {
    _variantes = variantes;
}

void Productos::setCaracteristicas(std::string caracteristicas)
{
    _caracteristicas = caracteristicas;
}

void Productos::setEnvase(std::string envase)
{
    _envase = envase;
}

void Productos::setContenido(string contenido) {
    _contenidoXunidad = contenido;
}

void Productos::setUnidad(std::string unidad)
{
    _unidad = unidad;
}

void Productos::setUnidades(int unidades) {
    _unidades = unidades;
}

void Productos::setPrecio(double precio) {
    _precioVenta = precio;
}

void Productos::setStockMinimo(int stockMinimo) {
    _stockMinimo = stockMinimo;
}

void Productos::setStockObjetivo(int stockObjetivo) {
    _stockObjetivo = stockObjetivo;
}

void Productos::setStockActual(int stockActual) {
    _stockActual = stockActual;
}

void Productos::setIdCategoria(int idCategoria) {
    _idCategoria = idCategoria;
}

void Productos::setIdSubcategoria(int idSubcategoria) {
    _idSubcategoria = idSubcategoria;
}

void Productos::setObservacion(std::string observacion)
{
    _observacion = observacion;
}

int Productos::getIdProducto() const
{
    return _idProducto;
}

string Productos::getNombreProducto() const {
    return _Nombreproducto;
}

string Productos::getMarcaProducto() const {
    return _marcaProducto;
}

string Productos::getVariantes() const {
    return _variantes;
}

std::string Productos::getCaracteristicas() const
{
    return _caracteristicas;
}

std::string Productos::getEnvase() const
{
    return _envase;
}

string Productos::getContenido() const {
    return _contenidoXunidad;
}

std::string Productos::getUnidad() const
{
    return _unidad;
}

int Productos::getUnidades() const {
    return _unidades;
}

double Productos::getPrecio() const {
    return _precioVenta;
}

int Productos::getStockMinimo() const {
    return _stockMinimo;
}

int Productos::getStockObjetivo() const {
    return _stockObjetivo;
}

int Productos::getStockActual() const {
    return _stockActual;
}

int Productos::getIdCategoria() const {
    return _idCategoria;
}

int Productos::getIdSubcategoria() const {
    return _idSubcategoria;
}

std::string Productos::getObservacion() const
{
    return _observacion;
}

void Productos::lecturaProducto()
{
    GestorBaseDatos datos;
    if(!datos.conectar("db/Almacen.db")) 
    {
        cout << "No se pudo conectar a la base de datos:" <<endl;
        return;
    }

    int idBuscado = datos.elegirCategoria("Leer producto - Elegir categoria");
    if (idBuscado != Selector::CANCELADO)
    {
        datos.buscarCategoria(idBuscado);
    }
    datos.desconectar(); 
}

namespace
{
    bool leerTexto(const string& mensaje, string& valor, bool obligatorio, const string& porDefecto)
    {
        while (true)
        {
            cout << mensaje;
            if (!getline(cin, valor))
            {
                return false;
            }

            size_t inicio = valor.find_first_not_of(" \t\r");
            if (inicio == string::npos)
            {
                valor = "";
            }
            else
            {
                size_t fin = valor.find_last_not_of(" \t\r");
                valor = valor.substr(inicio, fin - inicio + 1);
            }

            if (!valor.empty())
            {
                return true;
            }
            if (!obligatorio)
            {
                valor = porDefecto;
                return true;
            }
            cout << "Este campo es obligatorio." << endl;
        }
    }

    bool leerEntero(const string& mensaje, int& valor, int minimo)
    {
        while (true)
        {
            cout << mensaje;
            cin >> valor;
            if (cin.eof())
            {
                return false;
            }
            if (!cin.fail() && valor >= minimo)
            {
                cin.ignore(10000, '\n');
                return true;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Valor invalido (debe ser " << minimo << " o mayor)." << endl;
        }
    }

    bool leerDecimal(const string& mensaje, double& valor, double minimo)
    {
        while (true)
        {
            cout << mensaje;
            cin >> valor;
            if (cin.eof())
            {
                return false;
            }
            if (!cin.fail() && valor >= minimo)
            {
                cin.ignore(10000, '\n');
                return true;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Valor invalido (debe ser " << minimo << " o mayor)." << endl;
        }
    }
}

void Productos::altaProducto()
{   
    
    ClaseUsuarios usuarioActual = ClaseUsuarios::getUsuarioLogeado();
    if (usuarioActual.getRolUsuario() != "ADMINISTRADOR")
    {
        cout << "Sin permisos para dar de alta un producto." << endl;
        system("pause");
        return;
    }

    GestorBaseDatos bd;

    cout << "============ ALTA DE PRODUCTO ============" << endl;

    _idCategoria = bd.elegirCategoria("Alta de producto - Elegir categoria");
    if (_idCategoria == Selector::CANCELADO)
    {
        cout << "Alta de producto cancelada." << endl;
        system("pause");
        return;
    }

    _idSubcategoria = bd.elegirSubcategoria(_idCategoria);
    if (_idSubcategoria == Selector::CANCELADO)
    {
        cout << "Alta de producto cancelada." << endl;
        system("pause");
        return;
    }

    auto cancelar = [&]()
    {
        cout << "Sin entrada. Alta de producto cancelada." << endl;
        system("pause");
    };

    string eanPrincipal;
    if (!leerTexto("EAN principal: ", eanPrincipal, true, "")) { cancelar(); return; }
    if (bd.compararEan(eanPrincipal))
    {
        cout << "El EAN ya existe en la base de datos." << endl;
        system("pause");
    }
    
    if (!leerTexto("Producto: ", _Nombreproducto, true, "")) { cancelar(); return; }
    if (!leerTexto("Marca (Enter = NO APLICA): ", _marcaProducto, false, "NO APLICA")) { cancelar(); return; }
    if (!leerTexto("Variante (Enter = NO APLICA): ", _variantes, false, "NO APLICA")) { cancelar(); return; }
    if (!leerTexto("Caracteristicas (Enter = NO APLICA): ", _caracteristicas, false, "NO APLICA")) { cancelar(); return; }
    if (!leerTexto("Envase (Enter = NO APLICA): ", _envase, false, "NO APLICA")) { cancelar(); return; }
    if (!leerTexto("Contenido por unidad (Enter = NO APLICA): ", _contenidoXunidad, false, "NO APLICA")) { cancelar(); return; }
    if (!leerTexto("Unidad (Enter = UNIDAD): ", _unidad, false, "UNIDAD")) { cancelar(); return; }
    if (!leerEntero("Unidades por pack (1): ", _unidades, 1)) { cancelar(); return; }
    if (!leerDecimal("Precio de venta: ", _precioVenta, 0.0)) { cancelar(); return; }
    if (!leerEntero("Stock minimo: ", _stockMinimo, 0)) { cancelar(); return; }
    if (!leerEntero("Stock objetivo: ", _stockObjetivo, 0)) { cancelar(); return; }
    if (!leerEntero("Cantidad inicial: ", _stockActual, 0)) { cancelar(); return; }
    if (!leerTexto("Observacion (Enter = SIN OBSERVACION): ", _observacion, false, "SIN OBSERVACION")) { cancelar(); return; }

    if (!bd.AltaDeProducto(*this, eanPrincipal))
    {
        cout << "No se pudo dar de alta el producto." << endl;
        system("pause");
        return;
    }

    cout << endl << "==========================================" << endl;
    cout << " Producto dado de alta correctamente" << endl;
    cout << " Codigo interno : " << _idProducto << endl;
    cout << " EAN            : " << eanPrincipal << endl;
    cout << " Producto       : " << _Nombreproducto << endl;
    cout << " Categoria ID   : " << _idCategoria << endl;
    cout << " Subcategoria ID: " << _idSubcategoria << endl;
    cout << " Stock inicial  : " << _stockActual << endl;
    cout << "==========================================" << endl;
    system("pause");
}
