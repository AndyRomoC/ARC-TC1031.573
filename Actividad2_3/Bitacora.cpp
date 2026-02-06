
#include "Bitacora.h"
#include <sstream>
#include <ctime>

//Constructor
//Complejidad: O(1)

Bitacora::Bitacora() {}

//Destructor
//Complejidad: O(n)

Bitacora::~Bitacora() {}

/*
Descripcion: Lee archivo y llena la lista
Parametros: nombreArchivo
Retorno: void
Complejidad: O(n)
*/
void Bitacora::leerArchivo(std::string nombreArchivo) {
    std::ifstream file(nombreArchivo);
    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return;
    }

    std::string mes, dia, tiempo, ipPuerto, falla, linea;
    while (file >> mes >> dia >> tiempo >> ipPuerto) {
        std::getline(file, falla);

        std::string h = tiempo.substr(0, 2);
        std::string m = tiempo.substr(3, 2);
        std::string s = tiempo.substr(6, 2);

        std::string ip = ipPuerto.substr(0, ipPuerto.find(':'));
        std::string puerto = ipPuerto.substr(ipPuerto.find(':') + 1);

        if (!falla.empty() && falla[0] == ' ') falla.erase(0, 1);

        Registro reg(mes, dia, h, m, s, ip, puerto, falla);
        lista.addLast(reg);
    }
    file.close();
}

/*
Descripcion: Ejecuta el ordenamiento y guarda resultado
Parametros: algoritmo (1=Merge, 2=Quick)
Retorno: void
Complejidad: O(n log n)
 */
void Bitacora::ordenar(int algoritmo) {
    clock_t start = clock();

    if (algoritmo == 1) lista.sortMerge();
    else lista.sortQuick();

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "Ordenamiento completado en " << duration << " ms." << std::endl;

    // Guardado O(n^2) en lista ligada por acceso secuencial
    std::ofstream sal("bitacora_ordenada.txt");
    int n = lista.getNumElements();
    for(int i = 0; i < n; i++) {
        sal << lista.getElementAt(i) << "\n";
    }
    sal.close();
}

/*
 Descripcion: Busca un rango de fechas y imprime resultados
Parametros: fechaInicio, fechaFin
Retorno: void
Complejidad: O(n log n)
 */
void Bitacora::buscarRango(std::string fechaInicio, std::string fechaFin) {
    std::stringstream ss1(fechaInicio), ss2(fechaFin);
    std::string m1, d1, t1, m2, d2, t2;
    ss1 >> m1 >> d1 >> t1;
    ss2 >> m2 >> d2 >> t2;

    Registro rIni(m1, d1, t1.substr(0,2), t1.substr(3,2), t1.substr(6,2), "","","");
    Registro rFin(m2, d2, t2.substr(0,2), t2.substr(3,2), t2.substr(6,2), "","","");

    int idxInicio = lista.binarySearchFirst(rIni);
    int idxFin = lista.binarySearchLast(rFin);

    std::ofstream sal("resultado_busqueda.txt");

    if (idxInicio == -1 || idxFin == -1 || idxInicio > idxFin) {
        std::cout << "Resultado: 0 Registros" << std::endl;
        sal << "Resultado: 0 Registros" << std::endl;
    } else {
        int cantidad = idxFin - idxInicio + 1;
        std::cout << "Resultado: " << cantidad << " Registros" << std::endl;
        sal << "Resultado: " << cantidad << " Registros" << std::endl;

        for (int i = idxInicio; i <= idxFin; i++) {
            Registro r = lista.getElementAt(i);
            std::cout << r << std::endl;
            sal << r << std::endl;
        }
    }
    sal.close();
}