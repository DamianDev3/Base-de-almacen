#include "ArchivoSubcategoria.h"
#include "subCategoria.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

ArchivoSubcategoria::ArchivoSubcategoria(const char* registroSub)
{
    strcpy(_rutaArchiSubcategoria,registroSub); 
}
bool ArchivoSubcategoria::guardadoSubCategoria(subCategoria &objSubCat)
{
    FILE *pguardar;
    pguardar = fopen(_rutaArchiSubcategoria,"ab+");
    if (pguardar == nullptr)
    {
        cout << "ERROR:"<<endl;
        return false; 
     }
     bool rGuardado;
     rGuardado = fwrite(&objSubCat,sizeof(subCategoria),1,pguardar);
     fclose(pguardar);
     return rGuardado; 

}
int ArchivoSubcategoria::contarRegistro()
{
    FILE *pContar = fopen(_rutaArchiSubcategoria, "rb");
    if (pContar == nullptr)
    {
        return 0;
    }

    fseek(pContar, 0, SEEK_END);
    int totalBytes = ftell(pContar);
    fclose(pContar);

    int cantidad = totalBytes / sizeof(subCategoria);
    return cantidad;
}

 void ArchivoSubcategoria::subCategoriaGuardada()
{
    subCategoria Objsub;
    FILE *pLista;
    pLista = fopen(_rutaArchiSubcategoria,"rb");
    if (pLista == nullptr)
    {
        cout <<"ERROR:" <<endl;
        system("pause");
        return;
    }
    while(fread(&Objsub,sizeof(subCategoria),1,pLista)==1)
    {
        if(Objsub.getEstadoSubcategoria() && Objsub.getIdSubcategoria() >0)
        {
            cout << Objsub.getNombreSubcategoria() <<endl;
            cout << Objsub.getIdPadre() <<endl;
        }
    }
    system("pause");
fclose(pLista);

}