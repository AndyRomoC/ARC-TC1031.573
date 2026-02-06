//Implementacion de la clase Registro

#include "Registro.h"

/*
 Descripcion: Constructor
 Parametros: Ninguno
 Retorno: N/A
 Complejidad: O(1)
 */
Registro::Registro() : fechaHora(0) {}

/*
Descripcion: Constructor que convierte fecha a timestamp
Parametros: Cadenas con partes de la fecha y datos
Retorno: N/A
Complejidad: O(1)
 */
Registro::Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla) {
    mes = _mes; dia = _dia; horas = _horas; minutos = _minutos; segundos = _segundos;
    ip = _ip; puerto = _puerto; falla = _falla;

    dateStruct.tm_hour = std::stoi(horas);
    dateStruct.tm_min = std::stoi(minutos);
    dateStruct.tm_sec = std::stoi(segundos);
    dateStruct.tm_mday = std::stoi(dia);
    dateStruct.tm_isdst = -1;
    dateStruct.tm_year = 2024 - 1900;

    dateStruct.tm_mon = 0;
    for (int i = 0; i < 12; i++) {
        if (nombresMeses[i] == mes) {
            dateStruct.tm_mon = i;
            break;
        }
    }
    fechaHora = mktime(&dateStruct);
}

/*
Descripcion: Retorna en string
Parametros: Ninguno
Retorno: string
Complejidad: O(1)
 */
std::string Registro::getAll() const {
    return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;
}

// Sobrecargas de comparacion
//Complejidad: O(1) para todas
bool Registro::operator==(const Registro &other) const { return this->fechaHora == other.fechaHora; }
bool Registro::operator!=(const Registro &other) const { return this->fechaHora != other.fechaHora; }
bool Registro::operator>(const Registro &other) const { return this->fechaHora > other.fechaHora; }
bool Registro::operator<(const Registro &other) const { return this->fechaHora < other.fechaHora; }
bool Registro::operator>=(const Registro &other) const { return this->fechaHora >= other.fechaHora; }
bool Registro::operator<=(const Registro &other) const { return this->fechaHora <= other.fechaHora; }

std::ostream& operator<<(std::ostream& os, const Registro& reg) {
    os << reg.getAll();
    return os;
}