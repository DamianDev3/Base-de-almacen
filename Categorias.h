#pragma once
#include <iostream>
#include <string>
using namespace std;
class Categorias 
{
    private:
    int _idCategoria;
    char _nombreCategoria[30];
    bool _estadoCategoria;

    public:
    Categorias();
    Categorias(int, const char*, bool);
    int getIdCategoria();
    const char* getNombreCategoria();
    bool getEstadoCategoria();
    void setIdCategoria(int);
    void setNombreCategoria(const char*);
    void setEstadoCategoria(bool);
    void listaCategorias();
};