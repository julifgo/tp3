#include <iostream>
#include <string>
#include "red.h"
#include "../aed2.h"
using namespace aed2;
using namespace std;

namespace dcnet{
	Red::Red(){
	//	estr.computadoras = Lista<Compu>();
	//	estr.vecinos = DiccString<Conj<Compu> >();
	/*	estr.usaInterfaz;
		estr.interfaz;
		estr.caminos;
		estr.caminosMasCortos;*/ //TODO. LEA, SOLUCIONA ESTO.// SOLUCIONADO ASI?
	}
	Red::Red(const Red& otra){
		estr.caminos=otra.estr.caminos;
	}
	void Red::AgCompu(const Compu& compu){
		Lista<Compu>::Iterador it = estr.computadoras.CrearIt();
		it.AgregarComoSiguiente(compu);
		Conj<Interfaz> conjInter = compu.Interfaces();
		Arreglo<bool> arr = ArmarArreglo(conjInter);
		estr.usaInterfaz.definir(compu.Ip(),arr);
		DiccString<Nat> diccInterfaz;
		estr.interfaz.definir(compu.Ip(),diccInterfaz);
		Conj<Compu> conjVecinos;
		estr.vecinos.definir(compu.Ip(),conjVecinos);
		DiccString<Conj<Lista<Compu> > > caminosCortos;
		estr.caminosMasCortos.definir(compu.Ip(),caminosCortos);
	}

	Lista<Compu> Red::Computadoras() const{
		return estr.computadoras;
	}

	bool Red::Conectadas(const Compu& c1,const Compu& c2){

		Conj<Compu> conjVecinos = *estr.vecinos.obtener(c1.Ip());
		return conjVecinos.Pertenece(c2);

	}
	const Red& Red::operator=(const Red& otra){
		return otra;
	}
	
	Interfaz Red::InterfazUsada(const Compu& c1,const Compu& c2){
		Interfaz res = *estr.interfaz.obtener(c1.Ip())->obtener(c2.Ip());
		return res;
	}

	Conj<Compu> Red::Vecinos(const Compu& c1){
		Conj<Compu> res = *estr.vecinos.obtener(c1.Ip());
		return res;
	}

	bool Red::UsaInterfaz(const Compu& c1,Nat i){
		bool res = estr.usaInterfaz.obtener(c1.Ip())->operator [](i);
		return res;
	}

	bool Red::HayCamino(const Compu& c1,const Compu& c2){
		bool res = estr.caminosMasCortos.obtener(c2.Ip())->obtener(c1.Ip())->EsVacio();
		return res;
	}

	Conj<Lista<Compu> > Red::CaminosMin(const Compu& c1,const Compu& c2){
		Conj<Lista<Compu> > res = *estr.caminosMasCortos.obtener(c2.Ip())->obtener(c1.Ip());
		return res;
	}

	Interfaz Red::Max(const Conj<Interfaz>& conj) const{
		Conj<Interfaz>::const_Iterador it = conj.CrearIt();
		Interfaz max = it.Siguiente();
		while (it.HaySiguiente()){
			if(max <= it.Siguiente()){
				max = it.Siguiente();
			}
			it.Avanzar();
		}
		return max;
	}

	Arreglo<bool> Red::ArmarArreglo(const Conj<Interfaz>& conj) const{
		Interfaz max = Max(conj);
		Arreglo<bool> arr(max+1);
		Nat i = 0;
		while (i<=max){
			arr.Definir(i,false);
			i++;
		}
		Conj<Interfaz>::const_Iterador it = conj.CrearIt();
		while (it.HaySiguiente()){
			arr.Definir(it.Siguiente(),true);
			it.Avanzar();
		}
		return arr;
	}


}
