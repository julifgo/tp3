#ifndef AB_H
#define AB_H

#include <iostream>
#include "../aed2.h"

using namespace aed2;

namespace dcnet {

template<typename T>
class Ab {
 private:
    struct Nodo {
        T valor;
        Ab<T>* _izq;
        Ab<T>* _der;

        Nodo(Ab<T>* i, T v, Ab<T>* d) :
            valor(v), _izq(i), _der(d) {}

        Nodo(const Nodo& otro) :
            valor(otro.valor) {
            _izq = otro._izq == NULL ? NULL : new Ab<T>(*(otro._izq));
            _der = otro._der == NULL ? NULL : new Ab<T>(*(otro._der));
        }
        
        ~Nodo() {
            delete _izq;
            delete _der;
        }
    };
    Nat _cardinal;
    Nodo* _raiz;

 public:
    Ab();                          // Construye un árbol vacío
    Ab(const Ab<T>&);              // Construye un árbol por copia
    Ab(Ab<T>*, const T&, Ab<T>*);  // Construye un árbol a partir de su raíz
                                      // y subárboles izquierdo y derecho
    ~Ab();                         // Destruye un árbol

    Ab<T>& operator=(const Ab<T>&);  // Operador de asignación por copia

    bool IsNil() const;          // Devuelve True si y solo si el árbol
                                    // no contiene nodos
    T& Raiz() const;             // Devuelve el valor de la raíz del árbol
   /* Ab<T>* Izq() const;          // Devuelve el subárbol izquierdo
    Ab<T>* Der() const;     */     // Devuelve el subárbol derecho
    Ab<T>* Izq();                // Devuelve el subárbol izquierdo
    Ab<T>* Der();   	           // Devuelve el subárbol derecho
    void Izq(Ab<T>*);            // Reemplaza el subárbol izquierdo
                                    // (NO libera memoria)
    void Der(Ab<T>*);            // Reemplaza el subárbol derecho
                                    // (NO libera memoria)
    Nat Tamano() const;       // Devuelve la cantidad de nodos del árbol
};

// Implementación de métodos públicos

template<typename T>
Ab<T>::Ab() : _raiz(NULL), _cardinal(0) {
}

template<typename T>
Ab<T>::Ab(const Ab<T>& otro) {
    _raiz = otro._raiz == NULL ? NULL : new Nodo(*(otro._raiz));
    _cardinal = otro._cardinal;
}

template<typename T>
Ab<T>::Ab(Ab<T>* i, const T& r, Ab<T>* d) {
    _raiz = new Nodo(i, r, d);
    Nat cardinalIzq = i==NULL?0:i->_cardinal;
    Nat cardinalDer = d==NULL?0:d->_cardinal;
    _cardinal = cardinalIzq + cardinalDer + 1;
}

template<typename T>
Ab<T>::~Ab() {
    delete _raiz;
}

template<typename T>
Ab<T>& Ab<T>::operator=(const Ab<T>& otro) {
    delete _raiz;
    _raiz = otro._raiz == NULL ? NULL : new Nodo(*(otro._raiz));
    _cardinal = otro._cardinal;
    return *this;
}

template<typename T>
bool Ab<T>::IsNil() const {
    return _raiz == NULL;
}

template<typename T>
T& Ab<T>::Raiz() const {
    assert(!IsNil());
    return _raiz->valor;
}

/*template<typename T>
Ab<T>* Ab<T>::Izq() const {
    assert(!esNil());
    return _raiz->_izq;
}

template<typename T>
Ab<T>* Ab<T>::Der() const {
    assert(!esNil());
    return _raiz->_der;
}*/

template<typename T>
Ab<T>* Ab<T>::Izq() {
    assert(!IsNil());
    return _raiz->_izq;
}

template<typename T>
Ab<T>* Ab<T>::Der() {
    assert(!IsNil());
    return _raiz->_der;
}

template<typename T>
void Ab<T>::Izq(Ab<T>* i) {
    assert(!IsNil());
    // delete _raiz->_izq;
    _raiz->_izq = i;
}

template<typename T>
void Ab<T>::Der(Ab<T>* d) {
    assert(!IsNil());
    // delete _raiz->_der;
    _raiz->_der = d;
}

template<typename T>
Nat Ab<T>::Tamano() const {
return _cardinal;
}

}

#endif  // AB_H
