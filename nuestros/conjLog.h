/*
/CONJUNTO LOGARITMICO
/ Desc: Clase para representar un conjunto con operaciones basicas en tiempo logaritmico
/ Author: Grupo 17, AED2, 1C, 2015
/
*/
#ifndef CONJLOG_H
#define CONJLOG_H

#include "../aed2.h"
#include "diccLog.h"

namespace dcnet {

	template<typename T>
	class ConjLog{
	public:
		ConjLog<T>(){
			//cout<<"Creando conjLog"<<endl;
		}
		~ConjLog<T>(){

		}

		void Definir(T& valor){
			conj.Definir(valor,valor);
		}

		void Borrar(const T& valor){
			if(conj.IsDefinido(valor)){
				conj.Borrar(valor);
			}
		}

		bool Pertenece(const T& valor) const{
			return conj.IsDefinido(valor);
		}

		const Nat Cardinal(){
			return conj.CantClaves();
		}

		T& Minimo() const{
			return conj.MinimoSignificado();
		}

	private:
		DiccLog<T,T> conj;
	};

}

#endif