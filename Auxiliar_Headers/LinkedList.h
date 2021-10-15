#ifndef INFOII_LINKEDLIST_H
#define INFOII_LINKEDLIST_H


#include "Node.h"

template<typename T>
class LinkedList {
private:
    Node<T> *head;
    int size;
public:
    LinkedList();

    void insert(unsigned int pos, T data);

    T get(unsigned int pos);

    void remove(unsigned int pos);

    T find(T data);

    void push_front(T data) {
        insert(0, data);
    }

    void push_back(T data) {
        insert(size, data);
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

private:
    Node<T> *getNode(unsigned int pos);
};


template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}

template<typename T>
void LinkedList<T>::insert(unsigned int pos, T data) {
    Node<T> *aux, *newNode;

    if (pos == 0) {
        newNode = new Node<T>(data, head);
        head = newNode;
        size++;
        return;
    }

    aux = getNode(pos - 1);
    newNode = new Node<T>(data, aux->getNext());
    size++;
    aux->setNext(newNode);
}


template<typename T>
T LinkedList<T>::get(unsigned int pos) {
    Node<T> *aux = getNode(pos);
    return aux->getData();
}

template<typename T>
Node<T> *LinkedList<T>::getNode(unsigned int pos) {
    Node<T> *aux = head;

    if (pos >= size)
        throw 404;

    while (pos > 0) {
        aux = aux->getNext();
        pos--;
    }
    return aux;
}

template<typename T>
T LinkedList<T>::find(T data) {
    Node<T> *aux = head;

    while (aux != nullptr && aux->getData() != data) {
        aux = aux->getNext();
    }
    if (aux == nullptr)
        throw 404;

    return aux->getData();
}

template<typename T>
void LinkedList<T>::remove(unsigned int pos) {
    Node<T> *aux;
    Node<T> *toDelete;

    if (pos >= size)
        throw 404;

    if (pos == 0) {
        toDelete = head;
        head = head->getNext();
    } else {
        aux = getNode(pos - 1);
        toDelete = aux->getNext();
        aux->setNext(aux->getNext()->getNext());
    }
    delete toDelete;
    size--;
}


#endif //INFOII_LINKEDLIST_H