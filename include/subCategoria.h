#pragma once
#include "Categorias.h"
class subCategoria
{
    public:
    subCategoria();
    subCategoria(int,int, std::string,bool);
    void setIdSubcategoria(int);
    void setnombreSubcategoria(std::string);
    void setEstadoSubcategoria(bool);
    void setIDpadre(int);

    int getIdSubcategoria();
    std::string getNombreSubcategoria();
    bool getEstadoSubcategoria();
    int getIdPadre(); 
    void mostrarCatalogoInicial();

    private:
    int _idSubcategoria;
    int _idPadre;
    std::string _nombresubCategoria;
    bool _estadoSubcategoria;

};
