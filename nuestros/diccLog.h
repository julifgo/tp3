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
      //  	if(&_diccLog==NULL)
        //		delete _diccLog;//TODO. OJO CON ESTA LINEA! Esta asi porque si estoy parado, vengo de haber sido construido sin parametros

        	DefinirPrivate(*_diccLog,p,s);
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
        Ab<Nodo>* RotarIzquierda(Ab<Nodo>& diccLog){
      		Ab<Nodo>* aux1 = diccLog.Der();
        	Ab<Nodo>* aux2 = aux1->Izq();
        	aux1->Izq(diccLog);
        	diccLog.Der(aux2);
        	diccLog.Raiz().altura =1 + max(Altura(diccLog.Izq()),Altura(diccLog.Der()));
        	aux1->Raiz().altura = 1 + max(Altura(aux1->Izq()),Altura(aux1->Der()));
        	return aux1;
        };
        Ab<Nodo>& RotarDerecha(Ab<Nodo>& diccLog){
        	Ab<Nodo>* aux1 = diccLog.Izq();
        	Ab<Nodo>* aux2 = aux1->Der();
        	aux1->Der(&diccLog);
        	diccLog.Izq(*aux2);
        	diccLog.Raiz().altura = 1 + max(Altura(diccLog.Izq()),Altura(diccLog.Der()));
        	aux1->Raiz().altura = 1 + max(Altura(aux1->Izq()),Altura(aux1->Der()));
        	return *aux1;
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
					diccLog = RotarDerecha(diccLog);
				if(fdb<-1 && p>diccLog.Der()->Raiz().clave)
					diccLog = *RotarIzquierda(diccLog);
				if(fdb>1 && p>diccLog.Izq()->Raiz().clave){
					diccLog = *RotarIzquierda(*diccLog.Izq());
					diccLog = RotarDerecha(diccLog);
				}
				if(fdb<-1 && p<diccLog.Der()->Raiz().clave){
					diccLog = RotarDerecha(*diccLog.Der());
					diccLog = *RotarIzquierda(diccLog);
				}
				cout<<"No Soy nil"<<endl;
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

}



#endif


