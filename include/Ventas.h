#pragma once
#include "../include/Productos.h"
#include <ctime>
#include <string>

class Ventas
{
public:
///// CONSTRUCTOR

Ventas();
Ventas(int,int,float,float,float,bool);
~Ventas();
////// SETTERS
void setIdVenta(int);
void setFechaVenta(int);
void setVendedor(std::string);
void setTotalVenta(float);
void setTotalPagado(float);
void setDiferenciaPago(float);
void setEstadoVenta(bool);
void setAnuladaPor(std::string);
void setFechaHoraAnulacion(std::string);
void setMotivoAnulacion(std::string);
void setObservacion(std::string);

/////GETTERS
int getIdVenta();
int getFecha();
std::string getVendedor();
float getTotalVenta();
float getTotalPagado();
float getDiferenciaPago();
bool getEstadoVenta();
std::string getAnuladaPor();
std::string getFechaHoraAnulacion();
std::string getMotivoAnulacion();
std::string getObservacion();

///// FECHA Y HORA (ctime)
void ingresarFechaHoraActual();
std::string getFechaFormateada();
std::string getHoraFormateada();
std::string getFechaHoraSQL();

void realizarVenta(const Productos& producto, int cantidad);
void ventaGenerada();
void mostrarTicket(const Productos& producto, int cantidad);

private:
int _idVenta;
int _fecha;
std::string _vendedor;
float _totalVenta;
float _totalPagado;
float _diferenciaDePago;
bool _estadoVenta;
std::string _anuladaPor;
std::string _fechaHoraAnulacion;
std::string _motivoAnulacion;
std::string _observacion;


};
