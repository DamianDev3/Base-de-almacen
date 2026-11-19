#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "../include/Productos.h"
class EanProductos
{
public:
/////// METODOS SETTERS Y CONSTRUCTORES 
EanProductos(int, std::string,int,bool,bool);
EanProductos();
void setIdEanProduct(int);
void setEanProductos(std::string);
void setIdProductoorigen(int); 
void setEanEsPrincipal(bool);
void setEanEsAdicional(bool);
//////// METODOS GETTERS
int getIdEanProduct() const;
std::string getEanProductos() const;
int getIdProductoorigen() const;
bool getEanEsPrincipal() const;
bool getEanEsAdicional() const;

void validacionDeEan(std::string);
private:
int _idEanProduct;
std::string  _eanProductos;
int _idProductoOrigen;
bool _esPrincipal;
bool _esAdicional;

};

