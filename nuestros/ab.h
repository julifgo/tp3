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
    Nodo* _raiz;
    Nat _cardinal;

 public:
    Ab();
    Ab(const Ab<T>&);
    Ab(Ab<T>*, const T&, Ab<T>*);

    ~Ab();

    Ab<T>& operator=(const Ab<T>&);

    bool IsNil() const;

    T& Raiz() const;
    Ab<T>* Izq();
    Ab<T>* Der();
    void Izq(Ab<T>*);
    void Der(Ab<T>*);

    Nat Tamano() const;
};

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
    Nat cardinalIzq = i->_raiz==NULL?0:i->_cardinal;
    Nat cardinalDer = d->_raiz==NULL?0:d->_cardinal;
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
  //  delete _raiz->_izq;
     _raiz->_izq = i;
     Nat cardinalIzq = i->_raiz==NULL?0:i->_cardinal;
     Nat cardinalDer = _raiz->_der->_cardinal;
     _cardinal = cardinalIzq + cardinalDer + 1;
}

template<typename T>
void Ab<T>::Der(Ab<T>* d) {
    assert(!IsNil());
   // delete _raiz->_der;
    _raiz->_der = d;
    Nat cardinalIzq = _raiz->_izq->_cardinal;
    Nat cardinalDer = d->_raiz==NULL?0:d->_cardinal;
    _cardinal = cardinalIzq + cardinalDer + 1;
}

template<typename T>
Nat Ab<T>::Tamano() const {
return _cardinal;
}

}

#endif  // AB_H
