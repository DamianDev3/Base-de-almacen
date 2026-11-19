#include "MovimientoStock.h"
#include "../include/GestorBaseDatos.h"
#include "Selector.h"
#include <string>
#include <iostream>
using namespace std;

MovimientoStock::MovimientoStock()
{
    _idMovimiento = 0;
    _fechaHora = "";
    _codigoInterno = 0;
    _eanLeido = "";
    _producto = "";
    _tipoMovimiento = "";
    _motivo = "";
    _cantidad = 0;
    _impactoStock = 0;
    _usuario = "";
    _referencia = "";
}

MovimientoStock::MovimientoStock(int idMovimiento, std::string fechaHora, int codigoInterno, std::string eanLeido, std::string producto, std::string tipoMovimiento, std::string motivo, int cantidad, int impactoStock, std::string usuario, std::string referencia)
{
    _idMovimiento = idMovimiento;
    _fechaHora = fechaHora;
    _codigoInterno = codigoInterno;
    _eanLeido = eanLeido;
    _producto = producto;
    _tipoMovimiento = tipoMovimiento;
    _motivo = motivo;
    _cantidad = cantidad;
    _impactoStock = impactoStock;
    _usuario = usuario;
    _referencia = referencia;
}

void MovimientoStock::setIdMovimiento(int idMovimiento)
{
    _idMovimiento = idMovimiento;
}

void MovimientoStock::setFechaHora(std::string fechaHora)
{
    _fechaHora = fechaHora;
}

void MovimientoStock::setCodigoInterno(int codigoInterno)
{
    _codigoInterno = codigoInterno;
}

void MovimientoStock::setEanLeido(std::string eanLeido)
{
    _eanLeido = eanLeido;
}

void MovimientoStock::setProducto(std::string producto)
{
    _producto = producto;
}

void MovimientoStock::setTipoMovimiento(std::string tipoMovimiento)
{
    _tipoMovimiento = tipoMovimiento;
}

void MovimientoStock::setMotivo(std::string motivo)
{
    _motivo = motivo;
}

void MovimientoStock::setCantidad(int cantidad)
{
    _cantidad = cantidad;
}

void MovimientoStock::setImpactoStock(int impactoStock)
{
    _impactoStock = impactoStock;
}

void MovimientoStock::setUsuario(std::string usuario)
{
    _usuario = usuario;
}

void MovimientoStock::setReferencia(std::string referencia)
{
    _referencia = referencia;
}

int MovimientoStock::getIdMovimiento() const
{
    return _idMovimiento;
}

std::string MovimientoStock::getFechaHora() const
{
    return _fechaHora;
}

int MovimientoStock::getCodigoInterno() const
{
    return _codigoInterno;
}

std::string MovimientoStock::getEanLeido() const
{
    return _eanLeido;
}

std::string MovimientoStock::getProducto() const
{
    return _producto;
}

std::string MovimientoStock::getTipoMovimiento() const
{
    return _tipoMovimiento;
}

std::string MovimientoStock::getMotivo() const
{
    return _motivo;
}

int MovimientoStock::getCantidad() const
{
    return _cantidad;
}

int MovimientoStock::getImpactoStock() const
{
    return _impactoStock;
}

std::string MovimientoStock::getUsuario() const
{
    return _usuario;
}

std::string MovimientoStock::getReferencia() const
{
    return _referencia;
}


