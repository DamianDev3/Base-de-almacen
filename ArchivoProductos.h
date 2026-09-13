
#pragma once

class ArchivoProductos
{
public:
  ArchivoProductos(const char* rutaP = "ArchivoProductos.dat");
  bool GuardadodeProductos(); 

private:
char _rutaArchivoProudctos [20];
};
