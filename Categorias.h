#pragma once
#include <iostream>
#include <string>
using namespace std;
class Categorias 
{
    private:
    int _idCategoria;
    std::string _nombreCategoria;
    bool _estadoCategoria;

    public:
    Categorias();
    Categorias(int, std::string, bool);
    int getIdCategoria();
    std::string getNombreCategoria();
    bool getEstadoCategoria();
    void setIdCategoria(int);
    void setNombreCategoria(std::string);
    void setEstadoCategoria(bool);
    void listaCategorias();
};