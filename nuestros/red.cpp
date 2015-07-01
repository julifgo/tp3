#include <iostream>
#include <string>
#include "red.h"
#include "../aed2.h"
using namespace aed2;
using namespace std;

namespace dcnet{
	Red::Red(){
		estr.computadoras;
		estr.vecinos;
		estr.usaInterfaz;
		estr.interfaz;
		estr.caminos;
		estr.caminosMasCortos;
	}
	Red::Red(const Red& otra){
		estr.caminos=otra.estr.caminos;
	}
	void Red::AgCompu(const Compu compu){
		Lista<Compu>::Iterador it = estr.computadoras.CrearIt();
		it.AgregarComoSiguiente(compu);
		//cout << estr.computadoras.Primero().Ip();
		Conj<Interfaz> conjInter = compu.Interfaces();
		//HACER MAX
		Arreglo<bool> arr(3);
		estr.usaInterfaz.definir(compu.Ip(),arr);
	}



}
