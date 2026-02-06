#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <sstream>

/* Registro --> representa una linea de la bitacora
   Formato: MES-DIA-HORA-IP:PUERTO MENSAJE...
   EJ:
   Oct 9 10:32:24 10.15.175.231:6166 Failed password for illegal user guest
*/

class Registro {
private:
    std::string mes;
    int dia;
    std::string hora;
    std::string ipCompleta;   // 10.15.175.231:6166
    std::string ip;           // 10.15.175.231
    int puerto;               // 6166
    std::string mensaje;

public:
    Registro();
    Registro(const std::string& linea);

    // Gets
    std::string getMes() const;
    int getDia() const;
    std::string getHora() const;
    std::string getIPCompleta() const;
    std::string getIP() const;
    int getPuerto() const;
    std::string getMensaje() const;

    // devuelve registro en formato original
    std::string toString() const;

    // comparacion por IP 
    bool operator<(const Registro& other) const;
};

#endif
