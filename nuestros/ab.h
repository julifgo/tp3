#ifndef AB_H
#define AB_H

#include <iostream>
#include "../aed2.h"

using namespace aed2;

namespace dcnet {

template<typename T>
class Ab {
 private:
    struct nodo {
        T valor;
        Ab<T>* _izq;
        Ab<T>* _der;

        nodo(Ab<T>* i, T v, Ab<T>* d) :
            valor(v), _izq(i), _der(d) {}

        nodo(const nodo& otro) :
            valor(otro.valor) {
            _izq = otro._izq == NULL ? NULL : new Ab<T>(*(otro._izq));
            _der = otro._der == NULL ? NULL : new Ab<T>(*(otro._der));
        }
        
        ~nodo() {
            delete _izq;
            delete _der;
        }
    };
    Nat _cardinal;
    nodo* _raiz;

 public:
    Ab();                          // Construye un árbol vacío
    Ab(const Ab<T>&);              // Construye un árbol por copia
    Ab(Ab<T>*, const T&, Ab<T>*);  // Construye un árbol a partir de su raíz
                                      // y subárboles izquierdo y derecho
    ~Ab();                         // Destruye un árbol

    Ab<T>& operator=(const Ab<T>&);  // Operador de asignación por copia

    bool isNil() const;          // Devuelve True si y solo si el árbol
                                    // no contiene nodos
    T& raiz() const;             // Devuelve el valor de la raíz del árbol
   /* Ab<T>* izq() const;          // Devuelve el subárbol izquierdo
    Ab<T>* der() const;     */     // Devuelve el subárbol derecho
    Ab<T>* izq();                // Devuelve el subárbol izquierdo
    Ab<T>* der();   	           // Devuelve el subárbol derecho
    //void izq(Ab<T>*);            // Reemplaza el subárbol izquierdo
                                    // (NO libera memoria)
   // void der(Ab<T>*);            // Reemplaza el subárbol derecho
                                    // (NO libera memoria)
    Nat Tamano() const;       // Devuelve la cantidad de nodos del árbol
};

// Implementación de métodos públicos

template<class T>
Ab<T>::Ab() : _raiz(NULL), _cardinal(0) {
}

template<class T>
Ab<T>::Ab(const Ab<T>& otro) {
    _raiz = otro._raiz == NULL ? NULL : new nodo(*(otro._raiz));
    _cardinal = otro._cardinal;
}

template<class T>
Ab<T>::Ab(Ab<T>* i, const T& r, Ab<T>* d) {
    _raiz = new nodo(i, r, d);
    Nat cardinalIzq = i==NULL?0:i->_cardinal;
    Nat cardinalDer = d==NULL?0:d->_cardinal;
    _cardinal = cardinalIzq + cardinalDer + 1;
}

template<class T>
Ab<T>::~Ab() {
    delete _raiz;
}

template<class T>
Ab<T>& Ab<T>::operator=(const Ab<T>& otro) {
    delete _raiz;
    _raiz = otro._raiz == NULL ? NULL : new nodo(*(otro._raiz));
    _cardinal = otro._cardinal;
    return *this;
}

template<class T>
bool Ab<T>::isNil() const {
    return _raiz == NULL;
}

template<class T>
T& Ab<T>::raiz() const {
    assert(!isNil());
    return _raiz->valor;
}

/*template<class T>
Ab<T>* Ab<T>::izq() const {
    assert(!esNil());
    return _raiz->_izq;
}

template<class T>
Ab<T>* Ab<T>::der() const {
    assert(!esNil());
    return _raiz->_der;
}*/

template<class T>
Ab<T>* Ab<T>::izq() {
    assert(!isNil());
    return _raiz->_izq;
}

template<class T>
Ab<T>* Ab<T>::der() {
    assert(!isNil());
    return _raiz->_der;
}

/*template<class T>
void Ab<T>::izq(Ab<T>* i) {
    assert(!esNil());
    // delete _raiz->_izq;
    _raiz->_izq = i;
}

template<class T>
void Ab<T>::der(Ab<T>* d) {
    assert(!esNil());
    // delete _raiz->_der;
    _raiz->_der = d;
}*/

template<class T>
Nat Ab<T>::Tamano() const {
return _cardinal;
}

}

#endif  // AB_H
