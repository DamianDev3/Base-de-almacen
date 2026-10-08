#pragma once
#include "../include/ListasDeSistema.h"
#include "../include/ClaseUsuarios.h"

class CorreccionStock
{

    /////Ideas para corregir el stock: una es usar un ordenamiento de burbuja para que me muestre los productos de que tengan menor stock para que sean los primeros en reponerse
    ///// Otra es ir producto por producto para ver y analizar cuales hay que reponer y cuales se pueden dejar
    //// se pueden explorar otras ideas
public:
    CorreccionStock();
    CorreccionStock(int, std::string, std::string, std::string, int, ListasDeSistema, int, int, ClaseUsuarios, int);

private:
int _idDeCorreccion;
std::string _fechaHora;
std::string _eanProductoCorreccion;
std::string _productoCorregido;
int _stockActual;
ListasDeSistema _motivoCorreccion;
int _cantidadCorregida;
int _stockResultante;
ClaseUsuarios _usuario;
int _idMovimiento;

};
