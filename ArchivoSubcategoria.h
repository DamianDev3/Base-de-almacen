#pragma once
#include "subCategoria.h" 
class ArchivoSubcategoria
{
public:
 ArchivoSubcategoria(const char* ruta = "Subcategoria.dat");
bool guardadoSubCategoria(subCategoria&); 
int contarRegistro ();
void preCargasubcategoria(subCategoria);
void subCategoriaGuardada();
private:
char _rutaArchiSubcategoria [20];

};
