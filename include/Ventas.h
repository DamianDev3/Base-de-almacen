#pragma once
#include "../include/Productos.h"
#include <ctime>
#include <string>

class Ventas
{
public:
///// CONSTRUCTOR

Ventas();
Ventas(int,int,double,double,double,bool);
~Ventas();
////SETTERS
void setIdVenta(int);
void setFechaVenta(int);
void setVendedor(std::string);
void setTotalVenta(double);
void setTotalPagado(double);
void setDiferenciaPago(double);
void setEstadoVenta(bool);
void setAnuladaPor(std::string);
void setFechaHoraAnulacion(std::string);
void setMotivoAnulacion(std::string);
void setObservacion(std::string);
void setTipoMovimiento(std::string);

////GETTERS
int getIdVenta();
int getFecha();
std::string getVendedor();
double getTotalVenta();
double getTotalPagado();
double getDiferenciaPago();
bool getEstadoVenta();
std::string getAnuladaPor();
std::string getFechaHoraAnulacion();
std::string getMotivoAnulacion();
std::string getObservacion();
std::string getTipoMovimiento();

///// FECHA Y HORA (ctime)
void ingresarFechaHoraActual();
std::string getFechaFormateada();
std::string getHoraFormateada();
std::string getFechaHoraSQL();

void realizarVenta(const Productos& producto, int cantidad);
void registrarPagoCliente();
void anular(const std::string& usuario, const std::string& motivo);
void ventaGenerada();
void mostrarTicket(const Productos& producto, int cantidad);

private:
int _idVenta;
int _fecha;
std::string _vendedor;
double _totalVenta;
double _totalPagado;
double _diferenciaDePago;
bool _estadoVenta;
std::string _anuladaPor;
std::string _fechaHoraAnulacion;
std::string _motivoAnulacion;
std::string _observacion;
std::string _tipoMovimiento;


};
