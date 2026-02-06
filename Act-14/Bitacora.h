#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Registro.h"

class Bitacora {
  private:
    std::vector<Registro> listaRegistros;

  public:
    Bitacora();
    ~Bitacora();

    void leerArchivo(std::string filePath);

    std::vector<Registro> sort(int num, int algorithm);

    Registro getRegistro(std::string dia, std::string mes, std::string horas, std::string minutos, std::string segundos, int algorithm);

    void searchRegistroRange(Registro inicio, Registro fin, int algorithm);

    void printRegistros(int n);

};


#endif  // _BITACORA_H_
