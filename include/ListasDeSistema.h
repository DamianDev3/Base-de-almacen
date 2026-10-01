#pragma once
#include <string>
class ListasDeSistema
{
public:
    ListasDeSistema();
    ListasDeSistema(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string);
    ////SETTERS
    void setRoldeSistema(std::string);
    void setRevicionPrecio(std::string);
    void setEstadoCompra(std::string);
    void setDirecionstock(std::string);
    void settipoMovimiento(std::string);
    void setmotivoCorreccion(std::string);
    void setMediodePago(std::string);
    void setEstadodeVenta(std::string);
    void setUnidadMedicion(std::string);

    ////GETTERS
    std::string getRolsistema();
    std::string getRevisionPrecio();
    std::string getEstadoCompra();
    std::string getDireccionstock();
    std::string getTipoMovimiento();
    std::string getmotivoCorreccion();
    std::string getMediodePago();
    std::string getEstadoVenta();
    std::string getUnidadMedicon();

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
