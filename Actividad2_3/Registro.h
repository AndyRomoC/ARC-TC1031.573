/*
Descripcion: Clase que representa un registro de la bitacora
*/

#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <string>
#include <ctime>
#include <iostream>

class Registro {
private:
    std::string mes;
    std::string dia;
    std::string horas, minutos, segundos;
    std::string ip, puerto;
    std::string falla;

    //arreglo de los meses
    std::string nombresMeses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    struct tm dateStruct;
    time_t fechaHora;

public:
    Registro();
    Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla);

    std::string getAll() const;

    //sobrecargas
    bool operator ==(const Registro &other) const;
    bool operator !=(const Registro &other) const;
    bool operator >(const Registro &other) const;
    bool operator <(const Registro &other) const;
    bool operator >=(const Registro &other) const;
    bool operator <=(const Registro &other) const;

    friend std::ostream& operator<<(std::ostream& os, const Registro& reg);
};

#endif // _REGISTRO_H_