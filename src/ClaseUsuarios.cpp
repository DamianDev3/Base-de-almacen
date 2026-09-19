#include "../include/ClaseUsuarios.h"
#include "../include/GestorBaseDatos.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std; 
 ClaseUsuarios::ClaseUsuarios()
{
    _idUsuario = 0;
    _nombreUsuario = "Usuario_sin_nombre";
    _rolUsuario = "Usuario_sin_rol";
}
ClaseUsuarios::ClaseUsuarios(int idUsuario,const string& nombreUsuario,const string& rolUsuario, const string& password)
{
    _idUsuario = idUsuario;
    _nombreUsuario = nombreUsuario;
    _rolUsuario = rolUsuario;

} 
void ClaseUsuarios::setIdUsuario(int idUser)
{
    _idUsuario = idUser;
}
void ClaseUsuarios::setNombreUsuario(string nombreUser)
{
    _nombreUsuario = nombreUser;
}
void ClaseUsuarios::setRolUsuario(string rolUser)
{
    _rolUsuario = rolUser;
}

void ClaseUsuarios::setPassword(string passwordUser)
{
    _password = passwordUser;
}
int ClaseUsuarios::getIdUsuario()
{
    return _idUsuario;

}
string ClaseUsuarios::getNombreUsuario()
{
    return _nombreUsuario;
}
string ClaseUsuarios::getRolUsuario()
{
    return _rolUsuario;
}

string ClaseUsuarios::getPassword()
{
    return _password;
}
void ClaseUsuarios::cargaDeUsuario()
{
    GestorBaseDatos cargaUser;
    cout << "Ingrese el Rol del usuario:" <<endl;
    cin >> _rolUsuario;
    

    cout << "Ingrese nombre del usuario:" <<endl;
    cin >> _nombreUsuario;

    cout << "Cree la su contrasenia: " <<endl;
    cin >> _password;
    cargaUser.AltaDeUsuario(_rolUsuario,_nombreUsuario,_password);

}