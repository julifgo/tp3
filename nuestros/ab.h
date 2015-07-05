#ifndef AB_H
#define AB_H

#include "../aed2.h"

namespace dcnet {

    //NOTA este Ab va a tener que sufrir cambios a medida que avancemos

    template<typename T>
    class Ab {
        
        public:

            //Miembros definidos en el módulo

            //nil
            Ab<T>() : raiz(NULL), cardinal(0) {}

            //bin (el const que precede puede limitar operaciones: reconsiderar)
            Ab<T>(const Ab<T>& i, const T& e, const Ab<T>& d) {
                Nodo* n = new Nodo; //creo un nuevo nodo en el heap
                n->valor = &e; //el puntero apunta a la referencia e pasada
                n->izq = i.raiz; //el puntero es igual al puntero raiz de la referencia i
                n->der = d.raiz; //el puntero es igual al puntero raiz de la referencia d
                this->raiz = n; //el puntero es igual al puntero de n
                this->cardinal = i.Tamano() + d.Tamano() + 1; //actualizo el tamaño
            }
            
            //destructor
            ~Ab<T>() {
                delete this->raiz; //este destructor destruye el contenido de toda las referencias hijas (recursivo)
            }

            //tamaño
            Nat Tamano() const {
                return this->cardinal;
            }

            //nil?
            bool IsNil() const {
                return this->raiz == NULL;
            }

            //raiz
            T& Raiz() const {
                return this->raiz->valor;
            }

            //izq (el const que precede puede limitar operaciones: reconsiderar)
            const Ab& Izq() const {
                return this->raiz->izq;
            }

            //der (el const que precede puede limitar operaciones: reconsiderar)
            const Ab& Der() const {
                return this->raiz->der;
            }

        private:

            struct Nodo {
                //dejo const el valor que se guarda, si molesta avisar para sacar después
                const T* valor;
                Nodo* izq;
                Nodo* der;

                ~Nodo() {
                    delete izq;
                    delete der;
                    delete valor;
                }
            };

            Nodo* raiz;
            Nat cardinal;     

    };

}
#endif //AB_H
