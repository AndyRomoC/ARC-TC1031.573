#ifndef BITACORA_H
#define BITACORA_H

#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "Registro.h"

/*
   guarda IP y cantidad de accesos
   priority_queue en C++ esta implementada como un Binary Heap
   https://cplusplus.com/reference/queue/priority_queue/
*/
struct IPAccess {
    std::string ip;
    int accesos;

    IPAccess(const std::string& _ip, int _accesos) {
        ip = _ip;
        accesos = _accesos;
    }

    /*
     sobrecarga del operador < 
     priority_queue es un Max-Heap por defecto, asi la IP con mayor numero de accesos va hasta arriba de la lista
     */
    bool operator<(const IPAccess& other) const {
        return accesos < other.accesos;
    }
};

/*
  Bitacora
   - lee archivo bitacoraHeap.txt
   - almacena registros en vector
   - ordena registros por IP (heap sort)
   - guardar la bitácora ordenada
   - contar accesos por IP
   - construir binary heap con las IP
   - obtener top 10 IP con mayor número de accesos
 */
class Bitacora {
private:
    std::vector<Registro> registros;

    void heapify(int n, int i);
    void heapSort();

public:
    Bitacora();

    //leer archivo
    void leerArchivo(const std::string& nombreArchivo);

    // ordenar por IP
    void ordenarPorIP();

    // guardar bitácora ordenada
    void guardarOrdenada(const std::string& nombreArchivo) const;

    // construir binary heap 
    std::priority_queue<IPAccess> construirHeapIPs() const;

    // mostrar 10 IP con más accesos
    void mostrarTop10(std::priority_queue<IPAccess>& heap) const;

    // guardar
    void guardarTop10(const std::string& nombreArchivo,
                      std::priority_queue<IPAccess>& heap) const;

    // Get registros
    std::vector<Registro>& getRegistros();
};

#endif
