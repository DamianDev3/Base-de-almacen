#pragma once
#include <iomanip>
#include <sstream>
#include <string>

inline std::string dinero(double importe)
{
    std::ostringstream texto;
    texto << std::fixed << std::setprecision(2) << importe;
    return texto.str();
}
