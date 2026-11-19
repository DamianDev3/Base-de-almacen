#include "CorreccionStock.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

CorreccionStock::CorreccionStock()
{
    _idDeCorreccion = 0;
    _fechayHora = "";
    _codigoInterno = 0;
    _eanProductoCorreccion = "SIN_EAN";
    _productoCorregido = "SIN_PRODUCTO";
    _stockActual =  0;
    _motivoCorreccion = "SIN_MOTIVO_ASIGNADO"; 
    _cantidadCorregida = 0;
    _direccion = "";
    _stockResultante = 0;
    _usuarioCorreccion = "SIN_USUARIO_CORREGIDO";
    _idMovimiento = 0;

}

CorreccionStock::CorreccionStock(int idDeCorreccion, std::string fechayHora, int codigoInterno, std::string eanProductoCorreccion, std::string productoCorregido, int stockActual, std::string motivoCorreccion, int cantidadCorregida, std::string direccion, int stockResultante, std::string usuarioCorreccion, int idMovimiento)
{
    _idDeCorreccion = idDeCorreccion;
    _fechayHora = fechayHora;
    _codigoInterno = codigoInterno;
    _eanProductoCorreccion = eanProductoCorreccion;
    _productoCorregido = productoCorregido;
    _stockActual = stockActual;
    _motivoCorreccion = motivoCorreccion;
    _cantidadCorregida = cantidadCorregida;
    _direccion = direccion;
    _stockResultante = stockResultante;
    _usuarioCorreccion = usuarioCorreccion;
    _idMovimiento = idMovimiento;
}

void CorreccionStock::setIdCorreccion(int idCorreccion)
{
    _idDeCorreccion = idCorreccion;
}

void CorreccionStock::setFehcayHora(std::string fechayHora)
{
    _fechayHora = fechayHora;
}

void CorreccionStock::setCodigoInterno(int codigoInterno)
{
    _codigoInterno = codigoInterno;
}

void CorreccionStock::setProductoEan(std::string productoEan)
{
    _eanProductoCorreccion = productoEan;
}

void CorreccionStock::setProductoCorregido(std::string productoCorregido)
{
    _productoCorregido = productoCorregido;
}

void CorreccionStock::setStockActual(int stockActual)
{
    _stockActual = stockActual;
}

void CorreccionStock::setListaDeSistemas(std::string motivoCorreccion)
{
    _motivoCorreccion = motivoCorreccion;
}

void CorreccionStock::setCantidadCorregida(int cantidadCorregida)
{
    _cantidadCorregida = cantidadCorregida;
}

void CorreccionStock::setDireccion(std::string direccion)
{
    _direccion = direccion;
}

void CorreccionStock::setStockResultante(int stockResultante)
{
    _stockResultante = stockResultante;
}

void CorreccionStock::setUsuarioCorreccion(std::string usuarioCorreccion)
{
    _usuarioCorreccion = usuarioCorreccion;
}

void CorreccionStock::setIdMovimiento(int idMovimiento)
{
    _idMovimiento = idMovimiento;
}

int CorreccionStock::getIdCorreccion() const
{
    return _idDeCorreccion;
}

std::string CorreccionStock::getFechayHoracorreccion() const
{
    return _fechayHora;
}

int CorreccionStock::getCodigoInterno() const
{
    return _codigoInterno;
}

std::string CorreccionStock::getProductoEan() const
{
    return _eanProductoCorreccion;
}

std::string CorreccionStock::getProductoCorregido() const
{
    return _productoCorregido;
}

int CorreccionStock::getStockactual() const
{
    return _stockActual;
}

std::string CorreccionStock::getListaSistema() const
{
    return _motivoCorreccion;
}

int CorreccionStock::getCatnidadcorregida() const
{
    return _cantidadCorregida;
}

std::string CorreccionStock::getDireccion() const
{
    return _direccion;
}

int CorreccionStock::getStockResultante() const
{
    return _stockResultante;
}

std::string CorreccionStock::getUsuarioCorreccion() const
{
    return _usuarioCorreccion;
}

int CorreccionStock::getIdMovimiento() const
{
    return _idMovimiento;
}

void CorreccionStock::ingresarFechaHoraActual()
{
    time_t ahora = time(nullptr);
    tm* fechaLocal = localtime(&ahora);
    if (fechaLocal != nullptr)
    {
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fechaLocal);
        _fechayHora = string(buffer);
    }
    else
    {
        _fechayHora = "";
    }
}

string CorreccionStock::getFechaFormateada() const
{
    if (_fechayHora.size() < 10)
    {
        return "";
    }
    return _fechayHora.substr(8, 2) + "/" + _fechayHora.substr(5, 2) + "/" + _fechayHora.substr(0, 4);
}

string CorreccionStock::getHoraFormateada() const
{
    if (_fechayHora.size() < 19)
    {
        return "";
    }
    return _fechayHora.substr(11, 8);
}

string CorreccionStock::getFechaHoraSQL() const
{
    return _fechayHora;
}
