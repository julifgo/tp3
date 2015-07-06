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

	void Red::Conectar(const Compu& c1,const Compu& c2,Nat i1, Nat i2){
		estr.vecinos.obtener(c1.Ip())->AgregarRapido(c2);
		estr.vecinos.obtener(c2.Ip())->AgregarRapido(c1);
		estr.usaInterfaz.obtener(c1.Ip())->operator [](i1) = true;
		estr.usaInterfaz.obtener(c2.Ip())->operator [](i2) = true;
		DiccString<Nat> interfaz1 = *estr.interfaz.obtener(c1.Ip());
		interfaz1.definir(c2.Ip(),i1);
		DiccString<Nat> interfaz2 = *estr.interfaz.obtener(c2.Ip());
		interfaz2.definir(c1.Ip(),i2);
		//TODO: @Luis: llamar a las funciones de actualizarCaminos
		ActualizarCaminos(c1, c2);
		//estr.caminosMasCortos = ActualizarCaminosMasCortos(c1, c2);
		
		cout << estr.caminos << endl;
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
		return arr;
	}

	//operaciones privadas de caminos auxiliares (Luis) ---------
	//dejo todos los tipos que se devuelven sin const porque no estoy seguro en que momento se pueden llegar a utilizar

	//actualizarCaminos
	void Red::ActualizarCaminos(const Compu pc1, const Compu pc2) {
		Conj<Lista<Compu> > caminos = this->estr.caminos;

		if(CaminosQueEmpiezanConPcx(caminos, pc1).EsVacio()) {
			Lista<Compu>* aux = new Lista<Compu>();
			aux->AgregarAtras(pc1);
			caminos.AgregarRapido( *aux );
		}

		if(CaminosQueEmpiezanConPcx(caminos, pc2).EsVacio()) {
			Lista<Compu>* aux = new Lista<Compu>();
			aux->AgregarAtras(pc2);
			caminos.AgregarRapido( *aux );
		}

		Conj<Lista<Compu> > caminosQueTerminanConpc1 = CaminosQueTerminanConPcx(caminos, pc1);
		Conj<Lista<Compu> > caminosQueEmpiezanConpc2 = CaminosQueEmpiezanConPcx(caminos, pc2);

		Conj<Lista<Compu> >::Iterador itCaminosQueEmpiezanConpc2 = caminosQueEmpiezanConpc2.CrearIt();
		Conj<Lista<Compu> >::Iterador itCaminosQueTerminanConpc1 = caminosQueTerminanConpc1.CrearIt();

		while(itCaminosQueTerminanConpc1.HaySiguiente()) {
			while(itCaminosQueEmpiezanConpc2.HaySiguiente()) {
				if(HayInterseccionDeCaminos(itCaminosQueTerminanConpc1.Siguiente(), itCaminosQueEmpiezanConpc2.Siguiente())) {
					Lista<Compu> nuevoCamino = Lista<Compu>();
					Concatenar( itCaminosQueTerminanConpc1.Siguiente(), itCaminosQueEmpiezanConpc2.Siguiente() );
					Concatenar(nuevoCamino, itCaminosQueTerminanConpc1.Siguiente() );
					caminos.AgregarRapido(nuevoCamino);
					caminos.AgregarRapido(Reverso( *(new Lista<Compu>(nuevoCamino)) ));
				}
				itCaminosQueEmpiezanConpc2.Avanzar();
			}
			itCaminosQueTerminanConpc1.Avanzar();
		}

	}

	//actualizarCaminosMasCortos
	Conj<Lista<Compu> > Red::ActualizarCaminosMasCortos(const Compu pc1, const Compu pc2) const {
		Conj<Lista<Compu> > caminosRes = CaminosQueEmpiezanConPcx(CaminosQueTerminanConPcx(this->estr.caminos, pc2), pc1);
		Conj<Lista<Compu> >::Iterador itConjCamino = caminosRes.CrearIt();
		Nat cantidadDeComputadorasEnCaminoMinimo = itConjCamino.Siguiente().Longitud();
		while(itConjCamino.HaySiguiente()) {
			if(cantidadDeComputadorasEnCaminoMinimo > itConjCamino.Siguiente().Longitud()) {
				cantidadDeComputadorasEnCaminoMinimo = itConjCamino.Siguiente().Longitud();
			}
			itConjCamino.Avanzar();
		}

		while(itConjCamino.HayAnterior()) {
			if(cantidadDeComputadorasEnCaminoMinimo != itConjCamino.Anterior().Longitud()) {
				itConjCamino.EliminarAnterior();
			}
			itConjCamino.Retroceder();
		}
		return caminosRes;
	}

	//caminosQueEmpiezanConPcx
	Conj<Lista<Compu> > Red::CaminosQueEmpiezanConPcx(const Conj<Lista<Compu> > caminos, const Compu pcx) const {
		Conj<Lista<Compu> >* res = new Conj<Lista<Compu> >();
		Conj<Lista<Compu> >::const_Iterador it = caminos.CrearIt();
		while(it.HaySiguiente()) {
			if(it.Siguiente()[0] == pcx) {
				res->AgregarRapido(it.Siguiente());
			}
			it.Avanzar();
		}
		return *res;
	}
	
	//caminosQueTerminanConPcx
	Conj<Lista<Compu> > Red::CaminosQueTerminanConPcx(const Conj<Lista<Compu> > caminos, const Compu pcx) const {
		Conj<Lista<Compu> >* res = new Conj<Lista<Compu> >(); //creo una lista de compus en el heap
		Conj<Lista<Compu> >::const_Iterador it = caminos.CrearIt();
		while(it.HaySiguiente()) {
			Lista<Compu>::const_Iterador itUlt = it.Siguiente().CrearItUlt();
			if(itUlt.Anterior() == pcx) {
				res->AgregarRapido(it.Siguiente());
			}
			it.Avanzar();
		}
		return *res;
	}
	
	//hayInterseccionDeCaminos
	bool Red::HayInterseccionDeCaminos(const Lista<Compu> camino1,const Lista<Compu> camino2) const {
		bool hay = false;
		Lista<Compu>::const_Iterador it1 = camino1.CrearIt();
		Lista<Compu>::const_Iterador it2 = camino2.CrearIt();
		while( it1.HaySiguiente() && !hay ) {
			while( it2.HaySiguiente() && !hay ) {
				hay = (it1.Siguiente() == it2.Siguiente());
				it2.Avanzar();
			}
			it1.Avanzar();
		}
		return hay;
	}
	
	//concatenar
	void Red::Concatenar(Lista<Compu> camino1, const Lista<Compu> camino2) const {
		Lista<Compu>::const_Iterador it = camino2.CrearIt(); //voy a iterar camino2
		while( it.HaySiguiente() ) {
			camino1.AgregarAtras(it.Siguiente()); //agrego la referencia a camino1 (es it.Siguiente() es una referencia porque camino2 es una lista de tipos no primitivos)
			it.Avanzar(); //avanzo
		}
	}
	
	//reverso
	Lista<Compu> Red::Reverso(const Lista<Compu> camino) const {
		Lista<Compu>* arr = new Lista<Compu>();	//se crea una lista de computadoras en el heap
		Lista<Compu>::const_Iterador it = camino.CrearItUlt(); //voy a iterar camino del último al primero
		while( it.HayAnterior() ) {
			arr->AgregarAdelante(it.Anterior()); //como camino es una lista de compus, cada compu es un tipo no primitivo, por lo que it.Anterior es una referencia
			it.Retroceder(); //retrocedo
		}
		return *arr; //devuelvo la lista que tengo en el heap (se devuelve una referencia porque es un tipo no primitivo)
	}



}
