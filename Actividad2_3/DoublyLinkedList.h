//Clase de una lista doblemente ligada con algoritmos de ordenamiento
#ifndef _DOUBLYLINKEDLIST_H_
#define _DOUBLYLINKEDLIST_H_

#include "NodeDLL.h"
#include <iostream>
#include <stdexcept>

template <class T>
class DoublyLinkedList {
private:
    NodeDLL<T>* head;
    NodeDLL<T>* tail;
    int numElements;

    //Metodos para mergesort
    NodeDLL<T>* split(NodeDLL<T>* head);
    NodeDLL<T>* merge(NodeDLL<T>* first, NodeDLL<T>* second);
    NodeDLL<T>* mergeSortRecursive(NodeDLL<T>* node);

    //Metodos para quicksort
    NodeDLL<T>* partition(NodeDLL<T>* l, NodeDLL<T>* h);
    void quickSortRecursive(NodeDLL<T>* l, NodeDLL<T>* h);
    void swapData(NodeDLL<T>* a, NodeDLL<T>* b);

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void addLast(T value);
    int getNumElements() const;
    bool isEmpty();
    
    //acceso y busqueda
    T getElementAt(int index);
    int binarySearchFirst(T value); 
    int binarySearchLast(T value);  

    //algoritmos de ordenamiento
    void sortMerge(); 
    void sortQuick(); 
};

//Constructor
//Parametros: Ninguno
//Retorno: N/A
//Complejidad: O(1)
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

/*
Descripcion: Destructor de la lista y libera memoria
Parametros: Ninguno
Retorno: N/A
Complejidad: O(n) */

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    NodeDLL<T>* p = head;
    while (p != nullptr) {
        NodeDLL<T>* next = p->next;
        delete p;
        p = next;
    }
}

/*
 * Descripcion: Agrega un elemento al final de la lista
 * Parametros: value - elemento a agregar
 * Retorno: void
 * Complejidad: O(1)
 */
template <class T>
void DoublyLinkedList<T>::addLast(T value) {
    NodeDLL<T>* newNode = new NodeDLL<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    numElements++;
}

/*
 Descripcion: Obtiene el numero de elementos
 Parametros: Ninguno
 Retorno: int
 Complejidad: O(1)
 */
template <class T>
int DoublyLinkedList<T>::getNumElements() const {
    return numElements;
}

/*
 Descripcion: Obtiene el elemento en una posicion especifica
 Parametros: index que te da la posicion deseada
 Retorno: T
 Complejidad: O(n)
 */
template <class T>
T DoublyLinkedList<T>::getElementAt(int index) {
    if (index < 0 || index >= numElements) throw std::out_of_range("Indice fuera de rango");
    NodeDLL<T>* p = head;
    for (int i = 0; i < index; i++) p = p->next;
    return p->data;
}

/*
 Descripcion: Inicia el algoritmo MergeSort
 Parametros: Ninguno
 Retorno: void
 Complejidad: O(n log n)
 */
template <class T>
void DoublyLinkedList<T>::sortMerge() {
    if (head == nullptr || head->next == nullptr) return;
    head = mergeSortRecursive(head);
    
    // Actualizar tail
    NodeDLL<T>* curr = head;
    while (curr->next != nullptr) curr = curr->next;
    tail = curr;
}

/*
Descripcion: Divide la lista en dos mitades osea la particion
 Parametros: source que viene siendo el nodo inicio
 Retorno: NodeDLL* que es el puntero al inicio de la segunda mitad
 Complejidad: O(n)
 */
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::split(NodeDLL<T>* source) {
    NodeDLL<T>* fast = source;
    NodeDLL<T>* slow = source;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    NodeDLL<T>* temp = slow->next;
    slow->next = nullptr;
    if (temp != nullptr) temp->prev = nullptr;
    return temp;
}

/*
Descripcion: Mezcla dos sublistas ordenadas
Parametros: first, second - cabezas de las sublistas
Retorno: NodeDLL* - cabeza de la lista mezclada
Complejidad: O(n)
 */
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::merge(NodeDLL<T>* first, NodeDLL<T>* second) {
    if (!first) return second;
    if (!second) return first;

    if (first->data <= second->data) {
        first->next = merge(first->next, second);
        if (first->next) first->next->prev = first;
        first->prev = nullptr;
        return first;
    } else {
        second->next = merge(first, second->next);
        if (second->next) second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

/*
Descripcion: Funcion recursiva de MergeSort
Parametros: node
Retorno: NodeDLL*
Complejidad: O(n log n)
 */
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::mergeSortRecursive(NodeDLL<T>* node) {
    if (!node || !node->next) return node;
    NodeDLL<T>* second = split(node);
    node = mergeSortRecursive(node);
    second = mergeSortRecursive(second);
    return merge(node, second);
}

//Quicksort

/*
Descripcion: Inicia QuickSort
Parametros: Ninguno
Retorno: void
Complejidad: O(n log n) promedio y O(n^2) en el peor caso
 */
template <class T>
void DoublyLinkedList<T>::sortQuick() {
    NodeDLL<T>* h = tail;
    quickSortRecursive(head, h);
}

/*
Descripcion: Intercambia los datos de dos nodos
Parametros: "a" y "b"
Retorno: void
Complejidad: O(1)
 */
template <class T>
void DoublyLinkedList<T>::swapData(NodeDLL<T>* a, NodeDLL<T>* b) {
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/*
Descripcion: Particiona la lista usando el ultimo elemento como pivote
Parametros: l (low), h (high) - rango de particion
Retorno: NodeDLL* - nodo pivote en su posicion correcta
Complejidad: O(n)
 */
template <class T>
NodeDLL<T>* DoublyLinkedList<T>::partition(NodeDLL<T>* l, NodeDLL<T>* h) {
    T x = h->data;
    NodeDLL<T>* i = l->prev;

    for (NodeDLL<T>* j = l; j != h; j = j->next) {
        if (j->data <= x) {
            i = (i == nullptr) ? l : i->next;
            swapData(i, j);
        }
    }
    i = (i == nullptr) ? l : i->next;
    swapData(i, h);
    return i;
}

/*
Descripcion: Funcion recursiva de QuickSort
Parametros: l, h - rango actual
Retorno: void
Complejidad: O(n log n)
 */
template <class T>
void DoublyLinkedList<T>::quickSortRecursive(NodeDLL<T>* l, NodeDLL<T>* h) {
    if (h != nullptr && l != h && l != h->next) {
        NodeDLL<T>* p = partition(l, h);
        if (p != nullptr && p->prev != nullptr)
            quickSortRecursive(l, p->prev);
        if (p != nullptr && p->next != nullptr)
            quickSortRecursive(p->next, h);
    }
}

/*
Descripcion: Busqueda binaria para la primera fecha
Parametros: value que viene siendo el valor a buscar
Retorno: int
Complejidad: O(n log n)
 */
template <class T>
int DoublyLinkedList<T>::binarySearchFirst(T value) {
    int l = 0;
    int r = numElements - 1;
    int result = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        T midVal = getElementAt(m); // Costo O(n)

        if (midVal >= value) {
            result = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return result;
}

/*
 Descripcion: Busqueda binaria (Upper Bound aproximado)
 Parametros: value
 Retorno: int
Complejidad: O(n log n)
 */
template <class T>
int DoublyLinkedList<T>::binarySearchLast(T value) {
    int l = 0;
    int r = numElements - 1;
    int result = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        T midVal = getElementAt(m);

        if (midVal <= value) {
            result = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return result;
}

#endif // _DOUBLYLINKEDLIST_H_