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
            Ab<T>() : raiz(NULL) {}
            

            //bin (el const que precede puede limitar operaciones: reconsiderar)

            Ab<T>(const Ab<T>& i, const T& e, const Ab<T>& d) {
            	Nodo* n = new Nodo; //creo un nuevo nodo en el arbol
            	n->valor = e; //el valor es la referencia pasada
            	n->izq = i.raiz; //el puntero es igual al puntero raiz de la referencia i
                n->der = d.raiz; //el puntero es igual al puntero raiz de la referencia d
                
                Nat cardinalIzq = i.raiz==NULL?0:i.raiz->cardinal;
                Nat cardinalDer = d.raiz==NULL?0:d.raiz->cardinal;
                n->cardinal = cardinalIzq + cardinalDer + 1;

                this->raiz = n; //el puntero es igual al puntero de n
                //this->cardinal = i.Tamano() + d.Tamano() + 1; //actualizo el tamaño
            }
            
            //destructor
            ~Ab<T>() {
                //cout<<"ent dest"<<endl;
                delete this->raiz; //este destructor destruye el contenido de toda las referencias hijas (recursivo)
                //cout<<"leaving dest"<<endl;
                }

            //tamaño
            Nat Tamano() const {
                return  this->raiz == NULL ? 0 : this->raiz->cardinal;
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
            Ab Izq() {
                //return this->raiz->izq;
                return Ab<T>(*this->raiz->izq);
            }

            //der (el const que precede puede limitar operaciones: reconsiderar)
            const Ab& Der() const {
                return Ab<T>(*this->raiz->der);
            }

             Ab<T>& operator = (const Ab<T>& otro)
            {
                //delete this->raiz;
                cout<<"Entering to equal operator"<<endl;
                //Nodo* n = new Nodo;


             /* this->raiz = otro.raiz;
              cout<<"After raiz"<<endl;
              this->cardinal = otro.cardinal;
              cout<<"After cardinal"<<endl;*/
              return *this;
            }

        private:

            struct Nodo {
                T valor;
                Nodo* izq;
                Nodo* der;
                Nat cardinal;
                ~Nodo() {
                    delete izq;
                    delete der;
               //   delete valor;
                }
            };

            Nodo* raiz;
            //Nat cardinal;     
            Ab<T>(Nodo n) { //TODO. VER QUE PASA SI n == NULL
                Nodo* n2 = new Nodo;
                n2->valor=n.valor;
                n2->izq = n.izq;
                n2->der = n.der;
                n2->cardinal = n.cardinal;
                cout<<"new constructor"<<endl;
                this->raiz = n2;
                //this->cardinal = 15;
            }
    };

}
#endif //AB_H
