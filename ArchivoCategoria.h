#pragma once
#include "Categorias.h"

class ArchivoCategoria {
private:
    char rutaArchivo[30];

public:
    ArchivoCategoria(const char* ruta = "Categorias.dat");

    bool guardadoListacategorias(Categorias &objCat);
    void Categoriasguardadas();
    void precargaDeRegistros(Categorias);
    int contarRegistros();
    ///int generarID();
};