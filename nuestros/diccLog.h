#ifndef DICCLOG_H
#define DICCLOG_H
#include <cassert>
#include "../aed2.h"
#include "ab.h"

namespace dcnet {

	template<typename K,typename S>
    class DiccLog {
    private:
           struct Nodo{
                K clave;
                S significado;
                Nat altura;
                ~Nodo(){
                }
           };

           Ab<Nodo> *_diccLog;

           Ab<Nodo>* Minimo(Ab<Nodo> *diccLog) const{
				while(!diccLog->Izq()->IsNil()){
					diccLog = diccLog->Izq();
				}
				return diccLog;
           }
           Ab<Nodo>* RotarIzquierda(Ab<Nodo>* diccLog){
         		assert(!diccLog->Der()->IsNil());
        	   	Ab<Nodo>* aux1 = diccLog->Der();
        	   	diccLog->Der(aux1->Izq());
        		aux1->Izq(diccLog);
         		aux1->Izq()->Raiz().altura =1 + max(Altura(aux1->Izq()->Izq()),Altura(aux1->Izq()->Der()));
         		aux1->Raiz().altura = 1 + max(Altura(aux1->Izq()),Altura(aux1->Der()));
           		return aux1;
           };
           Ab<Nodo>* RotarDerecha(Ab<Nodo>* diccLog){
        	   assert(!diccLog->Izq()->IsNil());
        	   Ab<Nodo>* aux1 = diccLog->Izq();
        	   diccLog->Izq(aux1->Der());
        	   aux1->Der(diccLog);
        	   aux1->Der()->Raiz().altura = 1 + max(Altura(aux1->Der()->Izq()),Altura(aux1->Der()->Der()));
        	   aux1->Raiz().altura = 1 + max(Altura(aux1->Izq()),Altura(aux1->Der()));
        	   return aux1;
           };
           int FactorDeBalanceo(Ab<Nodo> *diccLog);

           int Altura(Ab<Nodo> *diccLog){
               if (diccLog->IsNil())
                   return 0;
               return diccLog->Raiz().altura;
           }

           int Max(int a, int b){
               return (a > b)? a : b;
           }

           Ab<Nodo>* BorrarPrivate(Ab<Nodo>** diccLog,const K& clave){
        	   if(!(*diccLog)->IsNil()){
        		   if(clave < (*diccLog)->Raiz().clave){
        			   Ab<Nodo>* nodoIzq = (*diccLog)->Izq();
        			   (*diccLog)->Izq(BorrarPrivate(&nodoIzq,clave));
        		   }else if(clave > (*diccLog)->Raiz().clave){
        				Ab<Nodo>* nodoDer = (*diccLog)->Der();
        			   	(*diccLog)->Der(BorrarPrivate(&nodoDer,clave));
        		   }else{
        			   if((*diccLog)->Izq()->IsNil() || (*diccLog)->Der()->IsNil()){
        				   Ab<Nodo>* temp = (!(*diccLog)->Izq()->IsNil())?(*diccLog)->Izq():(*diccLog)->Der();
        				   if(temp->IsNil()){
        					   temp = (*diccLog);
        					   (*diccLog) = new Ab<Nodo>();
        				   }else{
        					   (!(*diccLog)->Izq()->IsNil())?(*diccLog)->Izq(new Ab<Nodo>):(*diccLog)->Der(new Ab<Nodo>);
        					   (*diccLog)->Raiz().clave=temp->Raiz().clave;
        					   (*diccLog)->Raiz().significado=temp->Raiz().significado;
        				   }
        				   delete temp;
        			   }
        			   else{
        				   Ab<Nodo>* temp = Minimo((*diccLog)->Der());
        				   Ab<Nodo>* nodoDer = (*diccLog)->Der();
        				   (*diccLog)->Raiz().clave=temp->Raiz().clave;
        				   (*diccLog)->Raiz().significado=temp->Raiz().significado;
        				   (*diccLog)->Der(BorrarPrivate(&nodoDer,temp->Raiz().clave));
        			   }
        		   }
        		   if((*diccLog)->Tamano()>0){
        			   (*diccLog)->Raiz().altura = 1 + max(Altura((*diccLog)->Izq()),Altura((*diccLog)->Der()));
        			   int fdb = FactorDeBalanceo((*diccLog));
        			   if(fdb > 1 && FactorDeBalanceo((*diccLog)->Izq())>=0){
        				   (*diccLog) = RotarDerecha((*diccLog));
        			   }
        			   if(fdb > 1 && FactorDeBalanceo((*diccLog)->Izq())<0){
        				   (*diccLog)->Izq(RotarIzquierda((*diccLog)->Izq()));
        				   (*diccLog) = RotarDerecha((*diccLog));
        			   }
        			   if(fdb < -1 && FactorDeBalanceo((*diccLog)->Der())<=0){
        				   (*diccLog) = RotarIzquierda((*diccLog));
        			   }
        			   if(fdb > 1 && FactorDeBalanceo((*diccLog)->Izq())<0){
        				   (*diccLog)->Der(RotarDerecha((*diccLog)->Der()));
        				   (*diccLog) = RotarIzquierda((*diccLog));
        			   }

        		   }
        	   }
        	   return (*diccLog);
           }
           S& SignificadoPrivate(Ab<Nodo>* diccLog, const K& clave) const{
               if(diccLog->Raiz().clave == clave){
            	   return  diccLog->Raiz().significado;
               }
               if(!diccLog->IsNil() &&  diccLog->Raiz().clave > clave){
            	   return SignificadoPrivate(diccLog->Izq(),clave);
               }else{
            	   return SignificadoPrivate(diccLog->Der(),clave);
               }
           }
           bool IsDefinidoPrivate(Ab<Nodo>* diccLog, const K& clave) const{
         		if(diccLog->IsNil()){
         			return false;
         		}
                if(diccLog->Raiz().clave == clave){
         			return true;
         		}
         		if(!diccLog->IsNil() &&  diccLog->Raiz().clave > clave){
         			return IsDefinidoPrivate(diccLog->Izq(),clave);
         		}else{
         			return IsDefinidoPrivate(diccLog->Der(),clave);
         		}
           }

           Ab<Nodo>* DefinirPrivate(Ab<Nodo>** diccLog,const K& p, const S& s){
           	if((*diccLog)->IsNil() || (*diccLog)->Tamano()==0){
           		Nodo nodo;
   				nodo.clave = p;
   				nodo.significado = s;
   				nodo.altura = 1;
   				delete *diccLog;
   				*diccLog = new Ab<Nodo>(new Ab<Nodo>(),nodo,new Ab<Nodo>());
   			}
   			else{
   				Nodo raiz = (*diccLog)->Raiz();
   				if(p<raiz.clave){
   					Ab<Nodo>* nodoIzq = (*diccLog)->Izq();
   					(*diccLog)->Izq(DefinirPrivate(&nodoIzq,p,s));
   				}else{
   					Ab<Nodo>* nodoDer = (*diccLog)->Der();
   					(*diccLog)->Der(DefinirPrivate(&nodoDer,p,s));
   				}

   				(*diccLog)->Raiz().altura = 1 + max(Altura((*diccLog)->Izq()),Altura((*diccLog)->Der()));
   				int fdb = FactorDeBalanceo((*diccLog));
   				if(fdb>1 && p<(*diccLog)->Izq()->Raiz().clave)
   					(*diccLog) = RotarDerecha((*diccLog));
   				if(fdb<-1 && p>(*diccLog)->Der()->Raiz().clave){
   					(*diccLog) = RotarIzquierda((*diccLog));
   				}
   				if(fdb>1 && p>(*diccLog)->Izq()->Raiz().clave){
   					(*diccLog)->Izq(RotarIzquierda((*diccLog)->Izq()));
   					(*diccLog) = RotarDerecha((*diccLog));
   				}
   				if(fdb<-1 && p<(*diccLog)->Der()->Raiz().clave){
   					(*diccLog)->Der(RotarDerecha((*diccLog)->Der()));
   					(*diccLog) = RotarIzquierda((*diccLog));
   				}
   			}
           	return *diccLog;
           }
        
        public:
    	DiccLog<K,S>(){
            _diccLog = new Ab<Nodo>();
        }//Equivalente a Vacio()                    
        ~DiccLog<K,S>(){
            delete this->_diccLog;
        }                                           
                                                    
        bool IsDefinido(const K& p) const;          
                                                    
        void Definir(const K& p, const S& s){
        	assert(!IsDefinido(p));
        	DefinirPrivate(&_diccLog,p,s);
        }

        S& Significado(const K& clave) const;
        void Borrar(const K& clave){
        	BorrarPrivate(&_diccLog,clave);
        }

        S& MinimoSignificado() const{
        	assert(!_diccLog->IsNil());
        	return Minimo(_diccLog)->Raiz().significado;
        }
        Nat CantClaves() const{
        	return _diccLog->Tamano();
        }

    };

	template<typename K,typename S>
	int DiccLog<K,S>::FactorDeBalanceo(Ab<Nodo> *diccLog){
		if(diccLog->IsNil()){
			return 0;
		}else{
			int alturaIzq =0;
			int alturaDer =0;
			alturaIzq = Altura(diccLog->Izq());
			alturaDer = Altura(diccLog->Der());

			return alturaIzq - alturaDer;
		}
	}

	template<typename K,typename S>
	S& DiccLog<K,S>::Significado(const K& clave) const{
		assert(IsDefinido(clave));
		return SignificadoPrivate(_diccLog,clave);
	}

	template<typename K,typename S>
	bool DiccLog<K,S>::IsDefinido(const K& clave) const{
		return IsDefinidoPrivate(_diccLog,clave);
	}
}



#endif


