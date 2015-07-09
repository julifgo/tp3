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
            if(diccLog->IsNil()){
                delete diccLog;//TODO. OJO CON ESTA LINEA! Esta asi porque si estoy parado, vengo de haber sido construido sin parametros
                Nodo *nodo = new Nodo;
                nodo->clave = p;
                nodo->significado = s;
                nodo->altura = 1;
                diccLog = new Ab<Nodo>(NULL,*nodo,NULL);
                delete nodo;
            }
            else{
            	Nodo raiz = diccLog->Raiz();
            	if(p<raiz.clave){
            		diccLog->Izq()->Definir(p,s);
            	}else{
            		diccLog->Der()->Definir(p,s);
            	}
            	raiz.altura = 1 + (diccLog->Izq()->Raiz().altura > diccLog->Izq()->Raiz().altura)?diccLog->Izq()->Raiz().altura:diccLog->Der()->Raiz().altura;
            	int fdb = FactorDeBalanceo();
            	if(fdb>1 && p<diccLog->Izq()->Raiz().clave)
            		RotarDerecha();
            	if(fdb<-1 && p>diccLog->Der()->Raiz().clave)
            	    RotarIzquierda();
            	if(fdb>1 && p>diccLog->Izq()->Raiz().clave){
            		diccLog->Izq()->RotarIzquierda();
            		RotarDerecha();
            	}
            	if(fdb<-1 && p<diccLog->Der()->Raiz().clave){
            		diccLog->Der()->RotarDerecha();
            	    RotarIzquierda();
            	}

            	cout<<"No Soy nil"<<endl;
            }
                
        }

        S& Significado(const K& clave) const;
        void Borrar(const K& clave);
        DiccLog<K,S> Minimo() const;
        S& MinimoSignificado() const;
        Nat CantClaves() const;

        private:
        struct Nodo{
             K clave;
             S significado;
             Nat altura;
             ~Nodo(){
             cout<<"No deberia haber entrada aca"<<endl;
             }
        };
        Ab<Nodo>* RotarIzquierda(){
      		Ab<Nodo>* aux1 = diccLog->der();
        	Ab<Nodo>* aux2 = aux1->izq();
        	aux1->izq() = diccLog;
        	diccLog->der() = aux2;
        	diccLog->Raiz().altura = 1 + (diccLog->izq()->Raiz().altura > diccLog->izq()->Raiz().altura)?diccLog->izq()->Raiz().altura:diccLog->der()->Raiz().altura;
        	aux1->Raiz().altura = 1 + (aux1->izq()->Raiz().altura > aux1->izq()->Raiz().altura)?aux1->izq()->Raiz().altura:aux1->der()->Raiz().altura;
        	return aux1;
        };
        Ab<Nodo>* RotarDerecha(){
        	Ab<Nodo>* aux1 = diccLog->izq();
        	Ab<Nodo>* aux2 = aux1->der();
        	aux1->der() = diccLog;
        	diccLog->izq() = aux2;
        	diccLog->Raiz().altura = 1 + (diccLog->izq()->Raiz().altura > diccLog->izq()->Raiz().altura)?diccLog->izq()->Raiz().altura:diccLog->der()->Raiz().altura;
        	aux1->Raiz().altura = 1 + (aux1->izq()->Raiz().altura > aux1->izq()->Raiz().altura)?aux1->izq()->Raiz().altura:aux1->der()->Raiz().altura;
        	return aux1;
        };
        int FactorDeBalanceo();



        Ab<Nodo> *diccLog;
            

    };

	template<typename K,typename S>
	int DiccLog<K,S>::FactorDeBalanceo(){
		if(diccLog->IsNil()){
			return 0;
		}else{
			int alturaIzq =0;
			int alturaDer =0;
			if(!diccLog->izq()->IsNil()){
				alturaIzq = diccLog->izq()->Raiz().altura;
			}
			if(!diccLog->Der()->IsNil()){
				alturaDer = diccLog->Izq()->Raiz().altura;
			}
			return alturaIzq - alturaDer;
		}
	}

}



#endif


