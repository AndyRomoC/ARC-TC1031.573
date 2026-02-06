/*
 Programa que procesa una bitacora de accesos implementando una estructura de datos
lineal dinamica tipo Lista Doblemente Ligada (Doubly Linked List).

Cada linea del archivo se convierte en un objeto de la clase Registro, transformando
la fecha y hora a un timestamp (time_t) para permitir comparaciones eficientes
mediante la sobrecarga de operadores.

El programa permite al usuario:
- Cargar datos masivos desde un archivo de texto a una estructura enlazada personalizada.
- Seleccionar y comparar algoritmos de ordenamiento: Merge Sort y Quick Sort.
- Ordenar cronologicamente todos los registros de la bitacora.
- Realizar busquedas eficientes de rangos de fechas (inicio y fin) usando Busqueda Binaria.
- Generar archivos de salida con la bitacora ordenada y los resultados de la busqueda.

Integrantes del equipo:
- A00838495 Rodrigo Martínez Escalante
- A01234579 Andres Romo Castañeda
- A00839099 Paula Guerrero Martínez

Fecha: 01/22/2026

Compilación para depuración:
   g++ -std=c++17 -g -o main *.cpp

Ejecución con Valgrind:
   nix-env -iA nixpkgs.valgrind
    valgrind --leak-check=full ./main

Compilación optimizada para ejecución:
    g++ -std=c++17 -O3 -o main *.cpp

Ejecución:
    ./main

*/

#include <iostream>
#include "Bitacora.h"

int main() {
    Bitacora bitacora;
    bitacora.leerArchivo("bitacoraData.txt");

    int opcSort;
    std::cout << "Selecciona algoritmo para ordenar:\n1. MergeSort\n2. QuickSort\nOpcion: ";
    std::cin >> opcSort;

    bitacora.ordenar(opcSort);

    std::cin.ignore();
    std::string fInicio, fFin;
    std::cout << "\nIngresa fecha inicio (ej Jun 01 00:00:00): ";
    std::getline(std::cin, fInicio);
    std::cout << "Ingresa fecha fin (ej Jun 01 23:59:59): ";
    std::getline(std::cin, fFin);

    bitacora.buscarRango(fInicio, fFin);

    return 0;
}