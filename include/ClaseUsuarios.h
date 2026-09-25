#pragma once
#include <string>
class ClaseUsuarios
{
public:
    /// Constructores:
    ClaseUsuarios();
    ClaseUsuarios(int id, const std::string& nombre, const std::string& rol, const std::string& password); 
    void setIdUsuario(int);
    void setNombreUsuario(std::string);
    void setApellidoUsuario(std::string);
    void setRolUsuario(std::string);
    void setPassword(std::string);

    int getIdUsuario() const;
    std::string getNombreUsuario() const;
    std::string getApellidoUsuario() const;
    std::string getRolUsuario() const;
    std::string getPassword() const;

    void cargaDeUsuario();

private:
int _idUsuario;
std::string _nombreUsuario;
std::string _apellidoUsuario;
std::string _rolUsuario;
std::string _password;
};
