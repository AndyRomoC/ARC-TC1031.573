#ifndef _NODEHASHTABLE_H_
#define _NODEHASHTABLE_H_

#include <vector>
#include <algorithm>

template <class K, class T>
class NodeHashTable {
private:
    K key;
    T data;
    int status; // 0 empty, 1 used, 2 deleted
    std::vector<int> overflow;

public:
    NodeHashTable();
    ~NodeHashTable();

    K getKey();
    T getData();
    int getStatus();

    void setKey(K keyValue);
    void setData(T dataValue);

    void clearData();

    void addToOverflow(int hashIndex);
    int getOverflowSize();
    int getOverflowAt(int index);
    void removeFromOverflow(int index);
};

template<class K, class T>
NodeHashTable<K,T>::NodeHashTable() {
    key = K();   // FIX genérico
    data = T();
    status = 0;
    overflow.clear();
}

template<class K, class T>
NodeHashTable<K,T>::~NodeHashTable() {
    overflow.clear();
}

template<class K, class T>
K NodeHashTable<K,T>::getKey() {
    return key;
}

template<class K, class T>
T NodeHashTable<K,T>::getData() {
    return data;
}

template<class K, class T>
int NodeHashTable<K,T>::getStatus() {
    return status;
}

template<class K, class T>
void NodeHashTable<K,T>::setKey(K keyValue) {
    key = keyValue;
}

template<class K, class T>
void NodeHashTable<K,T>::setData(T dataValue) {
    data = dataValue;
    status = 1;
}

template<class K, class T>
void NodeHashTable<K,T>::clearData() {
    data = T();
    status = 2;
}

template<class K, class T>
void NodeHashTable<K,T>::addToOverflow(int hashIndex) {
    overflow.push_back(hashIndex);
}

template<class K, class T>
int NodeHashTable<K,T>::getOverflowSize() {
    return overflow.size();
}

template<class K, class T>
int NodeHashTable<K,T>::getOverflowAt(int index) {
    return overflow[index];
}

template<class K, class T>
void NodeHashTable<K,T>::removeFromOverflow(int index) {
    auto it = std::find(overflow.begin(), overflow.end(), index);
    if (it != overflow.end())
        overflow.erase(it);
}

#endif
