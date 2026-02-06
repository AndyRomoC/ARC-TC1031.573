
#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <string>
#include <fstream>
#include "DoublyLinkedList.h"
#include "Registro.h"

class Bitacora {
private:
    DoublyLinkedList<Registro> lista;

public:
    Bitacora();
    ~Bitacora();

    void leerArchivo(std::string nombreArchivo);
    void ordenar(int algoritmo);
    void buscarRango(std::string fechaInicio, std::string fechaFin);
};

#endif // _BITACORA_H_