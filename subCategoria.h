#pragma once
#include "Categorias.h"
class subCategoria
{
    public:
    /* CONSTRUCTORES Y SETTERS*/
    subCategoria();
    subCategoria(int,int, const char*,bool);
    void setIdSubcategoria(int);
    void setnombreSubcategoria(const char*);
    void setEstadoSubcategoria(bool);
    void setIDpadre(int);

    /// GETTERS
    int getIdSubcategoria();
    const char* getNombreSubcategoria();
    bool getEstadoSubcategoria();
    int getCategoriaP();
    int getIdPadre(); 
    void mostrarCatalogoInicial();

    private:
    int _idSubcategoria;
    int _idPadre;
    char _nombresubCategoria [105];
    bool _estadoSubcategoria;

};
