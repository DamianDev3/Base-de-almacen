#include "../include/subCategoria.h"
#include "../include/GestorBaseDatos.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

subCategoria::subCategoria()
{
    _idSubcategoria = 0;
    _nombresubCategoria = "SIN_SUBCATEGORIA"; 
    _estadoSubcategoria = false;
    _idPadre = 0;
}
subCategoria::subCategoria(int idSub,int idPadre, string nombSub,bool estSub)
{
_idSubcategoria = idSub;
_nombresubCategoria = nombSub;
_estadoSubcategoria = estSub;
_idPadre = idPadre; 
}
///SETTERS
void subCategoria::setIdSubcategoria(int idSub)
{
    _idSubcategoria = idSub;
}
void subCategoria::setIDpadre(int idBadre)
{
    _idPadre = idBadre;
}

void subCategoria::setnombreSubcategoria(string nombreSubcategoria)
{
    _nombresubCategoria = nombreSubcategoria;
}
void subCategoria::setEstadoSubcategoria(bool estadoSub)
{
    _estadoSubcategoria = estadoSub;
}
/// GETTERS

int subCategoria::getIdSubcategoria()
{
    return _idSubcategoria;
}
int subCategoria::getIdPadre()
{
    return _idPadre;
}
string subCategoria::getNombreSubcategoria()
{
    return _nombresubCategoria;
}
bool subCategoria::getEstadoSubcategoria()
{
    return _estadoSubcategoria;
}
// Estructura auxiliar solo para inicializar el catálogo base
struct SemillaSubcategoria {
    int idPadre;
    const char* nombre;
};

void subCategoria::mostrarCatalogoInicial()
{
/// Funcion para gestionar las subcategorias
    

}