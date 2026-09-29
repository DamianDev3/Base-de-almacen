#pragma once
#include <string>
#include <vector>
#include <utility>

/// Controles de seleccion para la consola.
/// - En una consola interactiva se puede elegir con las flechas del teclado
///   (arriba/abajo) y Enter, o apretando el numero/ID directamente.
/// - Si la entrada viene de un archivo o tuberia, se elige escribiendo el
///   numero/ID y Enter (como se hacia antes).
namespace Selector
{
    /// Valor que devuelven las funciones cuando se cancela la seleccion.
    const int CANCELADO = -1;

    /// Codigos de teclas especiales que devuelve leerTecla().
    const int TECLA_FIN       = -100;  // fin de entrada (EOF)
    const int TECLA_ARRIBA    = -101;
    const int TECLA_ABAJO     = -102;
    const int TECLA_IZQUIERDA = -103;
    const int TECLA_DERECHA   = -104;
    const int TECLA_ENTER     = -105;
    const int TECLA_ESCAPE    = -106;
    const int TECLA_PGUP      = -107;
    const int TECLA_PGDOWN    = -108;

    /// true si la entrada es una consola interactiva (se pueden usar flechas).
    bool hayConsola();

    /// Lee una tecla. Devuelve un codigo TECLA_* o el caracter apretado.
    int leerTecla();

    /// Menu vertical: flechas arriba/abajo + Enter (o el numero directo).
    /// Devuelve el valor de la opcion elegida, o CANCELADO.
    int elegirOpcion(const std::string& titulo,
                     const std::vector<std::pair<int, std::string>>& opciones);

    /// Pregunta de si/no en una sola linea: flechas para cambiar, Enter para
    /// confirmar, o directamente las teclas 's' / 'n'.
    /// Devuelve false si se cancela (Escape o fin de entrada).
    bool confirmar(const std::string& pregunta, bool porDefecto = false);

    /// Lista seleccionable con paginado (categorias, subcategorias, productos...).
    /// Flechas para mover, Enter para elegir, o escribir el ID y Enter.
    /// Devuelve el ID elegido, o CANCELADO.
    int elegirDeLista(const std::string& titulo,
                      const std::vector<std::pair<int, std::string>>& items);
}
