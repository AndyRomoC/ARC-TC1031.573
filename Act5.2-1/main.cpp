/**
 *
 * ACT 4.3 - Análisis de Bitácora con Grafos y Tabla Hash
 *
 * Descripción:
 * Este programa lee un archivo de bitácora que contiene direcciones IP e incidencias
 * de acceso entre ellas. Con esta información se construye un grafo dirigido mediante
 * una lista de adyacencias organizada por IP.
 *
 * Posteriormente, con base en el grafo, se implementa una tabla hash utilizando
 * direccionamiento abierto con prueba cuadrática para almacenar un resumen de cada IP:
 *
 *  IP en formato string
 *  Total de direcciones accesadas desde dicha IP (OutDegree)
 *  Total de direcciones que intentaron acceder a dicha IP (InDegree)
 *
 * El programa contabiliza el número total de colisiones generadas durante la inserción
 * en la tabla hash y permite consultar el resumen de una IP específica.
 *
 * Compilación para debug:
 * g++ -std=c++17 -g -Wall -Wextra -o main *.cpp
 *
 * Compilación optimizada:
 * g++ -std=c++17 -O3 -o main *.cpp
 *
 * Ejecución:
 * ./main
 *
 * Archivo de entrada requerido:
 *  - bitacoraGrafos.txt
 *
 * Miembros del equipo 2:
 * Rodrigo Martínez Escalante - A00838495
 * Paula Guerrero Martínez - A00839099
 * Andres Romo - A01234579
 *
 */




#include <iostream>
#include "IPGraph.h"

int main(){

    IPGraph g;

    g.readBitacora("bitacoraGrafos.txt");

    // Mostrar número de IPs
    std::cout << "\nEl archivo contiene "
              << g.getNumIPs()
              << " direcciones IP.\n";

    std::cout << "Elige un tamaño de tabla hash >= "
              << g.getNumIPs()
              << " (primo recomendado).\n";

    int size;
    std::cout << "Tamaño tabla hash: ";
    std::cin >> size;

    g.buildHashTable(size);

    g.getIPSummary();

    return 0;
}
