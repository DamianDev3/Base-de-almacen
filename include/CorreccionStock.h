#pragma once
#include <string>
#include <ctime>
class CorreccionStock
{

    /////Ideas para corregir el stock: una es usar un ordenamiento de burbuja para que me muestre los productos de que tengan menor stock para que sean los primeros en reponerse
    ///// Otra es ir producto por producto para ver y analizar cuales hay que reponer y cuales se pueden dejar
    //// se pueden explorar otras ideas
public:

    ///// Constructor y Setters
    CorreccionStock();
    CorreccionStock(int, std::string, int, std::string, std::string, int, std::string, int, std::string, int, std::string, int);
    void setIdCorreccion(int);
    void setFehcayHora(std::string);
    void setCodigoInterno(int);
    void setProductoEan(std::string);
    void setProductoCorregido(std::string);
    void setStockActual(int);
    void setListaDeSistemas(std::string);
    void setCantidadCorregida(int);
    void setDireccion(std::string);
    void setStockResultante(int);
    void setUsuarioCorreccion(std::string);
    void setIdMovimiento(int);
    
    ////Fecha y hora
    void ingresarFechaHoraActual();
    std::string getFechaFormateada() const;
    std::string getHoraFormateada() const;
    std::string getFechaHoraSQL() const;  

    ////// Getters
    int getIdCorreccion() const;
    std::string getFechayHoracorreccion() const;
    int getCodigoInterno() const;
    std::string getProductoEan() const;
    std::string getProductoCorregido() const;
    int getStockactual() const;
    std::string getListaSistema() const;
    int getCatnidadcorregida() const;
    std::string getDireccion() const;
    int getStockResultante() const;
    std::string getUsuarioCorreccion() const;
    int getIdMovimiento() const;
    void HistorialdeMovimiento();
    
private:
    int _idDeCorreccion;
    std::string _fechayHora;
    int _codigoInterno;
    std::string _eanProductoCorreccion;
    std::string _productoCorregido;
    int _stockActual;
    std::string _motivoCorreccion;
    int _cantidadCorregida;
    std::string _direccion;
    int _stockResultante;
    std::string _usuarioCorreccion;
    int _idMovimiento;

};
