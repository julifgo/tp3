#include <iostream>
#include "red.h"
using namespace aed2;

namespace dcnet{
	Red::Red(){
		estr.computadoras = Lista<Compu>();
//esto rompe	estr.vecinos = DiccString<Conj<Compu> >();
//		estr.usaInterfaz = DiccString<Vector<bool> >();
//		estr.interfaz = DiccString<DiccString<Nat> >();
//		estr.caminos = Conj<Lista<Compu> >();
//		estr.caminosMasCortos = DiccString<DiccString<Conj<Lista<Compu> > > >();
	}
	Red::Red(const Red& otra){
		estr.caminos=otra.estr.caminos;
	}

}
