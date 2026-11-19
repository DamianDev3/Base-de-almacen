#include "EanProductos.h"
#include "../include/Productos.h"
#include "../include/GestorBaseDatos.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

EanProductos::EanProductos(int idDeEan, string eanProduct, int idDeProducto, bool esPrincipal, bool esAdicional)
{
    _idEanProduct = idDeEan;
    _eanProductos = eanProduct;
    _idProductoOrigen = idDeProducto;
    _esPrincipal = esPrincipal;
    _esAdicional = esAdicional;
}
EanProductos::EanProductos()
{
    _idEanProduct = 0;
    _eanProductos = "0";
    _idProductoOrigen = 0;
    _esPrincipal = false;
    _esAdicional = false;
}

void EanProductos::setIdEanProduct(int ideanProduct)
{
    _idEanProduct = ideanProduct;
}

void EanProductos::setEanProductos(std::string eanProductos)
{
    _eanProductos = eanProductos;
}

void EanProductos::setIdProductoorigen(int idProducotsean)
{
    _idProductoOrigen = idProducotsean;
}

void EanProductos::setEanEsPrincipal(bool esPrincipal)
{
 _esPrincipal = esPrincipal;
}

void EanProductos::setEanEsAdicional(bool esAdicional)
{
    _esAdicional = esAdicional;
}

int EanProductos::getIdEanProduct() const
{
return _idEanProduct;
}

std::string EanProductos::getEanProductos() const
{
return _eanProductos;
}

int EanProductos::getIdProductoorigen() const
{
return _idProductoOrigen;
}

bool EanProductos::getEanEsPrincipal() const
{
return _esPrincipal;
}

bool EanProductos::getEanEsAdicional() const
{
return _esAdicional;
}

void EanProductos::validacionDeEan(string eanEnvaido)
{
GestorBaseDatos datos;

if(!datos.conectar("almacen.db"))
{
    cout << "No se pudo conectar a la base de datos:" <<endl;
    return; 
}

}



