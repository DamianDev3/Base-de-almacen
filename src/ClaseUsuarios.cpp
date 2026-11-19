#include "../include/ClaseUsuarios.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Selector.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std; 

ClaseUsuarios ClaseUsuarios::_usuarioLogeado;

 ClaseUsuarios::ClaseUsuarios()
{
    _idUsuario = 0;
    _nombreUsuario = "Usuario_sin_nombre";
    _rolUsuario = "Usuario_sin_rol";
    _apellidoUsuario = "Usuario_sin_apellido";
}
ClaseUsuarios::ClaseUsuarios(int idUsuario,const string& nombreUsuario,const string& rolUsuario, const string& password)
{
    _idUsuario = idUsuario;
    _nombreUsuario = nombreUsuario;
    _apellidoUsuario = "Usuario_sin_apellido";
    _rolUsuario = rolUsuario;
    _password = password;

} 
void ClaseUsuarios::setIdUsuario(int idUser)
{
    _idUsuario = idUser;
}

void ClaseUsuarios::setNombreUsuario(string nombreUser)
{
    _nombreUsuario = nombreUser;
}
void ClaseUsuarios::setApellidoUsuario(string apellidoUser)
{
    _apellidoUsuario = apellidoUser;
}
void ClaseUsuarios::setUsuarioLogeado(const ClaseUsuarios & usuarioLogeado)
{
 _usuarioLogeado = usuarioLogeado;
}
void ClaseUsuarios::setRolUsuario(string rolUser)
{
    _rolUsuario = rolUser;
}

void ClaseUsuarios::setPassword(string passwordUser)
{
    _password = passwordUser;
}
int ClaseUsuarios::getIdUsuario() const
{
    return _idUsuario;

}
string ClaseUsuarios::getNombreUsuario() const
{
    return _nombreUsuario;
}
string ClaseUsuarios::getApellidoUsuario() const
{
    return _apellidoUsuario;
}
string ClaseUsuarios::getRolUsuario() const
{
    return _rolUsuario;
}

string ClaseUsuarios::getPassword() const
{
    return _password;
}
const ClaseUsuarios ClaseUsuarios::getUsuarioLogeado()
{
return _usuarioLogeado;
}

void ClaseUsuarios::cargaDeUsuario()
{
    ClaseUsuarios usuarioActual = ClaseUsuarios::getUsuarioLogeado();
    if (usuarioActual.getRolUsuario() != "ADMINISTRADOR")
    {
        cout << "======= USUARIO INVALIDO =======" << endl;
        cout << "Solo un ADMINISTRADOR puede dar de alta usuarios." << endl;
        cout << "Usuario: " << usuarioActual.getNombreUsuario() << endl;
        cout << "Rol: " << usuarioActual.getRolUsuario() << endl;
        cout << "================================" << endl;
        system("pause");
        return;
    }

    int opcion = Selector::elegirOpcion("Alta de usuario - Rol del nuevo usuario",
    {
        {1, "Administrador"},
        {2, "Logistica"},
        {3, "Vendedor"},
        {0, "Cancelar"}
    });

    if (opcion == Selector::CANCELADO || opcion == 0)
    {
        cout << "Alta de usuario cancelada." << endl;
        system("pause");
        return;
    }

    if (opcion == 1)
    {
        _rolUsuario = "ADMINISTRADOR";
    }
    else if (opcion == 2)
    {
        _rolUsuario = "LOGISTICA";
    }
    else
    {
        _rolUsuario = "VENDEDOR";
    }
    cout << "Rol elegido: " << _rolUsuario << endl << endl;

    do
    {
        cout << "Nombre del usuario: ";
        if (!getline(cin >> ws, _nombreUsuario))
        {
            cout << "Sin entrada. Alta de usuario cancelada." << endl;
            system("pause");
            return;
        }
        if (_nombreUsuario.empty())
        {
            cout << "El nombre no puede quedar vacio." << endl;
        }
    } while (_nombreUsuario.empty());

    do
    {
        cout << "Apellido del usuario: ";
        if (!getline(cin >> ws, _apellidoUsuario))
        {
            cout << "Sin entrada. Alta de usuario cancelada." << endl;
            system("pause");
            return;
        }
        if (_apellidoUsuario.empty())
        {
            cout << "El apellido no puede quedar vacio." << endl;
        }
    } while (_apellidoUsuario.empty());

    do
    {
        cout << "Contrasena del usuario: ";
        if (!getline(cin >> ws, _password))
        {
            cout << "Sin entrada. Alta de usuario cancelada." << endl;
            system("pause");
            return;
        }
        if (_password.empty())
        {
            cout << "La contrasena no puede quedar vacia." << endl;
        }
    } while (_password.empty());

    string confirmacion;
    do
    {
        cout << "Repita la contrasena: ";
        if (!getline(cin >> ws, confirmacion))
        {
            cout << "Sin entrada. Alta de usuario cancelada." << endl;
            system("pause");
            return;
        }
        if (confirmacion != _password)
        {
            cout << "Las contrasenas no coinciden. Intente de nuevo." << endl;
        }
    } while (confirmacion != _password);

    GestorBaseDatos altaUsuario;
    altaUsuario.AltaDeUsuario(_nombreUsuario, _apellidoUsuario, _rolUsuario, _password);

    system("pause");
}

