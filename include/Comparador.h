#pragma once
#include <string>
class Comparador
{
public:
    Comparador();
    Comparador(std::string, std::string, std::string, double, double, double, double, double, std::string, int, double, double);

    void setCodigoEanSepa(std::string);
    void setProducto(std::string);
    void setMarca(std::string);
    void setMakroBenavidez(double);
    void setYaguarMaschwitz(double);
    void setMaxiconsumoPacheco(double);
    void setVitalElTalar(double);
    void setMejorPrecio(double);
    void setMayoristaMasBarato(std::string);
    void setCantPrecios(int);
    void setDiferenciaMaxMin(double);
    void setAhorroMaximo(double);

    std::string getCodigoEanSepa() const;
    std::string getProducto() const;
    std::string getMarca() const;
    double getMakroBenavidez() const;
    double getYaguarMaschwitz() const;
    double getMaxiconsumoPacheco() const;
    double getVitalElTalar() const;
    double getMejorPrecio() const;
    std::string getMayoristaMasBarato() const;
    int getCantPrecios() const;
    double getDiferenciaMaxMin() const;
    double getAhorroMaximo() const;

private:
    std::string _codigoEanSepa;
    std::string _producto;
    std::string _marca;
    double _makroBenavidez;
    double _yaguarMaschwitz;
    double _maxiconsumoPacheco;
    double _vitalElTalar;
    double _mejorPrecio;
    std::string _mayoristaMasBarato;
    int _cantPrecios;
    double _diferenciaMaxMin;
    double _ahorroMaximo;
};
