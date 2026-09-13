#include <iostream>
#include "ArchivoCategoria.h"
#include "Categorias.h"
#include <cstring>
#include <string>
using namespace std;

ArchivoCategoria::ArchivoCategoria(const char* ruta) {
    strcpy(rutaArchivo, ruta);
}

bool ArchivoCategoria::guardadoListacategorias(Categorias &objCat)
{
    bool escribio = false;
    FILE *guardado;
    guardado = fopen(rutaArchivo,"ab");
    if (guardado == nullptr)
    {
        cout << "NO SE PUDO GUARDAR" <<endl;
        system("pause");
        return false;
    }
    escribio = fwrite (&objCat,sizeof(Categorias),1,guardado);
    fclose(guardado);
    return escribio;
}
int ArchivoCategoria::contarRegistros()
{
    FILE *pContar;
    pContar  = fopen(rutaArchivo, "rb");
    if (pContar == nullptr) 
    {
        return 0;
    }
int cantidad;
fseek(pContar,0,SEEK_END);
cantidad = ftell(pContar) / sizeof(Categorias);
fclose(pContar);
return cantidad;
}


void ArchivoCategoria::precargaDeRegistros(Categorias objCargado)
{
objCargado.listaCategorias();
guardadoListacategorias(objCargado); 
}

void ArchivoCategoria::Categoriasguardadas()
{
    Categorias objC;
    FILE *pLeer;
    pLeer = fopen(rutaArchivo,"rb");
    if (pLeer == nullptr)
    {
        cout << "ERROR:" <<endl;
        system("pause");
        return;
    }
    while (fread(&objC,sizeof(Categorias), 1,pLeer)==1)
    {
        if (objC.getEstadoCategoria() && objC.getIdCategoria() > 0)
        {
           cout << objC.getNombreCategoria()<<endl;
            

        }
    }
    system("pause");
    fclose(pLeer);
}