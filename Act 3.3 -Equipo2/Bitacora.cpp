#include "Bitacora.h"

//Constructor
Bitacora::Bitacora() {
}

//lee la bitacora y la guarda en un vector de registros
void Bitacora::leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error al abrir el archivo: " + nombreArchivo);
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (!linea.empty()) {
            Registro r(linea);
            registros.push_back(r);
        }
    }

    archivo.close();
}

/*
  heapify --> mantiene max-heap en el subarbol con raiz en i
  https://www.geeksforgeeks.org/heap-sort/
*/
void Bitacora::heapify(int n, int i) {
    int largest = i;        // raíz
    int left = 2 * i + 1;   // hijo izq
    int right = 2 * i + 2;  // hijo der

    // hijo izquierdo > raiz 
    if (left < n && registros[largest] < registros[left]) {
        largest = left;
    }

    // hijo derecho >  mas grande hasta ahora
    if (right < n && registros[largest] < registros[right]) {
        largest = right;
    }

    // más grande no es la raiz
    if (largest != i) {
        std::swap(registros[i], registros[largest]);
        heapify(n, largest);
    }
}

/*
 Heap Sort --> ordena el vector registros por IP
 Complejidad:
   - construccion del heap: O(n)
   - extracción de elementos: O(n log n)
   - total: O(n log n)
 */
void Bitacora::heapSort() {
    int n = registros.size();

    // Max-Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(n, i);
    }

    // extraer elementos (uno por uno)
    for (int i = n - 1; i >= 0; i--) {
        std::swap(registros[0], registros[i]);
        heapify(i, 0);
    }
}

// metodo ordenar por IP
void Bitacora::ordenarPorIP() {
    heapSort();
}

//guardar la bitacora en archivo de txt
void Bitacora::guardarOrdenada(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error al crear --> " + nombreArchivo);
    }

    for (const Registro& r : registros) {
        archivo << r.toString() << std::endl;
    }

    archivo.close();
}

// binary heap con cada IP y la cant de accesos

std::priority_queue<IPAccess> Bitacora::construirHeapIPs() const {
    std::priority_queue<IPAccess> heap;

    if (registros.empty()) {
        return heap;
    }

    std::string ipActual = registros[0].getIP();
    int contador = 1;

    for (size_t i = 1; i < registros.size(); i++) {
        if (registros[i].getIP() == ipActual) {
            contador++;
        } else {
            heap.push(IPAccess(ipActual, contador));
            ipActual = registros[i].getIP();
            contador = 1;
        }
    }

    heap.push(IPAccess(ipActual, contador));

    return heap;
}

/*
 10 IP con mayor num de accesos
 */
void Bitacora::mostrarTop10(std::priority_queue<IPAccess>& heap) const {
    std::cout << "\n10 IP con mayor num de accesos:\n";
    std::cout << "****************************************\n";

    for (int i = 0; i < 10 && !heap.empty(); i++) {
        IPAccess top = heap.top();
        heap.pop();
        std::cout << (i + 1) << ". " << top.ip
                  << " - accesos: " << top.accesos << std::endl;
    }
}

//guardar en un archivo 
void Bitacora::guardarTop10(const std::string& nombreArchivo,
                            std::priority_queue<IPAccess>& heap) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error al crear el archivo: " + nombreArchivo);
    }

    archivo << "10 IPs con mayor num de accesos:\n";
    archivo << "****************************************\n";

    for (int i = 0; i < 10 && !heap.empty(); i++) {
        IPAccess top = heap.top();
        heap.pop();
        archivo << (i + 1) << ". " << top.ip
                << " - accesos: " << top.accesos << std::endl;
    }

    archivo.close();
}

//Get
std::vector<Registro>& Bitacora::getRegistros() {
    return registros;
}

