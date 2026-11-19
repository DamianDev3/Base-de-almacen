#pragma once
#include <string>
#include <vector>
#include <utility>

namespace Selector
{
    const int CANCELADO = -1;

    const int TECLA_FIN       = -100;
    const int TECLA_ARRIBA    = -101;
    const int TECLA_ABAJO     = -102;
    const int TECLA_IZQUIERDA = -103;
    const int TECLA_DERECHA   = -104;
    const int TECLA_ENTER     = -105;
    const int TECLA_ESCAPE    = -106;
    const int TECLA_PGUP      = -107;
    const int TECLA_PGDOWN    = -108;

    bool hayConsola();

    int leerTecla();

    int elegirOpcion(const std::string& titulo,
                     const std::vector<std::pair<int, std::string>>& opciones);

    bool confirmar(const std::string& pregunta, bool porDefecto = false);

    int elegirDeLista(const std::string& titulo,
                      const std::vector<std::pair<int, std::string>>& items);
}
