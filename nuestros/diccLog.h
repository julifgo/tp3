#ifndef DICCLOG_H
#define DICCLOG_H

#include "../aed2.h"
#include "ab.h"

namespace dcnet {

	template<typename K,typename S>
    class DiccLog {
        
        public:
    	DiccLog<K,S>(){
            diccLog = new Ab<Nodo>(); //TODO. try equal this to NULL
        }//Equivalente a Vacio()                    
        ~DiccLog<K,S>(){                            
            cout<<"destructor"<<endl;               
            delete this->diccLog;                   
        }                                           
                                                    
        bool IsDefinido(const K& p) const;          
                                                    
        void Definir(const K& p, const S& s){       
            if(diccLog->isNil()){                   
                delete diccLog;//TODO. OJO CON ESTA LINEA! Esta asi porque si estoy parado, vengo de haber sido construido sin parametros
                Nodo *nodo = new Nodo;
                nodo->clave = p;
                nodo->significado = s;
                nodo->altura =1;
                diccLog = new Ab<Nodo>(NULL,*nodo,NULL);
                delete nodo;
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

        struct Nodo{
        	K clave;
        	S significado;
        	Nat altura;
                ~Nodo(){
                    cout<<"No deberia haber entrada aca"<<endl;
                }
        };

        Ab<Nodo> *diccLog;
            

    };
}
#endif