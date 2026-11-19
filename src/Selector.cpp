#include "../include/Selector.h"
#include "../include/rlutil.h"
#include "../include/ClaseUsuarios.h"
#include "../include/GestorBaseDatos.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace
{
    bool detectarConsola()
    {
        static int resultado = -1;

        if (resultado < 0)
        {
            HANDLE entrada = GetStdHandle(STD_INPUT_HANDLE);
            DWORD modo = 0;
            bool esConsola = (entrada != INVALID_HANDLE_VALUE) &&
                             (entrada != NULL) &&
                             (GetConsoleMode(entrada, &modo) != 0);
            resultado = esConsola ? 1 : 0;
        }

        return resultado == 1;
    }

    void prepararColores()
    {
        static bool listo = false;

        if (!listo)
        {
            rlutil::saveDefaultColor();
            listo = true;
        }
    }

    void limpiarPantalla()
    {
        if (Selector::hayConsola())
        {
            rlutil::cls();
        }
    }

    int traducirTecla(int tecla)
    {
        switch (tecla)
        {
            case rlutil::KEY_UP:     return Selector::TECLA_ARRIBA;
            case rlutil::KEY_DOWN:   return Selector::TECLA_ABAJO;
            case rlutil::KEY_LEFT:   return Selector::TECLA_IZQUIERDA;
            case rlutil::KEY_RIGHT:  return Selector::TECLA_DERECHA;
            case rlutil::KEY_ENTER:  return Selector::TECLA_ENTER;
            case rlutil::KEY_ESCAPE: return Selector::TECLA_ESCAPE;
            case rlutil::KEY_PGUP:   return Selector::TECLA_PGUP;
            case rlutil::KEY_PGDOWN: return Selector::TECLA_PGDOWN;
            default:                 return tecla;
        }
    }

    int digitoDeTecla(int tecla)
    {
        if (tecla >= '0' && tecla <= '9')
        {
            return tecla - '0';
        }
        if (tecla >= rlutil::KEY_NUMPAD1 && tecla <= rlutil::KEY_NUMPAD9)
        {
            return tecla - rlutil::KEY_NUMPAD1 + 1;
        }
        if (tecla == rlutil::KEY_NUMPAD0)
        {
            return 0;
        }
        return -1;
    }

    void dibujarTitulo(const string& titulo, const string& ayuda)
    {
        ClaseUsuarios usuarioActual = ClaseUsuarios::getUsuarioLogeado();
        bool hayUsuario = !usuarioActual.getNombreUsuario().empty() &&
                          usuarioActual.getRolUsuario() != "Usuario_sin_rol";

        bool stockBajo = false;
        GestorBaseDatos bd;
        
        if (bd.consultarStock() == true)
        {
            stockBajo = true;
        }

        limpiarPantalla();

        cout << "========================================================" << endl;
        cout << " " << titulo << endl;
        if (hayUsuario)
        {
            cout << "Usuario Actual: " << usuarioActual.getNombreUsuario() << " " << usuarioActual.getApellidoUsuario() << endl;
            cout << "Rol: " << usuarioActual.getRolUsuario() << endl;
            
        }
        if (stockBajo == true && usuarioActual.getRolUsuario() == "ADMINISTRADOR")
        {
            cout << "Se detecto un producto bajo en stock, desea generar la compra de hoy?" <<endl;
            
        }
        else if (stockBajo == true && usuarioActual.getRolUsuario() == "VENDEDOR")
        {
            cout << "Se genero la compra de hoy por faltante de stock" <<endl;
        
        }
        cout << "========================================================" << endl;
        cout << " " << ayuda << endl << endl;
    }

    bool lineaANumero(const string& linea, int& numero)
    {
        if (linea.empty())
        {
            return false;
        }

        char* fin = 0;
        long valor = strtol(linea.c_str(), &fin, 10);

        if (fin == linea.c_str() || *fin != '\0')
        {
            return false;
        }

        numero = static_cast<int>(valor);
        return true;
    }
}

namespace Selector
{

bool hayConsola()
{
    return detectarConsola();
}

int leerTecla()
{
    if (hayConsola())
    {
        return traducirTecla(rlutil::getkey());
    }

    while (true)
    {
        string linea;

        if (!getline(cin, linea))
        {
            return TECLA_FIN;
        }

        if (linea.empty())
        {
            continue;
        }

        return static_cast<unsigned char>(linea[0]);
    }
}

int elegirOpcion(const string& titulo, const vector<pair<int, string>>& opciones)
{
    if (opciones.empty())
    {
        return CANCELADO;
    }

    if (!hayConsola())
    {
        while (true)
        {
            dibujarTitulo(titulo, "Elija una opcion escribiendo el numero:");

            for (size_t i = 0; i < opciones.size(); i++)
            {
                cout << "  " << opciones[i].first << " - " << opciones[i].second << endl;
            }

            cout << endl << "Opcion: ";

            string linea;

            if (!getline(cin, linea))
            {
                return CANCELADO;
            }

            if (linea.empty())
            {
                continue;
            }

            int valor = 0;
            if (lineaANumero(linea, valor))
            {
                for (size_t i = 0; i < opciones.size(); i++)
                {
                    if (opciones[i].first == valor)
                    {
                        return valor;
                    }
                }
            }

            cout << "Opcion invalida." << endl;
        }
    }

    prepararColores();
    int seleccion = 0;

    while (true)
    {
        dibujarTitulo(titulo, "Usa las flechas arriba/abajo y Enter (o apreta el numero directo)");

        for (size_t i = 0; i < opciones.size(); i++)
        {
            if ((int)i == seleccion)
            {
                rlutil::setColor(rlutil::LIGHTCYAN);
                cout << "  > " << opciones[i].first << "- " << opciones[i].second << endl;
                rlutil::resetColor();
            }
            else
            {
                cout << "    " << opciones[i].first << "- " << opciones[i].second << endl;
            }
        }

        int tecla = leerTecla();

        if (tecla == TECLA_ARRIBA)
        {
            seleccion = (seleccion + (int)opciones.size() - 1) % (int)opciones.size();
        }
        else if (tecla == TECLA_ABAJO)
        {
            seleccion = (seleccion + 1) % (int)opciones.size();
        }
        else if (tecla == TECLA_ENTER)
        {
            return opciones[seleccion].first;
        }
        else if (tecla == TECLA_ESCAPE || tecla == TECLA_FIN)
        {
            return CANCELADO;
        }
        else
        {
            int digito = digitoDeTecla(tecla);

            if (digito >= 0)
            {
                for (size_t i = 0; i < opciones.size(); i++)
                {
                    if (opciones[i].first == digito)
                    {
                        return digito;
                    }
                }
            }
        }
    }
}

bool confirmar(const string& pregunta, bool porDefecto)
{
    if (!hayConsola())
    {
        while (true)
        {
            cout << pregunta << " (s/n): ";

            string linea;

            if (!getline(cin, linea))
            {
                return false;
            }

            if (linea.empty())
            {
                continue;
            }

            if (linea[0] == 's' || linea[0] == 'S')
            {
                return true;
            }
            if (linea[0] == 'n' || linea[0] == 'N')
            {
                return false;
            }

            cout << "Responda s o n." << endl;
        }
    }

    prepararColores();
    int seleccion = porDefecto ? 0 : 1;

    string base = pregunta + "  (s/n)   ";
    int largoDibujado = 0;

    while (true)
    {
        cout << "\r" << string(largoDibujado, ' ') << "\r";

        cout << base;

        string opcionSi = (seleccion == 0) ? "[ Si ]" : "  Si  ";
        string opcionNo = (seleccion == 1) ? "[ No ]" : "  No  ";

        if (seleccion == 0)
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
        }
        cout << opcionSi;
        if (seleccion == 0)
        {
            rlutil::resetColor();
        }

        cout << "   ";

        if (seleccion == 1)
        {
            rlutil::setColor(rlutil::LIGHTCYAN);
        }
        cout << opcionNo;
        if (seleccion == 1)
        {
            rlutil::resetColor();
        }

        cout.flush();

        int largo = (int)(base.size() + opcionSi.size() + 3 + opcionNo.size());
        if (largo > largoDibujado)
        {
            largoDibujado = largo;
        }

        int tecla = leerTecla();

        if (tecla == TECLA_ARRIBA || tecla == TECLA_ABAJO ||
            tecla == TECLA_IZQUIERDA || tecla == TECLA_DERECHA)
        {
            seleccion = 1 - seleccion;
        }
        else if (tecla == TECLA_ENTER)
        {
            rlutil::resetColor();
            cout << endl;
            return seleccion == 0;
        }
        else if (tecla == 's' || tecla == 'S')
        {
            rlutil::resetColor();
            cout << endl;
            return true;
        }
        else if (tecla == 'n' || tecla == 'N')
        {
            rlutil::resetColor();
            cout << endl;
            return false;
        }
        else if (tecla == TECLA_ESCAPE || tecla == TECLA_FIN)
        {
            rlutil::resetColor();
            cout << endl;
            return false;
        }
    }
}

int elegirDeLista(const string& titulo, const vector<pair<int, string>>& items)
{
    if (items.empty())
    {
        return CANCELADO;
    }

    if (!hayConsola())
    {
        while (true)
        {
            dibujarTitulo(titulo, "Escriba el ID y presione Enter (0 para cancelar):");

            for (size_t i = 0; i < items.size(); i++)
            {
                cout << "  ID " << items[i].first << " | " << items[i].second << endl;
            }

            cout << endl << "ID: ";

            string linea;

            if (!getline(cin, linea))
            {
                return CANCELADO;
            }

            if (linea.empty())
            {
                continue;
            }

            int id = 0;
            if (!lineaANumero(linea, id))
            {
                cout << "ID invalido." << endl;
                continue;
            }

            if (id == 0)
            {
                return CANCELADO;
            }

            for (size_t i = 0; i < items.size(); i++)
            {
                if (items[i].first == id)
                {
                    return id;
                }
            }

            cout << "No existe un item con el ID " << id << "." << endl;
        }
    }

    prepararColores();
    const int POR_PAGINA = 12;

    int total = (int)items.size();
    int paginas = (total + POR_PAGINA - 1) / POR_PAGINA;
    int seleccion = 0;
    string idEscrito = "";
    string aviso = "";

    while (true)
    {
        int pagina = seleccion / POR_PAGINA;
        int inicio = pagina * POR_PAGINA;
        int fin = inicio + POR_PAGINA;
        if (fin > total)
        {
            fin = total;
        }

        dibujarTitulo(titulo, "Flechas: mover | Enter: elegir | Escribi el ID | 0: cancelar");

        for (int i = inicio; i < fin; i++)
        {
            if (i == seleccion)
            {
                rlutil::setColor(rlutil::LIGHTCYAN);
                cout << " > ID " << items[i].first << " | " << items[i].second << endl;
                rlutil::resetColor();
            }
            else
            {
                cout << "   ID " << items[i].first << " | " << items[i].second << endl;
            }
        }

        cout << endl;
        cout << " Pagina " << (pagina + 1) << " de " << paginas
             << " | Total: " << total << endl;
        cout << " ID: " << idEscrito << "_" << endl;
        if (!aviso.empty())
        {
            cout << " " << aviso << endl;
        }

        int tecla = leerTecla();

        if (tecla == TECLA_ARRIBA)
        {
            seleccion = (seleccion == 0) ? (total - 1) : (seleccion - 1);
        }
        else if (tecla == TECLA_ABAJO)
        {
            seleccion = (seleccion + 1) % total;
        }
        else if (tecla == TECLA_IZQUIERDA || tecla == TECLA_PGUP)
        {
            int nueva = (pagina - 1) * POR_PAGINA;
            if (nueva < 0)
            {
                nueva = 0;
            }
            seleccion = nueva;
        }
        else if (tecla == TECLA_DERECHA || tecla == TECLA_PGDOWN)
        {
            int nueva = (pagina + 1) * POR_PAGINA;
            if (nueva > total - 1)
            {
                nueva = total - 1;
            }
            seleccion = nueva;
        }
        else if (tecla == TECLA_ENTER)
        {
            if (idEscrito.empty())
            {
                return items[seleccion].first;
            }

            int id = atoi(idEscrito.c_str());
            for (size_t i = 0; i < items.size(); i++)
            {
                if (items[i].first == id)
                {
                    return id;
                }
            }

            aviso = "No existe un item con el ID " + idEscrito + ".";
            idEscrito = "";
        }
        else if (tecla == 8 || tecla == 127)
        {
            if (!idEscrito.empty())
            {
                idEscrito.erase(idEscrito.size() - 1);
            }
        }
        else if (tecla == TECLA_ESCAPE || tecla == TECLA_FIN)
        {
            return CANCELADO;
        }
        else
        {
            int digito = digitoDeTecla(tecla);

            if (digito >= 0)
            {
                if (idEscrito.empty() && digito == 0)
                {
                    return CANCELADO;
                }
                idEscrito += (char)('0' + digito);
                aviso = "";
            }
        }
    }
}

}
