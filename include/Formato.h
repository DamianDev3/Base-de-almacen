#pragma once
#include <iomanip>
#include <sstream>
#include <string>

/// Formatea un importe con 2 decimales fijos (centavos).
/// Por ejemplo: 23282.64  →  "23282.64"
inline std::string dinero(double importe)
{
    std::ostringstream texto;
    texto << std::fixed << std::setprecision(2) << importe;
    return texto.str();
}
