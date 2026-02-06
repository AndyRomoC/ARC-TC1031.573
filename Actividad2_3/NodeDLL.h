//Clase Nodo para lista doblemente ligada

#ifndef _NODEDLL_H_
#define _NODEDLL_H_

template <class T>
class NodeDLL {
private:
    T data;
    NodeDLL<T>* next;
    NodeDLL<T>* prev;

public:
    NodeDLL(T value);

    // Friend class para que DoublyLinkedList acceda a privados
    template<typename U> friend class DoublyLinkedList;
};

//Constructor del nodo
//Parametros: "value" va almacenar un valor de tipo T
//Retorno: N/A
//Complejidad: O(1)

template <class T>
NodeDLL<T>::NodeDLL(T value) : data{value}, next{nullptr}, prev{nullptr} {}

#endif // _NODEDLL_H_