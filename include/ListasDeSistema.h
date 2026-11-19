#pragma once
#include <string>
class ListasDeSistema
{
public:
    ListasDeSistema();
    ListasDeSistema(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string);
    void setRoldeSistema(std::string);
    void setRevicionPrecio(std::string);
    void setEstadoCompra(std::string);
    void setDirecionstock(std::string);
    void settipoMovimiento(std::string);
    void setmotivoCorreccion(std::string);
    void setMediodePago(std::string);
    void setEstadodeVenta(std::string);
    void setUnidadMedicion(std::string);

    std::string getRolsistema() const;
    std::string getRevisionPrecio() const;
    std::string getEstadoCompra() const;
    std::string getDireccionstock() const;
    std::string getTipoMovimiento() const;
    std::string getmotivoCorreccion() const;
    std::string getMediodePago() const;
    std::string getEstadoVenta() const;
    std::string getUnidadMedicon() const;

private:
std::string _rolDelsistema;
std::string _RevisionPrecio;
std::string _EstadoCompra;
std::string _direccionStock;
std::string _tipoMovimiento;
std::string _motivoCorreccion;
std::string _medioDePago;
std::string _estadoDeVenta;
std::string _unidadDeMedicion;



};
