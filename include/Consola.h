#pragma once

/// Modulo de consola.
/// Configura la consola de Windows para trabajar en UTF-8, de forma que
/// se puedan mostrar y escribir correctamente la enie y los acentos.
namespace Consola
{
    /// Activa la pagina de codigos UTF-8 (65001) en la consola actual,
    /// tanto para la salida (mostrar) como para la entrada (tipear).
    /// Devuelve true si ambas quedaron configuradas.
    bool activarUTF8();
}
