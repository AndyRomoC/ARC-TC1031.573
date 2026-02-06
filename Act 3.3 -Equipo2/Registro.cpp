#include "Registro.h"

//Constructor
Registro::Registro() {
    mes = "";
    dia = 0;
    hora = "";
    ipCompleta = "";
    ip = "";
    puerto = 0;
    mensaje = "";
}

//recibe una linea completa de bitacora y separa cada uno de los datos
Registro::Registro(const std::string& linea) {
    std::stringstream ss(linea);

    ss >> mes;
    ss >> dia;
    ss >> hora;
    ss >> ipCompleta;

    // separa IP y puerto
    std::size_t pos = ipCompleta.find(':');
    if (pos != std::string::npos) {
        ip = ipCompleta.substr(0, pos);
        puerto = std::stoi(ipCompleta.substr(pos + 1));
    } else {
        ip = ipCompleta;
        puerto = 0;
    }

    std::getline(ss, mensaje);
    //quitar espacio inicial
    if (!mensaje.empty() && mensaje[0] == ' ') {
        mensaje = mensaje.substr(1);
    }
}

// Gets
std::string Registro::getMes() const {
    return mes;
}

int Registro::getDia() const {
    return dia;
}

std::string Registro::getHora() const {
    return hora;
}

std::string Registro::getIPCompleta() const {
    return ipCompleta;
}

std::string Registro::getIP() const {
    return ip;
}

int Registro::getPuerto() const {
    return puerto;
}

std::string Registro::getMensaje() const {
    return mensaje;
}

//devolver el registro en el formato original 
std::string Registro::toString() const {
    std::stringstream ss;
    ss << mes << " " << dia << " " << hora << " "
       << ipCompleta << " " << mensaje;
    return ss.str();
}

//sobrecarga del operador < para comparar registros por IP
bool Registro::operator<(const Registro& other) const {
    return this->ip < other.ip;
}
