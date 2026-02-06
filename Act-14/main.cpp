/**
 * Programa que procesa una bitácora de accesos almacenada en un archivo de texto.
 * Cada línea se convierte en un objeto de la clase Registro, el cual transforma
 * la fecha y hora a un Linux timestamp para permitir comparaciones eficientes
 * mediante sobrecarga de operadores.
 *
 * El programa permite al usuario:
 *  - Seleccionar un algoritmo de ordenamiento (Bubble Sort o Merge Sort)
 *  - Ordenar todos los registros de la bitácora
 *  - Ingresar un rango de fechas (inicio y fin)
 *  - Seleccionar un algoritmo de búsqueda (Secuencial o Binaria)
 *  - Mostrar todos los registros que se encuentran dentro del rango indicado
 *
 * Compilación para depuración:
 *    g++ -std=c++17 -g -o main *.cpp
 *
 * Ejecución con Valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main
 *
 * Compilación optimizada para ejecución:
 *    g++ -std=c++17 -O3 -o main *.cpp
 *
 * Ejecución:
 *    ./main
 *
 * Integrantes del equipo:
 * A00838495 Rodrigo Martínez Escalante
 * A01234579 Andres Romo
 * A00839099 Paula Guerrero Martínez
 *
 * Fecha de creación: 19-01-2026
 

 */

#include <iostream>
#include "Bitacora.h"

int main() {
    try {
        Bitacora bitacora;


        std::string archivo = "bitacoraData.txt";
        bitacora.leerArchivo(archivo);

        int algSort;
        std::cout << "Seleccione algoritmo de ordenamiento:\n";
        std::cout << "1) Bubble Sort\n";
        std::cout << "2) Merge Sort\n";
        std::cout << "Opcion: ";
        std::cin >> algSort;

        std::cout << "\nOrdenando registros...\n";
        bitacora.sort(0, algSort); 


        std::string fecha1, fecha2;

        std::cin.ignore(); 
        std::cout << "\nIngrese FECHA INICIO (ej: Jun 01 00:22:36): ";
        std::getline(std::cin, fecha1);

        std::cout << "Ingrese FECHA FIN (ej: Jun 01 00:22:36): ";
        std::getline(std::cin, fecha2);

        Registro inicio(fecha1);
        Registro fin(fecha2);

        int algSearch;
        std::cout << "\nSeleccione algoritmo de busqueda:\n";
        std::cout << "1) Secuencial\n";
        std::cout << "2) Binaria\n";
        std::cout << "Opcion: ";
        std::cin >> algSearch;

        std::cout << "\nRegistros en el rango solicitado:\n";
        std::cout << "---------------------------------\n";

        bitacora.searchRegistroRange(inicio, fin, algSearch);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
