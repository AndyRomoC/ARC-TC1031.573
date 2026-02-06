#ifndef _SEARCH_ALGORITHM_H_
#define _SEARCH_ALGORITHM_H_

#include <iostream>
#include <vector>

template <class T>
class SearchAlgorithm {
  public:
    SearchAlgorithm();
    ~SearchAlgorithm();
    int busquedaSecuencial(const std::vector<T> &A, T key, size_t &compara);
    int busquedaBinaria(const std::vector<T> &A, T key, size_t &compara);
    // Nuevo: Búsqueda de rango secuencial
    void busquedaSecuencialRango(const std::vector<T> &A, T inicio, T fin, int &idxI, int &idxF);
};

template <class T>
SearchAlgorithm<T>::SearchAlgorithm() {

}

template <class T>
SearchAlgorithm<T>::~SearchAlgorithm() {

}

// O(n) peor caso
template <class T>
int SearchAlgorithm<T>::busquedaSecuencial(const std::vector<T> &A, T key, size_t &compara) {
  compara = 0;
  size_t i = 0;
  while (i < A.size() && A[i] != key) {
    compara++;
    i++;
  }
  if (i < A.size())
    return i;
  else
    return -1;
}


// O(log n) peor caso
template <class T>
int SearchAlgorithm<T>::busquedaBinaria(const std::vector<T> &A, T key, size_t &compara) {
  compara = 0;
  if (A.empty()) return -1;
  int l = 0;
  int r = (int)A.size() - 1;
  int bestIdx = -1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    compara++;
    if (key == A[m])
      return m;
    else if (key < A[m]) {
      bestIdx = m; // Candidato por si no hay coincidencia exacta
      r = m - 1;
    }
    else
      l = m + 1;
  }
  return bestIdx;
}

template <class T>
void SearchAlgorithm<T>::busquedaSecuencialRango(const std::vector<T> &A, T inicio, T fin, int &idxI, int &idxF) {
  idxI = -1;
  idxF = -1;
  for (int i = 0; i < (int)A.size(); i++) {
    if (A[i] >= inicio && idxI == -1) {
      idxI = i;
    }
    if (A[i] <= fin) {
      idxF = i;
    }
  }
}





#endif  // _SEARCH_ALGORITHM_H_
