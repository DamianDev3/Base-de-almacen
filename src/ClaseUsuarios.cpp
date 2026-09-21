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
string ClaseUsuarios::getApellidoUsuario()
{
    return _apellidoUsuario;
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
    int opcion;
    GestorBaseDatos cargaUser;
    cargaUser.conectar("db/Almacen.db"); 
    bool carga = false;
    while (!carga)
    {
           cout << "Ingrese el Rol del usuario, 1- Para Administrador, 2- Para Logistica o 3- Para Vendedor:" <<endl;
    cin >> opcion;
             cin.ignore();
     if (cin.fail())
        {
         cin.clear();
         cin.ignore(10000, '\n');
         opcion = -1;
             }

    if(opcion == 1)
    {
        _rolUsuario = "ADMINISTRADOR";
        cout << "Usted eligio "<< " " << _rolUsuario << endl;
    
    }
    else if (opcion == 2)
    {
        _rolUsuario = "LOGISTICA";
        cout << "Usted eligio: "<< " " << _rolUsuario << endl;
    }
    else if (opcion == 3)
    {
        _rolUsuario = "VENDEDOR";
        cout << "Usted eligio: "<<" " << _rolUsuario << endl;
    }
    else
    {
        cout << "Opcion invalida:" <<endl;
        continue;
    }
    

    cout << "Ingrese nombre del usuario:" <<endl;
    cin >> _nombreUsuario;

    cout << "Ingrese el apellido del usuario:" <<endl;
    cin >> _apellidoUsuario;

    cout << "Cree la su contraseña: " <<endl;
    cin >> _password;
    cargaUser.AltaDeUsuario(_nombreUsuario,_apellidoUsuario,_rolUsuario,_password);
    carga = true;
    system("pause");
    }
    

}