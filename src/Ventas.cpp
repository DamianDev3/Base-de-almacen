#include "Ventas.h"
#include "../include/Productos.h"
#include "../include/GestorBaseDatos.h"
#include <ctime>
#include <string>
using namespace std;

Ventas::Ventas()
{
    _idVenta = 0;
    _fecha = 0;
    _vendedor = "";
    _totalVenta = 0.0;
    _totalPagado = 0.0;
    _diferenciaDePago = 0.0;
    _estadoVenta = false;
    _anuladaPor = "";
    _fechaHoraAnulacion = "";
    _motivoAnulacion = "";
    _observacion = "";
}

Ventas::Ventas(int idVenta, int fecha, float totalVenta, float totalPagado, float diferenciaDePago, bool estadoVenta)
{
    _idVenta = idVenta;
    _fecha = fecha;
    _vendedor = "sin_vendedor";
    _totalVenta = totalVenta;
    _totalPagado = totalPagado;
    _diferenciaDePago = diferenciaDePago;
    _estadoVenta = estadoVenta;
    _anuladaPor = "";
    _fechaHoraAnulacion = "";
    _motivoAnulacion = "";
    _observacion = "";
}

Ventas::~Ventas()
{
}

///// SETTERS
void Ventas::setIdVenta(int idVenta)
{
    _idVenta = idVenta;
}

void Ventas::setFechaVenta(int fecha)
{
    _fecha = fecha;
}

void Ventas::setVendedor(string vendedor)
{
    _vendedor = vendedor;
}

void Ventas::setTotalVenta(float totalVenta)
{
    _totalVenta = totalVenta;
}

void Ventas::setTotalPagado(float totalPagado)
{
    _totalPagado = totalPagado;
}

void Ventas::setDiferenciaPago(float diferenciaPago)
{
    _diferenciaDePago = diferenciaPago;
}

void Ventas::setEstadoVenta(bool estadoVenta)
{
    _estadoVenta = estadoVenta;
}

void Ventas::setAnuladaPor(string anuladaPor)
{
    _anuladaPor = anuladaPor;
}

void Ventas::setFechaHoraAnulacion(string fechaHoraAnulacion)
{
    _fechaHoraAnulacion = fechaHoraAnulacion;
}

void Ventas::setMotivoAnulacion(string motivoAnulacion)
{
    _motivoAnulacion = motivoAnulacion;
}

void Ventas::setObservacion(string observacion)
{
    _observacion = observacion;
}

///// GETTERS
int Ventas::getIdVenta()
{
    return _idVenta;
}

int Ventas::getFecha()
{
    return _fecha;
}

string Ventas::getVendedor()
{
    return _vendedor;
}

float Ventas::getTotalVenta()
{
    return _totalVenta;
}

float Ventas::getTotalPagado()
{
    return _totalPagado;
}

float Ventas::getDiferenciaPago()
{
    return _diferenciaDePago;
}

bool Ventas::getEstadoVenta()
{
    return _estadoVenta;
}

string Ventas::getAnuladaPor()
{
    return _anuladaPor;
}

string Ventas::getFechaHoraAnulacion()
{
    return _fechaHoraAnulacion;
}

string Ventas::getMotivoAnulacion()
{
    return _motivoAnulacion;
}

string Ventas::getObservacion()
{
    return _observacion;
}

///// FECHA Y HORA (ctime)

/// Guarda en _fecha la fecha y hora actuales del sistema (formato time_t).
void Ventas::ingresarFechaHoraActual()
{
    _fecha = static_cast<int>(time(nullptr));
}

/// Devuelve la fecha guardada formateada como "dd/mm/aaaa".
string Ventas::getFechaFormateada()
{
    time_t t = static_cast<time_t>(_fecha);
    tm* fechaLocal = localtime(&t);
    if (fechaLocal == nullptr)
    {
        return "";
    }
    char buffer[11];  // "dd/mm/aaaa" + fin de cadena
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", fechaLocal);
    return string(buffer);
}

/// Devuelve la hora guardada formateada como "hh:mm:ss".
string Ventas::getHoraFormateada()
{
    time_t t = static_cast<time_t>(_fecha);
    tm* horaLocal = localtime(&t);
    if (horaLocal == nullptr)
    {
        return "";
    }
    char buffer[9];  // "hh:mm:ss" + fin de cadena
    strftime(buffer, sizeof(buffer), "%H:%M:%S", horaLocal);
    return string(buffer);
}

/// Devuelve la fecha y hora en formato SQLite: "aaaa-mm-dd hh:mm:ss".
/// Es el formato que espera la columna fecha_hora de la tabla Ventas.
string Ventas::getFechaHoraSQL()
{
    time_t t = static_cast<time_t>(_fecha);
    tm* fechaLocal = localtime(&t);
    if (fechaLocal == nullptr)
    {
        return "";
    }
    char buffer[20];  // "aaaa-mm-dd hh:mm:ss" + fin de cadena
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fechaLocal);
    return string(buffer);
}

//// TERMINAR CON VENTA, DETALLE VENTA Y PAGOS VENTA.

void Ventas::ventaGenerada()
{
    GestorBaseDatos compra;
    compra.comprarProducto();
  cout << "Vendedor: " << _vendedor << endl;
    cout << "Total pagado: " << _totalPagado << endl;
    cout << "Diferencia de pago: " << _diferenciaDePago << endl;
    cout << "Estado de venta: " << (_estadoVenta ? "CONFIRMADA" : "ANULADA") << endl;

    if (!_estadoVenta)
    {
        cout << "--- Datos de Anulacion ---" << endl;
        cout << "Anulada por: " << _anuladaPor << endl;
        cout << "Fecha y hora de anulacion: " << _fechaHoraAnulacion << endl;
        cout << "Motivo de anulacion: " << _motivoAnulacion << endl;
    }

    cout << "Observacion: " << _observacion << endl;
    

    
}