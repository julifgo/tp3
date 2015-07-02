#include <iostream>
#include <string>
#include "red.h"
#include "../aed2.h"
using namespace aed2;
using namespace std;

namespace dcnet{
	Red::Red(){
		/*estr.computadoras;
		estr.vecinos;
		estr.usaInterfaz;
		estr.interfaz;
		estr.caminos;
		estr.caminosMasCortos;*/ //TODO. LEA, SOLUCIONA ESTO.
	}
	Red::Red(const Red& otra){
		estr.caminos=otra.estr.caminos;
	}
	void Red::AgCompu(const Compu& compu){
		Lista<Compu>::Iterador it = estr.computadoras.CrearIt();
		it.AgregarComoSiguiente(compu);
		Conj<Interfaz> conjInter = compu.Interfaces();
		//HACER MAX
		Arreglo<bool> arr(3);
		estr.usaInterfaz.definir(compu.Ip(),arr);
		DiccString<Nat> diccInterfaz;
		estr.interfaz.definir(compu.Ip(),diccInterfaz);
		Conj<Compu> conjVecinos;
		estr.vecinos.definir(compu.Ip(),conjVecinos);
		DiccString<Conj<Lista<Compu> > > caminosCortos;
		estr.caminosMasCortos.definir(compu.Ip(),caminosCortos);
	}

	Lista<Compu> Red::Computadoras(){
		return estr.computadoras;
	}

	bool Red::Conectadas(const Compu& c1,const Compu& c2){

		Conj<Compu> conjVecinos = *estr.vecinos.obtener(c1.Ip());
		return conjVecinos.Pertenece(c2);

	}
	const Red& Red::operator=(const Red& otra){
		return otra;
	}
	



}
