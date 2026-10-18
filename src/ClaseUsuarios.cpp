#include "../include/ClaseUsuarios.h"
#include "../include/GestorBaseDatos.h"
#include "../include/Selector.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std; 

/// Definicion del usuario logueado (miembro estatico de la clase).
/// Sin esta linea el linker da "undefined reference to ClaseUsuarios::_usuarioLogeado".
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
    GestorBaseDatos cargaUser;
    cargaUser.conectar("db/Almacen.db"); 
    if (!cargaUser.conectar("db/Almacen.db"))
    {
        cout << "No se pudo conectar a la base de datos:" <<endl;
        system("pause");
        return;
    }
    
    int opcion = Selector::elegirOpcion("Alta de usuario - Rol del nuevo usuario",
    {
        {1, "Administrador"},
        {2, "Logistica"},
        {3, "Vendedor"}
    });

    if (opcion == Selector::CANCELADO)
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
    cout << "Usted eligio: " << _rolUsuario << endl;

    cout << "Ingrese nombre del usuario:" << endl;
    cin >> _nombreUsuario;

    cout << "Ingrese el apellido del usuario:" << endl;
    cin >> _apellidoUsuario;

    cout << "Cree la su contraseña: " << endl;
    cin >> _password;
    cargaUser.AltaDeUsuario(_nombreUsuario, _apellidoUsuario, _rolUsuario, _password);
    system("pause");
    

}

