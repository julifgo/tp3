#ifndef DICCLOG_H
#define DICCLOG_H

#include "../aed2.h"
#include "ab.h"

namespace dcnet {

	template<typename K,typename S>
    class DiccLog {
        
        public:
    	DiccLog<K,S>():diccLog(Ab<Nodo2>()){}//Equivalente a Vacio()

        ~DiccLog<K,S>(){
            cout<<"destructor"<<endl;
        } //TODO!

        bool IsDefinido(const K& p) const;

        void Definir(const K& p, const S& s){
            if(diccLog.IsNil()){
                cout<<"Entering Nodo Init"<<endl;
                Nodo2 nodo;
                nodo.clave = p;
                nodo.significado = s;
                nodo.altura =1;
                cout<<"done nodo init"<<endl;
                diccLog = Ab<Nodo2>(Ab<Nodo2>(),nodo,Ab<Nodo2>());
                cout<<"done bin()"<<endl;
            }
            else{
                cout<<"No Soy nil"<<endl;   
            }
        }

        S& Significado(const K& clave) const;
        void Borrar(const K& clave);
        DiccLog<K,S> Minimo() const;
        S& MinimoSignificado() const;
        Nat CantClaves() const;

        private:
        DiccLog<K,S> RotarIzquierda(DiccLog<K,S> d); //d es subarbol de DiccLog
        DiccLog<K,S> RotarDerecha(DiccLog<K,S> d); //d es subarbol de DiccLog
        int FactorDeBalanceo(const DiccLog<K,S> d); //d es subarbol de DiccLog

        struct Nodo2{
        	K clave;
        	S significado;
        	Nat altura;
        };

        Ab<Nodo2> diccLog;
            

    };
}
#endif