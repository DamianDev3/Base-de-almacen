#include "../include/Consola.h"
#include "windows.h"

namespace Consola
{
    bool activarUTF8()
    {
        bool salida  = SetConsoleOutputCP(CP_UTF8) != 0;
        bool entrada = SetConsoleCP(CP_UTF8) != 0;
        return salida && entrada;
    }
}
