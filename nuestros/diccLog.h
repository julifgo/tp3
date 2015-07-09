#ifndef DICCLOG_H
#define DICCLOG_H

#include "../aed2.h"
#include "ab.h"

namespace dcnet {

	template<typename K,typename S>
    class DiccLog {
        
        public:
    	DiccLog<K,S>(){
            _diccLog = new Ab<Nodo>(); //TODO. try equal this to NULL
        }//Equivalente a Vacio()                    
        ~DiccLog<K,S>(){                            
            cout<<"destructor"<<endl;               
            delete this->_diccLog;
        }                                           
                                                    
        bool IsDefinido(const K& p) const;          
                                                    
        void Definir(const K& p, const S& s){
        	if(_diccLog->IsNil())
        		_diccLog = NULL;//TODO. OJO CON ESTA LINEA! Esta asi porque si estoy parado, vengo de haber sido construido sin parametros

        	DefinirPrivate(_diccLog,p,s);
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
             cout<<"No deberia haber entrada aca"<<endl;//@JULIAN:ME PARECE QUE SI DEBERIA
             }
        };
        Ab<Nodo>* RotarIzquierda(Ab<Nodo>* diccLog){
      		Ab<Nodo>* aux1 = diccLog->Der();
        	Ab<Nodo>* aux2 = aux1->Izq();
        	aux1->Izq(diccLog);
        	diccLog->Der(aux2);
        	diccLog->Raiz().altura = 1 + (diccLog->Izq()->Raiz().altura > diccLog->Izq()->Raiz().altura)?diccLog->Izq()->Raiz().altura:diccLog->Der()->Raiz().altura;
        	aux1->Raiz().altura = 1 + (aux1->Izq()->Raiz().altura > aux1->Izq()->Raiz().altura)?aux1->Izq()->Raiz().altura:aux1->Der()->Raiz().altura;
        	return aux1;
        };
        Ab<Nodo>* RotarDerecha(Ab<Nodo>* diccLog){
        	Ab<Nodo>* aux1 = diccLog->Izq();
        	Ab<Nodo>* aux2 = aux1->Der();
        	aux1->Der(diccLog);
        	diccLog->Izq(aux2);
        	diccLog->Raiz().altura = 1 + (diccLog->Izq()->Raiz().altura > diccLog->Izq()->Raiz().altura)?diccLog->Izq()->Raiz().altura:diccLog->Der()->Raiz().altura;
        	aux1->Raiz().altura = 1 + (aux1->Izq()->Raiz().altura > aux1->Izq()->Raiz().altura)?aux1->Izq()->Raiz().altura:aux1->Der()->Raiz().altura;
        	return aux1;
        };
        int FactorDeBalanceo();

        void DefinirPrivate(Ab<Nodo> *diccLog,const K& p, const S& s){
        	if(diccLog==NULL){
        		Nodo nodo;
				nodo.clave = p;
				nodo.significado = s;
				nodo.altura = 1;
				diccLog = new Ab<Nodo>(NULL,nodo,NULL);
				if(_diccLog==NULL)
					_diccLog = diccLog;
			}
			else{
				Nodo raiz = diccLog->Raiz();
				if(p<raiz.clave){
					DefinirPrivate(diccLog->Izq(),p,s);
				}else{
					DefinirPrivate(diccLog->Der(),p,s);
				}
				raiz.altura = 1 + (diccLog->Izq()->Raiz().altura > diccLog->Izq()->Raiz().altura)?diccLog->Izq()->Raiz().altura:diccLog->Der()->Raiz().altura;
				int fdb = FactorDeBalanceo();
				if(fdb>1 && p<diccLog->Izq()->Raiz().clave)
					RotarDerecha(diccLog);
				if(fdb<-1 && p>diccLog->Der()->Raiz().clave)
					RotarIzquierda(diccLog);
				if(fdb>1 && p>diccLog->Izq()->Raiz().clave){
					RotarIzquierda(diccLog->Izq());
					RotarDerecha(diccLog);
				}
				if(fdb<-1 && p<diccLog->Der()->Raiz().clave){
					RotarDerecha(diccLog->Der());
					RotarIzquierda(diccLog);
				}

				cout<<"No Soy nil"<<endl;
			}

        }



        Ab<Nodo> *_diccLog;
            

    };

	template<typename K,typename S>
	int DiccLog<K,S>::FactorDeBalanceo(){
		if(_diccLog->IsNil()){
			return 0;
		}else{
			int alturaIzq =0;
			int alturaDer =0;
			if(!_diccLog->Izq()->IsNil()){
				alturaIzq = _diccLog->Izq()->Raiz().altura;
			}
			if(!_diccLog->Der()->IsNil()){
				alturaDer = _diccLog->Izq()->Raiz().altura;
			}
			return alturaIzq - alturaDer;
		}
	}

}



#endif


