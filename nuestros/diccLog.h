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

           Ab<Nodo>* Minimo(Ab<Nodo> *diccLog) const{
				while(!diccLog->Izq()->IsNil()){
					diccLog = diccLog->Izq();
				}
				return diccLog;
           }
           Ab<Nodo>* RotarIzquierda(Ab<Nodo>* diccLog){
         		assert(!diccLog->Der()->IsNil());
        	   	Ab<Nodo>* aux1 = diccLog->Der();
         		Ab<Nodo> aux2 = *aux1->Izq();
         		aux1->Izq(*new Ab<Nodo>(*diccLog));
         		aux1->Izq()->Der(aux2);
         		aux1->Izq()->Raiz().altura =1 + max(Altura(aux1->Izq()->Izq()),Altura(aux1->Izq()->Der()));
         		aux1->Raiz().altura = 1 + max(Altura(aux1->Izq()),Altura(aux1->Der()));
           		return aux1;
           };
           Ab<Nodo>* RotarDerecha(Ab<Nodo>* diccLog){
        	   assert(!diccLog->Izq()->IsNil());
        	   Ab<Nodo>* aux1 = diccLog->Izq();
        	   Ab<Nodo> aux2 = *aux1->Der();
        	   aux1->Der(*new Ab<Nodo>(*diccLog));
        	   aux1->Der()->Izq(aux2);
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

           void BorrarPrivate(Ab<Nodo>& diccLog,const K& clave){
        	   if(!diccLog.IsNil()){
        		   if(clave < diccLog.Raiz().clave){
        			   BorrarPrivate(*diccLog.Izq(),clave);
        		   }else if(clave > diccLog.Raiz().clave){
        			   BorrarPrivate(*diccLog.Der(),clave);
        		   }else{
        			   if(diccLog.Izq()->IsNil() || diccLog.Der()->IsNil()){
        				   Ab<Nodo>* temp = (!diccLog.Izq()->IsNil())?diccLog.Izq():diccLog.Der();
        				   if(temp->IsNil()){
        					   *temp = diccLog;
        					   diccLog = Ab<Nodo>();
        				   }else{
        					 //  delete &diccLog;
        					//   diccLog = Ab<Nodo>();
        					   diccLog = *temp;
        				   }
        				   delete temp;
        			   }
        			   else{
        				   Ab<Nodo>* temp = Minimo(diccLog.Der());
        				   diccLog.Raiz().clave=temp->Raiz().clave;
        				   diccLog.Raiz().significado=temp->Raiz().significado;
        				   BorrarPrivate(*diccLog.Der(),temp->Raiz().clave);
        			   }
        		   }
        		   if(diccLog.Tamano()>0){
        			   diccLog.Raiz().altura = 1 + max(Altura(diccLog.Izq()),Altura(diccLog.Der()));
        			   int fdb = FactorDeBalanceo(&diccLog);
        			   if(fdb > 1 && FactorDeBalanceo(diccLog.Izq())>=0){
        				   diccLog = *RotarDerecha(&diccLog);
        			   }
        			   if(fdb > 1 && FactorDeBalanceo(diccLog.Izq())<0){
        			   	   diccLog.Izq(*RotarIzquierda(diccLog.Izq()));
        			   	   diccLog = *RotarDerecha(&diccLog);
        			   }
        			   if(fdb < -1 && FactorDeBalanceo(diccLog.Der())<=0){
        			       diccLog = *RotarIzquierda(&diccLog);
        			   }
        			   if(fdb > 1 && FactorDeBalanceo(diccLog.Izq())<0){
        				   diccLog.Der(*RotarDerecha(diccLog.Der()));
        				   diccLog = *RotarIzquierda(&diccLog);
        			   }

        		   }
        	   }
           }


           void DefinirPrivate(Ab<Nodo>& diccLog,const K& p, const S& s){
           	if(diccLog.IsNil() || diccLog.Tamano()==0){
           		Nodo nodo;
   				nodo.clave = p;
   				nodo.significado = s;
   				nodo.altura = 1;
   				diccLog = Ab<Nodo>(new Ab<Nodo>(),nodo,new Ab<Nodo>());
   		/*		if(_diccLog->IsNil()){
   					delete _diccLog;
   					_diccLog = &diccLog;
   					delete &diccLog;
   				}*/

   			}
   			else{
   				Nodo raiz = diccLog.Raiz();
   				if(p<raiz.clave){
   					DefinirPrivate(*diccLog.Izq(),p,s);
   				}else{
   					DefinirPrivate(*diccLog.Der(),p,s);
   				}

   				diccLog.Raiz().altura = 1 + max(Altura(diccLog.Izq()),Altura(diccLog.Der()));
   				int fdb = FactorDeBalanceo(&diccLog);
   				if(fdb>1 && p<diccLog.Izq()->Raiz().clave)
   					diccLog = *RotarDerecha(&diccLog);
   				if(fdb<-1 && p>diccLog.Der()->Raiz().clave)
   					diccLog = *RotarIzquierda(&diccLog);
   				if(fdb>1 && p>diccLog.Izq()->Raiz().clave){
   					diccLog.Izq(*RotarIzquierda(diccLog.Izq()));
   					diccLog = *RotarDerecha(&diccLog);
   				}
   				if(fdb<-1 && p<diccLog.Der()->Raiz().clave){
   					diccLog.Der(*RotarDerecha(diccLog.Der()));
   					diccLog = *RotarIzquierda(&diccLog);
   				}
   			/*	if(diccLog.Raiz().clave==2 && !diccLog.Izq()->IsNil() && !diccLog.Der()->IsNil()){
   					cout <<"ASSERTEANDO..."<<endl;
   					assert(diccLog.Raiz().clave==2);
   					assert(diccLog.Izq()->Raiz().clave==1);
   					assert(diccLog.Der()->Raiz().clave==3);
   					assert(diccLog.Der()->Izq()->IsNil());
   					assert(diccLog.Der()->Der()->IsNil());
   					assert(diccLog.Izq()->Izq()->IsNil());
   					assert(diccLog.Izq()->Der()->IsNil());
   				}*/
   			//	cout<<"No Soy nil"<<endl;
   			}

           }
        
        public:
    	DiccLog<K,S>(){
            _diccLog = new Ab<Nodo>();
        }//Equivalente a Vacio()                    
        ~DiccLog<K,S>(){                            
            //cout<<"destructor"<<endl;               
            delete this->_diccLog;
        }                                           
                                                    
        bool IsDefinido(const K& p) const;          
                                                    
        void Definir(const K& p, const S& s){
      //  	if(&_diccLog==NULL)
        //		delete _diccLog;//TODO. OJO CON ESTA LINEA! Esta asi porque si estoy parado, vengo de haber sido construido sin parametros

        	DefinirPrivate(*_diccLog,p,s);
        }

        S& Significado(const K& clave) const;
        void Borrar(const K& clave){
        	BorrarPrivate(*_diccLog,clave);
        }

        S& MinimoSignificado() const{
        	return Minimo(_diccLog)->Raiz().significado;
        }
        Nat CantClaves() const{
        	return _diccLog->Tamano();
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

        Ab<Nodo> *_diccLog;
            

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
		return SignificadoPrivate(_diccLog,clave);
	}

	template<typename K,typename S>
	bool DiccLog<K,S>::IsDefinido(const K& clave) const{
		return IsDefinidoPrivate(_diccLog,clave);
	}
}



#endif


