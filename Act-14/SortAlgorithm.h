#ifndef _ALGORITHM_SORT_H_
#define _ALGORITHM_SORT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

template <class T>
class AlgorithmSort {
  private:
    // semilla del generador de numeros aleatorios (time-based)
    unsigned seed; 
    // generador de numeros aleatorios (Mersenne Twister 64 bits)
    std::mt19937_64 gen;

    void merge(std::vector<T> &A, size_t low, size_t m, size_t high, size_t &compara);
    int partition(std::vector<T> &A, int low, int high, size_t &compara, size_t &swap);

  public:
    AlgorithmSort();
    ~AlgorithmSort();
    void randomShuffle(std::vector<T> &A);
    void printVector(std::vector<T> A);



    void bubbleSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);

    void mergeSort(std::vector<T> &A, size_t low, size_t high, size_t &compara);


};


template<class T>
AlgorithmSort<T>::AlgorithmSort() {
  // semilla del generador de numeros aleatorios (time-based)
  seed = std::chrono::system_clock::now().time_since_epoch().count();
  // generador de numeros aleatorios (Mersenne Twister 64 bits)
  std::mt19937_64 gen;
  // inicializar el generador con la semilla creada
  gen.seed(seed);
}

template<class T>
AlgorithmSort<T>::~AlgorithmSort() {

}

// Mezcla los elementos del vector en forma aleatoria
template<class T>
void AlgorithmSort<T>::randomShuffle(std::vector<T> &A) {
  std::shuffle(A.begin(), A.end(), gen);
}

// Imprime en pantalla los elementos del vector
template<class T>
void AlgorithmSort<T>::printVector(std::vector<T> A) {
    std::cout << "Los elementos del vector ordenado son: " << std::endl;
    for(size_t i = 0; i < A.size(); i++) {
      std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}




// O(n^2) peor caso
template<class T>
void AlgorithmSort<T>::bubbleSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap) {
  compara = swap = 0;
  for (size_t i = 0; i < n-1; i++) {
    for (size_t j = 0; j < n-i-1; j++) {
      compara++;
      if (A[j] > A[j+1]) {
        std::swap(A[j], A[j+1]);
        swap++;
      }
    }
  }
}



// O(n) peor caso
template<class T>
void AlgorithmSort<T>::merge(std::vector<T> &A, size_t low, size_t m, size_t high, size_t &compara) {
  size_t i, j, k;
  // calcular el tamaño de los vectores L y R
  size_t n1 = m - low + 1;
  size_t n2 = high - m;
  // Crear los vectores auxiliares L y R
  std::vector<T> L(n1);
  std::vector<T> R(n2);
  for (i = 0; i < n1; i++) L[i] = A[low + i];
  for (j = 0; j < n2; j++) R[j] = A[m + 1 + j];
  // Fusionar los vectores L y R de forma ordenada
  i = j = 0;
  k = low;
  while (i < n1 && j < n2) {
    compara++;
    if (L[i] <= R[i]) {
      A[k] = L[i];
      i++;
    }
    else {
      A[k] = R[j];
      j++;
    }
    k++;
  }
  // Copiar elementos restantes de L y R, si existen
  while (i < n1) { A[k] = L[i]; i++; k++; }
  while (j < n2) { A[k] = R[j]; j++; k++; }
}

// O(n log n) pero caso
template<class T>
void AlgorithmSort<T>::mergeSort(std::vector<T> &A, size_t low, size_t high, size_t &compara) {
  if (low < high) {
    // encontrar el punto medio
    size_t m = low + (high - low) / 2;
    // Dividir el problema en dos partes
    mergeSort(A, low, m, compara);
    mergeSort(A, m+1, high, compara);
    // Fusionar ambas partes ordenadas
    merge(A, low, m, high, compara);
  }
}


#endif   // _ALGORITHM_SORT_H_

