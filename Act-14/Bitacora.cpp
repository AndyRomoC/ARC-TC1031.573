#include "Bitacora.h"
#include <sstream>
#include <algorithm>
#include "SortAlgorithm.h"
#include "SearchAlgorithm.h"
#include <chrono>



Bitacora::Bitacora() {}


Bitacora::~Bitacora() {}


// Leer archivo de bitácora
void Bitacora::leerArchivo(std::string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }

    std::string mes, dia, tiempo, ipPuerto;
    std::string linea, falla;

    while (file >> mes >> dia >> tiempo >> ipPuerto) {
        std::getline(file, falla);  // resto de la línea

        // separar tiempo
        std::stringstream ssTiempo(tiempo);
        std::string horas, minutos, segundos;
        std::getline(ssTiempo, horas, ':');
        std::getline(ssTiempo, minutos, ':');
        std::getline(ssTiempo, segundos, ':');

        // separar ip y puerto
        std::stringstream ssIP(ipPuerto);
        std::string ip, puerto;
        std::getline(ssIP, ip, ':');
        std::getline(ssIP, puerto, ':');

        // quitar espacio inicial de la falla
        if (!falla.empty() && falla[0] == ' ')
            falla.erase(0, 1);

        Registro reg(mes, dia, horas, minutos, segundos, ip, puerto, falla);
        listaRegistros.push_back(reg);
    }

    file.close();
}


// Ordenar registros
std::vector<Registro> Bitacora::sort(int num, int algorithm) {
    AlgorithmSort<Registro> sorter;

    size_t comparaciones = 0;
    size_t swaps = 0;

    auto inicio = std::chrono::high_resolution_clock::now();

    if (algorithm == 1) {
        // Bubble Sort directamente sobre listaRegistros
        sorter.bubbleSort(listaRegistros, listaRegistros.size(), comparaciones, swaps);
    }
    else if (algorithm == 2) {
        // Merge Sort directamente sobre listaRegistros
        sorter.mergeSort(listaRegistros, 0, listaRegistros.size() - 1, comparaciones);
    }
    else {
        throw std::invalid_argument("Algoritmo invalido. Usa 1 (Bubble) o 2 (Merge)");
    }

    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

    std::cout << "Tiempo de ejecucion: " << duracion.count() << " ms" << std::endl;
    std::cout << "Comparaciones: " << comparaciones << std::endl;

    if (algorithm == 1) {
        std::cout << "Swaps: " << swaps << std::endl;
    }

    // Guardar la bitácora ordenada en archivo
    std::ofstream outFile("bitacora_ordenada.txt");
    if (outFile.is_open()) {
        for (const auto& reg : listaRegistros) {
            outFile << reg;
        }
        outFile.close();
        std::cout << "Bitácora completa ordenada guardada en 'bitacora_ordenada.txt'" << std::endl;
    }

    // Devolver copia de los registros solicitados
    std::vector<Registro> copia = listaRegistros;
    if (num > 0 && num < (int)copia.size()) {
        copia.resize(num);
    }

    return copia;
}


// Obtener registro exacto (búsqueda binaria)
Registro Bitacora::getRegistro(
    std::string dia,
    std::string mes,
    std::string horas,
    std::string minutos,
    std::string segundos,
    int algorithm
) {

    Registro key(mes, dia, horas, minutos, segundos, "", "", "");

    SearchAlgorithm<Registro> searcher;
    AlgorithmSort<Registro> sorter;

    size_t comparaciones = 0;
    int index = -1;

    auto inicio = std::chrono::high_resolution_clock::now();

    if (algorithm == 1) {
        // Búsqueda secuencial
        index = searcher.busquedaSecuencial(listaRegistros, key, comparaciones);
    }
    else if (algorithm == 2) {
        // Búsqueda binaria
        size_t compSort = 0;
        sorter.mergeSort(listaRegistros, 0, listaRegistros.size() - 1, compSort);

        index = searcher.busquedaBinaria(listaRegistros, key, comparaciones);
    }
    else {
        throw std::invalid_argument("Algoritmo invalido (1 = Secuencial, 2 = Binaria)");
    }

    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

    std::cout << "Tiempo de busqueda: " << duracion.count() << " ms" << std::endl;
    std::cout << "Comparaciones: " << comparaciones << std::endl;

    if (index == -1)
        throw std::runtime_error("Registro no encontrado");

    return listaRegistros[index];
}



// Buscar e imprimir registros en un rango
void Bitacora::searchRegistroRange(Registro inicio, Registro fin, int algorithm) {
    // Ordenar siempre para asegurar correctitud
    std::sort(listaRegistros.begin(), listaRegistros.end());

    int idxInicio = -1;
    int idxFin = -1;
    SearchAlgorithm<Registro> searcher;

    if (algorithm == 1) {
        // Búsqueda Secuencial de Rango usando el método de la clase
        searcher.busquedaSecuencialRango(listaRegistros, inicio, fin, idxInicio, idxFin);
    } else if (algorithm == 2) {
        // Búsqueda Binaria de Rango usando el método de la clase
        size_t comp = 0;
        idxInicio = searcher.busquedaBinaria(listaRegistros, inicio, comp);
        idxFin = searcher.busquedaBinaria(listaRegistros, fin, comp);
        
        if (idxFin == -1) {
            idxFin = (int)listaRegistros.size() - 1;
        } else if (listaRegistros[idxFin] > fin && idxFin > 0) {
            idxFin--;
        }
    }

    if (idxInicio == -1 || idxFin == -1 || idxInicio > idxFin) {
        std::cout << "No se encontraron registros en el rango solicitado" << std::endl;
        return;
    }

    // Guardar resultados ordenados en un archivo
    std::ofstream outFile("resultado_busqueda.txt");
    int totalEncontrados = idxFin - idxInicio + 1;

    if (outFile.is_open()) {
        for (int i = idxInicio; i <= idxFin; i++) {
            std::cout << listaRegistros[i];
            outFile << listaRegistros[i];
        }
        outFile.close();
        std::cout << "\nTotal de registros encontrados: " << totalEncontrados << std::endl;
        std::cout << "Resultados guardados en 'resultado_busqueda.txt'" << std::endl;
    } else {
        for (int i = idxInicio; i <= idxFin; i++) {
            std::cout << listaRegistros[i];
        }
        std::cout << "\nTotal de registros encontrados: " << totalEncontrados << std::endl;
    }
}



// Imprimir los primeros n registros
void Bitacora::printRegistros(int n) {
    int limite = std::min(n, (int)listaRegistros.size());
    for (int i = 0; i < limite; i++) {
        std::cout << listaRegistros[i];
    }
}
