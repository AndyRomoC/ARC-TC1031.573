#include <iostream>
#include "Bitacora.h"
/**
  Act 3.3 – Actividad Integral de BST (Evidencia Competencia)

  Binary Heap: std::priority_queue (STL de C++).

  Referencias:
   - Heap Sort: https://www.geeksforgeeks.org/heap-sort/
   - Binary Heap: https://www.geeksforgeeks.org/binary-heap/
   - priority_queue: https://cplusplus.com/reference/queue/priority_queue/

  Compilación para debug:
     g++ -std=c++17 -g -Wall -o main *.cpp

  Ejecución con Valgrind:
     (Agregar valgrind al entorno si es necesario)
     valgrind --run-libc-freeres=no --leak-check=full ./main

  Compilación para ejecución:
     g++ -std=c++17 -O3 -o main *.cpp

  Ejecución:
     ./main

  Equipo 2
  Integrantes:
    - Paula Guerrero Martínez    - A00839099
    - Rodrigo Martínez Escalante - A00838495
    - Andres Romo Castañeda      - A01234579

 */

int main() {
    try {
        Bitacora bitacora;

        // leer archivo 
        std::cout << "leyendo: bitacoraHeap_1769650119417.txt..." << std::endl;
        bitacora.leerArchivo("attached_assets/bitacoraHeap_1769650119417.txt");
        std::cout << "COMPLETADO" << std::endl;

        // ordenar bitácora por IP con Heap Sort
        std::cout << "ordenando bitacora por IP con heap sort..." << std::endl;
        bitacora.ordenarPorIP();
        std::cout << "COMPLETADO." << std::endl;

        // guardar bitacora ordenada
        std::cout << "guardando bitacora ordenada en: bitacora_ordenada.txt..." << std::endl;
        bitacora.guardarOrdenada("bitacora_ordenada.txt");
        std::cout << "COMPLETADO" << std::endl;

        // construir Binary Heap con s IP y accesos
        std::cout << "construyendo binary heap accesos por IP..." << std::endl;
        std::priority_queue<IPAccess> heapIPs = bitacora.construirHeapIPs();
        std::cout << "COMPLETADO" << std::endl;

        // mostrar las 10 IP con mas numero de accesos
        bitacora.mostrarTop10(heapIPs);

        // constructor de binary heap
        heapIPs = bitacora.construirHeapIPs();

        // guardar las 10 IP  en archivo
        std::cout << "\nguardando top 10 de IP --> ips_con_mayor_acceso.txt..." << std::endl;
        bitacora.guardarTop10("ips_con_mayor_acceso.txt", heapIPs);
        std::cout << "COMPLETADO" << std::endl;

        std::cout << "\nprograma finalizado" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
