#pragma once
#include <string>
class Productos;

class MovimientoStock
{
public:
    MovimientoStock();
    MovimientoStock(int, std::string, int, std::string, std::string, std::string, std::string, int, int, std::string, std::string);

    void setIdMovimiento(int);
    void setFechaHora(std::string);
    void setCodigoInterno(int);
    void setEanLeido(std::string);
    void setProducto(std::string);
    void setTipoMovimiento(std::string);
    void setMotivo(std::string);
    void setCantidad(int);
    void setImpactoStock(int);
    void setUsuario(std::string);
    void setReferencia(std::string);

    int getIdMovimiento() const;
    std::string getFechaHora() const;
    int getCodigoInterno() const;
    std::string getEanLeido() const;
    std::string getProducto() const;
    std::string getTipoMovimiento() const;
    std::string getMotivo() const;
    int getCantidad() const;
    int getImpactoStock() const;
    std::string getUsuario() const;
    std::string getReferencia() const;



private:
    int _idMovimiento;
    std::string _fechaHora;
    int _codigoInterno;
    std::string _eanLeido;
    std::string _producto;
    std::string _tipoMovimiento;
    std::string _motivo;
    int _cantidad;
    int _impactoStock;
    std::string _usuario;
    std::string _referencia;
};
