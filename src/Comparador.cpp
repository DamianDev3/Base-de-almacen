#include "Comparador.h"
#include <string>
using namespace std;

Comparador::Comparador()
{
    _codigoEanSepa = "";
    _producto = "";
    _marca = "";
    _makroBenavidez = 0.0;
    _yaguarMaschwitz = 0.0;
    _maxiconsumoPacheco = 0.0;
    _vitalElTalar = 0.0;
    _mejorPrecio = 0.0;
    _mayoristaMasBarato = "";
    _cantPrecios = 0;
    _diferenciaMaxMin = 0.0;
    _ahorroMaximo = 0.0;
}

Comparador::Comparador(std::string codigoEanSepa, std::string producto, std::string marca, double makroBenavidez, double yaguarMaschwitz, double maxiconsumoPacheco, double vitalElTalar, double mejorPrecio, std::string mayoristaMasBarato, int cantPrecios, double diferenciaMaxMin, double ahorroMaximo)
{
    _codigoEanSepa = codigoEanSepa;
    _producto = producto;
    _marca = marca;
    _makroBenavidez = makroBenavidez;
    _yaguarMaschwitz = yaguarMaschwitz;
    _maxiconsumoPacheco = maxiconsumoPacheco;
    _vitalElTalar = vitalElTalar;
    _mejorPrecio = mejorPrecio;
    _mayoristaMasBarato = mayoristaMasBarato;
    _cantPrecios = cantPrecios;
    _diferenciaMaxMin = diferenciaMaxMin;
    _ahorroMaximo = ahorroMaximo;
}

void Comparador::setCodigoEanSepa(std::string codigoEanSepa)
{
    _codigoEanSepa = codigoEanSepa;
}

void Comparador::setProducto(std::string producto)
{
    _producto = producto;
}

void Comparador::setMarca(std::string marca)
{
    _marca = marca;
}

void Comparador::setMakroBenavidez(double makroBenavidez)
{
    _makroBenavidez = makroBenavidez;
}

void Comparador::setYaguarMaschwitz(double yaguarMaschwitz)
{
    _yaguarMaschwitz = yaguarMaschwitz;
}

void Comparador::setMaxiconsumoPacheco(double maxiconsumoPacheco)
{
    _maxiconsumoPacheco = maxiconsumoPacheco;
}

void Comparador::setVitalElTalar(double vitalElTalar)
{
    _vitalElTalar = vitalElTalar;
}

void Comparador::setMejorPrecio(double mejorPrecio)
{
    _mejorPrecio = mejorPrecio;
}

void Comparador::setMayoristaMasBarato(std::string mayoristaMasBarato)
{
    _mayoristaMasBarato = mayoristaMasBarato;
}

void Comparador::setCantPrecios(int cantPrecios)
{
    _cantPrecios = cantPrecios;
}

void Comparador::setDiferenciaMaxMin(double diferenciaMaxMin)
{
    _diferenciaMaxMin = diferenciaMaxMin;
}

void Comparador::setAhorroMaximo(double ahorroMaximo)
{
    _ahorroMaximo = ahorroMaximo;
}

std::string Comparador::getCodigoEanSepa() const
{
    return _codigoEanSepa;
}

std::string Comparador::getProducto() const
{
    return _producto;
}

std::string Comparador::getMarca() const
{
    return _marca;
}

double Comparador::getMakroBenavidez() const
{
    return _makroBenavidez;
}

double Comparador::getYaguarMaschwitz() const
{
    return _yaguarMaschwitz;
}

double Comparador::getMaxiconsumoPacheco() const
{
    return _maxiconsumoPacheco;
}

double Comparador::getVitalElTalar() const
{
    return _vitalElTalar;
}

double Comparador::getMejorPrecio() const
{
    return _mejorPrecio;
}

std::string Comparador::getMayoristaMasBarato() const
{
    return _mayoristaMasBarato;
}

int Comparador::getCantPrecios() const
{
    return _cantPrecios;
}

double Comparador::getDiferenciaMaxMin() const
{
    return _diferenciaMaxMin;
}

double Comparador::getAhorroMaximo() const
{
    return _ahorroMaximo;
}
