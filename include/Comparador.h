#pragma once
#include <string>
class Comparador
{
public:
    /// Constructor
    Comparador();
    Comparador(std::string, std::string, std::string, double, double, double, double, double, std::string, int, double, double);

    ////SETTERS
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

    ////GETTERS
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
    /// Cada campo coincide con una columna de la tabla Comparador.
    std::string _codigoEanSepa;        // "Código / EAN SEPA"
    std::string _producto;             // "Producto"
    std::string _marca;                // "Marca"
    double _makroBenavidez;            // "Makro Benavídez"
    double _yaguarMaschwitz;           // "Yaguar Maschwitz"
    double _maxiconsumoPacheco;        // "Maxiconsumo Pacheco"
    double _vitalElTalar;              // "Vital El Talar"
    double _mejorPrecio;               // "Mejor precio"
    std::string _mayoristaMasBarato;   // "Mayorista más barato"
    int _cantPrecios;                  // "Cant. precios"
    double _diferenciaMaxMin;          // "Diferencia máx.-mín."
    double _ahorroMaximo;              // "Ahorro máximo % (valor de porcentaje)"
};
