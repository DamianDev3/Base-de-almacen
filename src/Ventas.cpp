#include "Ventas.h"
#include "../include/Productos.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Formato.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

namespace
{
    /// Redondea un importe a 2 decimales (centavos).
    double redondearCentavos(double importe)
    {
        return std::round(importe * 100.0) / 100.0;
    }
}

Ventas::Ventas()
{
    _idVenta = 0;
    _fecha = "";
    _vendedor = "";
    _totalVenta = 0.0;
    _totalPagado = 0.0;
    _diferenciaDePago = 0.0;
    _estadoVenta = false;
    _anuladaPor = "";
    _fechaHoraAnulacion = "";
    _motivoAnulacion = "";
    _observacion = "";
    _tipoMovimiento = "";
}

Ventas::Ventas(int idVenta, string fecha, double totalVenta, double totalPagado, double diferenciaDePago, bool estadoVenta)
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
    _tipoMovimiento = "";
}

Ventas::~Ventas()
{
}

///// SETTERS
void Ventas::setIdVenta(int idVenta)
{
    _idVenta = idVenta;
}

void Ventas::setFechaVenta(string fecha)
{
    _fecha = fecha;
}

void Ventas::setVendedor(string vendedor)
{
    _vendedor = vendedor;
}

void Ventas::setTotalVenta(double totalVenta)
{
    _totalVenta = totalVenta;
}

void Ventas::setTotalPagado(double totalPagado)
{
    _totalPagado = totalPagado;
}

void Ventas::setDiferenciaPago(double diferenciaPago)
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

void Ventas::setTipoMovimiento(string tipoMovimiento)
{
    _tipoMovimiento = tipoMovimiento;
}

///// GETTERS
int Ventas::getIdVenta()
{
    return _idVenta;
}

string Ventas::getFecha()
{
    return _fecha;
}

string Ventas::getVendedor()
{
    return _vendedor;
}

double Ventas::getTotalVenta()
{
    return _totalVenta;
}

double Ventas::getTotalPagado()
{
    return _totalPagado;
}

double Ventas::getDiferenciaPago()
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

string Ventas::getTipoMovimiento()
{
    return _tipoMovimiento;
}

///// FECHA Y HORA (ctime)

/// Guarda en _fecha la fecha y hora actuales del sistema, en formato
/// SQLite: "aaaa-mm-dd hh:mm:ss" (el mismo de la columna fecha_hora).
void Ventas::ingresarFechaHoraActual()
{
    time_t ahora = time(nullptr);
    tm* fechaLocal = localtime(&ahora);
    if (fechaLocal != nullptr)
    {
        char buffer[20];  // "aaaa-mm-dd hh:mm:ss" + fin de cadena
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fechaLocal);
        _fecha = string(buffer);
    }
    else
    {
        _fecha = "";
    }
}

/// Devuelve la fecha guardada formateada como "dd/mm/aaaa".
/// _fecha se guarda como "aaaa-mm-dd hh:mm:ss".
string Ventas::getFechaFormateada()
{
    if (_fecha.size() < 10)
    {
        return "";
    }
    return _fecha.substr(8, 2) + "/" + _fecha.substr(5, 2) + "/" + _fecha.substr(0, 4);
}

/// Devuelve la hora guardada formateada como "hh:mm:ss".
/// _fecha se guarda como "aaaa-mm-dd hh:mm:ss".
string Ventas::getHoraFormateada()
{
    if (_fecha.size() < 19)
    {
        return "";
    }
    return _fecha.substr(11, 8);
}

/// Devuelve la fecha y hora en formato SQLite: "aaaa-mm-dd hh:mm:ss".
/// Es el formato que espera la columna fecha_hora de la tabla Ventas.
string Ventas::getFechaHoraSQL()
{
    return _fecha;
}

//// VENTA DE UN PRODUCTO: completa los datos de la venta (fecha, total y estado).
///  El vendedor lo asigna GestorBaseDatos con el usuario que inicio sesion.
///  El pago se registra despues con registrarPagoCliente(), solo si la venta
///  no se anula. El ticket se muestra con mostrarTicket y el guardado en la
///  base lo hace GestorBaseDatos en las tablas Ventas, Detalle_Ventas y Pagos_Venta.
void Ventas::realizarVenta(const Productos& producto, int cantidad)
{
    ingresarFechaHoraActual();
    _totalVenta = redondearCentavos(producto.getPrecio() * cantidad);
    _estadoVenta = true;
    _totalPagado = 0.0;
    _diferenciaDePago = 0.0;
    _anuladaPor = "";
    _fechaHoraAnulacion = "";
    _motivoAnulacion = "";
    _observacion = "";
}

//// PAGO DEL CLIENTE: pide el monto abonado y calcula el vuelto o lo que falta.
void Ventas::registrarPagoCliente()
{
    cout << "Total de la venta: $" << dinero(_totalVenta) << endl;
    double pagado = 0.0;
    while (true)
    {
        cout << "Cuanto abono el cliente? $";
        cin >> pagado;
        if (cin.eof())
        {
            // Sin entrada disponible: se toma el pago justo.
            pagado = _totalVenta;
            break;
        }
        if (!cin.fail() && pagado >= 0.0)
        {
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Monto invalido." << endl;
    }
    _totalPagado = redondearCentavos(pagado);
    _diferenciaDePago = redondearCentavos(_totalPagado - _totalVenta);
}

//// ANULAR: marca la venta como anulada. El motivo llega elegido desde la
///  lista del sistema; aca solo se pide la observacion.
///  (La fecha y hora se toman en el momento de anular; el "anulada por" lo
///  informa el sistema con el usuario que tiene la sesion abierta.)
void Ventas::anular(const std::string& usuario, const std::string& motivo)
{
    _estadoVenta = false;
    _anuladaPor = usuario;
    _motivoAnulacion = motivo;
    if (_motivoAnulacion.empty())
    {
        _motivoAnulacion = "OTRO";
    }

    // Fecha y hora del momento de la anulacion.
    time_t ahora = time(nullptr);
    tm* fechaLocal = localtime(&ahora);
    if (fechaLocal != nullptr)
    {
        char buffer[20];  // "aaaa-mm-dd hh:mm:ss" + fin de cadena
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fechaLocal);
        _fechaHoraAnulacion = string(buffer);
    }
    else
    {
        _fechaHoraAnulacion = "";
    }

    cout << "Observacion: ";
    cin >> ws;
    getline(cin, _observacion);
}

//// TICKET: muestra la venta cargada (incluye el N° si ya fue guardada en la base).
void Ventas::mostrarTicket(const Productos& producto, int cantidad)
{
    cout << endl;
    cout << "=================== TICKET DE VENTA ===================" << endl;
    if (_idVenta > 0)
    {
        cout << " Venta N° : " << _idVenta << endl;
    }
    cout << " Fecha    : " << getFechaFormateada() << "  Hora: " << getHoraFormateada() << endl;
    cout << " Vendedor : " << _vendedor << endl;
    cout << " -------------------------------------------------------" << endl;
    cout << " Producto : " << producto.getNombreProducto() << endl;
    cout << " Cantidad : " << cantidad << endl;
    cout << " Precio   : $" << dinero(producto.getPrecio()) << endl;
    cout << " Subtotal : $" << dinero(_totalVenta) << endl;
    cout << " -------------------------------------------------------" << endl;
    cout << " TOTAL    : $" << dinero(_totalVenta) << endl;
    cout << " Pagado   : $" << dinero(_totalPagado) << endl;
    if (_diferenciaDePago >= 0.0)
    {
        cout << " Diferencia de pago: $" << dinero(_diferenciaDePago) << " (vuelto)" << endl;
    }
    else
    {
        cout << " Diferencia de pago: $" << dinero(-_diferenciaDePago) << " (falta)" << endl;
    }
    cout << " Estado   : " << (_estadoVenta ? "CONFIRMADA" : "ANULADA") << endl;
    cout << " Movimiento: " << _tipoMovimiento << endl;
    if (!_estadoVenta)
    {
        cout << " ------- Datos de anulacion -------" << endl;
        cout << " Anulada por  : " << _anuladaPor << endl;
        cout << " Fecha y hora : " << _fechaHoraAnulacion << endl;
        cout << " Motivo       : " << _motivoAnulacion << endl;
        cout << " Observacion  : " << _observacion << endl;
    }
    cout << " -------------------------------------------------------" << endl;
    cout << " Stock restante: " << producto.getStockActual() << " unidades" << endl;
    cout << "=======================================================" << endl;
}

//// TERMINAR CON VENTA, DETALLE VENTA Y PAGOS VENTA.

void Ventas::ventaGenerada()
{
    /// Muestra la ultima venta guardada en la base de datos.
    GestorBaseDatos bd;
    bd.mostrarUltimaVenta();
}