/**
 *
 * ACT 4.3 - Análisis de Bitácora con Grafos
 * Compilación para debug:
 * g++ -std=c++17 -g -Wall -Wextra -o main *.cpp
 *
 * Ejecución con Valgrind:
 * (Agregar pkgs.valgrind a replit.nix si se usa Replit)
 *
 * valgrind --run-libc-freeres=no --leak-check=full ./main
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
 * Archivos de salida generados:
 *  - grados_ips.txt
 *  - mayores_grados_ips.txt
 *  - distancia_bootmaster.txt
 * Miembros del equipo 2:
 * Rodrigo Martínez Escalante - A00838495
 * Paula Guerrero Martínez - A00839099
 * Andres Romo - A01234579
 */


#include "IPGraph.h"

int main() {
    try {
        IPGraph g;

        g.readBitacora("bitacoraGrafos.txt");
        std::string boot = g.computeDegrees();
        g.shortestPathsFromBootMaster(boot);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
