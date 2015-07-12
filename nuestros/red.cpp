#include <iostream>
#include <string>
#include "red.h"
#include "../aed2.h"
using namespace aed2;
using namespace std;

namespace dcnet{

	//Constructores ----------------------------------

	Red::Red() { }

	//Destructor -------------------------------------

	Red::~Red() { }

	//Getters ----------------------------------------

	Lista<Compu> Red::Computadoras() const {
		return this->computadoras;
	}

	bool Red::Conectadas(const Compu& c1,const Compu& c2) {
		assert( Esta( Computadoras(), c1 ) );
		assert( Esta( Computadoras(), c2 ) );
		
		return this->vecinos.obtener(c1.Ip())->Pertenece(c2);
	}
	
	Interfaz& Red::InterfazUsada(const Compu& c1,const Compu& c2) {
		assert( Conectadas(c1, c2) );

		return *this->interfaz.obtener( c1.Ip() )->obtener( c2.Ip() );
	}

	Conj<Compu> Red::Vecinos(const Compu& c1) {
		assert( Esta( Computadoras(), c1 ) );

		return *this->vecinos.obtener(c1.Ip());
	}

	bool Red::UsaInterfaz(const Compu& c1,Nat i) {
		assert( Esta( Computadoras(), c1 ) );
		assert( c1.Interfaces().Pertenece(i) );

		return this->usaInterfaz.obtener(c1.Ip())->operator [](i);
	}

	bool Red::HayCamino(const Compu& c1,const Compu& c2) {
		assert( Esta( Computadoras(), c1 ) );
		assert( Esta( Computadoras(), c2 ) );

		return ! this->caminosMasCortos.obtener(c1.Ip())->obtener(c2.Ip())->EsVacio();
	}

	Conj<Lista<Compu> > Red::CaminosMin(const Compu& c1,const Compu& c2) {
		assert( Esta( Computadoras(), c1 ) );
		assert( Esta( Computadoras(), c2 ) );
		assert( HayCamino(c1, c2) );

		return *(this->caminosMasCortos.obtener(c1.Ip()))->obtener(c2.Ip());
	}
	
	//Setters ----------------------------------------

	void Red::AgCompu(const Compu& compu) {
		assert(!this->vecinos.definido(compu.Ip()));

		Lista<Compu>::Iterador it = this->computadoras.CrearItUlt();
		it.AgregarComoSiguiente( compu );


		//cout << "computadoras de red " << this->computadoras << endl;

		Arreglo<bool> arr = ArmarArreglo( compu.Interfaces() );

		this->usaInterfaz.definir(compu.Ip(),arr);
		DiccString<Nat> diccInterfaz;
		this->interfaz.definir(compu.Ip(),diccInterfaz);
		Conj<Compu> conjVecinos;
		this->vecinos.definir(compu.Ip(),conjVecinos);
		DiccString<Conj<Lista<Compu> > > caminosCortos;
		this->caminosMasCortos.definir(compu.Ip(),caminosCortos);
	}


	void Red::Conectar(const Compu& c1,const Compu& c2,Nat i1, Nat i2) {
		assert( this->vecinos.definido(c1.Ip()) && this->vecinos.definido(c2.Ip()) );
		assert( Esta( Computadoras(), c1 ) );
		assert( Esta( Computadoras(), c2 ) );
		assert( c1.Interfaces().Pertenece(i1) );
		assert( c2.Interfaces().Pertenece(i2) );
		assert( !UsaInterfaz(c1, i1) );
		assert( !UsaInterfaz(c2, i2) );

		this->vecinos.obtener(c1.Ip())->AgregarRapido(c2);
		this->vecinos.obtener(c2.Ip())->AgregarRapido(c1);
		this->usaInterfaz.obtener(c1.Ip())->operator [](i1) = true;
		this->usaInterfaz.obtener(c2.Ip())->operator [](i2) = true;
		this->interfaz.obtener(c1.Ip())->definir(c2.Ip(),i1);
		this->interfaz.obtener(c2.Ip())->definir(c1.Ip(),i2);

		ActualizarCaminos(c1, c2);

		//Actualiza todos los caminos posibles sobre todas las computadoras en el diccionario de caminos màs cortos
		Lista<Compu>::const_Iterador it1 = this->computadoras.CrearIt();
		Lista<Compu>::const_Iterador it2 = this->computadoras.CrearIt();

		while(it1.HaySiguiente()) {
			while(it2.HaySiguiente()) {
				ActualizarCaminosMasCortos(it1.Siguiente(), it2.Siguiente());
				it2.Avanzar();
			}
			it2 = this->computadoras.CrearIt();
			it1.Avanzar();
		}
	}

	Interfaz Red::Max(const Conj<Interfaz>& conj) const {
		assert(conj.Cardinal() > 0);

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

	Arreglo<bool> Red::ArmarArreglo(const Conj<Interfaz>& conj) const {
		
		if(conj.Cardinal()==0){
			return Arreglo<bool>(0);
		}

		Interfaz max = Max(conj);
		Arreglo<bool> arr(max+1);
		Nat i = 0;
		
		while (i<=max){
			arr.Definir(i,false);
			i++;
		}

		return arr;
	}

	//operaciones privadas de caminos auxiliares

	void Red::ActualizarCaminos(const Compu& pc1, const Compu& pc2) {
		Conj<Lista<Compu> >& caminos = this->caminos;
		Conj<Lista<Compu> >& caminosQueEmpiezanConpc1 = CaminosQueEmpiezanConPcx(caminos, pc1);
		Conj<Lista<Compu> >& caminosQueEmpiezanConpc2 = CaminosQueEmpiezanConPcx(caminos, pc2);

		if(caminosQueEmpiezanConpc1.EsVacio()) {
			Lista<Compu> aux;
			aux.AgregarAtras(pc1);
			caminos.AgregarRapido( aux );
			caminosQueEmpiezanConpc1.AgregarRapido( aux );
		}

		if(caminosQueEmpiezanConpc2.EsVacio()) {
			Lista<Compu> aux;
			aux.AgregarAtras(pc2);
			caminos.AgregarRapido( aux );
			caminosQueEmpiezanConpc2.AgregarRapido( aux );
		}

		Conj<Lista<Compu> >& caminosQueTerminanConpc1 = CaminosQueTerminanConPcx(caminos, pc1);
		Conj<Lista<Compu> >::Iterador itCaminosQueEmpiezanConpc2 = caminosQueEmpiezanConpc2.CrearIt();
		Conj<Lista<Compu> >::Iterador itCaminosQueTerminanConpc1 = caminosQueTerminanConpc1.CrearIt();

		while(itCaminosQueTerminanConpc1.HaySiguiente()) {
			while(itCaminosQueEmpiezanConpc2.HaySiguiente()) {
				if(!HayInterseccionDeCaminos(itCaminosQueTerminanConpc1.Siguiente(), itCaminosQueEmpiezanConpc2.Siguiente())) {
					Lista<Compu>& nuevoCamino = Concatenar( itCaminosQueTerminanConpc1.Siguiente(), itCaminosQueEmpiezanConpc2.Siguiente() );
					Lista<Compu> copiaNuevoCamino(nuevoCamino);
					Lista<Compu>& nuevoCaminoInvertido = Reverso( copiaNuevoCamino );
					caminos.AgregarRapido(nuevoCamino);
					caminos.AgregarRapido(nuevoCaminoInvertido);
					delete &nuevoCaminoInvertido;
					delete &nuevoCamino;
				}
				itCaminosQueEmpiezanConpc2.Avanzar();
			}
			itCaminosQueEmpiezanConpc2 = caminosQueEmpiezanConpc2.CrearIt();
			itCaminosQueTerminanConpc1.Avanzar();
		}

		delete &caminosQueEmpiezanConpc1;
		delete &caminosQueEmpiezanConpc2;
		delete &caminosQueTerminanConpc1;
	}

	void Red::ActualizarCaminosMasCortos(const Compu& pc1, const Compu& pc2) {
		Conj<Lista<Compu> >& aux = CaminosQueTerminanConPcx(this->caminos, pc2);
		Conj<Lista<Compu> >& caminosRes = CaminosQueEmpiezanConPcx(aux, pc1);
 		Conj<Lista<Compu> > caminosAAgregar;

		Conj<Lista<Compu> >::Iterador itConjCamino = caminosRes.CrearIt();

		if(itConjCamino.HaySiguiente()) {

			Nat cantidadDeComputadorasEnCaminoMinimo = itConjCamino.Siguiente().Longitud();
			while(itConjCamino.HaySiguiente()) {
				if(cantidadDeComputadorasEnCaminoMinimo > itConjCamino.Siguiente().Longitud()) {
					cantidadDeComputadorasEnCaminoMinimo = itConjCamino.Siguiente().Longitud();
				}
				itConjCamino.Avanzar();
			}

			while(itConjCamino.HayAnterior()) {
				if(cantidadDeComputadorasEnCaminoMinimo == itConjCamino.Anterior().Longitud()) {
					caminosAAgregar.AgregarRapido(itConjCamino.Anterior());
				}
				itConjCamino.Retroceder();
			}
			
			if(this->caminosMasCortos.definido(pc1.Ip())){
				this->caminosMasCortos.obtener(pc1.Ip())->definir(pc2.Ip(), caminosAAgregar);
			}
			else{
				DiccString<Conj<Lista<Compu> > > hasta;	
				hasta.definir( pc2.Ip(), caminosAAgregar );
				this->caminosMasCortos.definir( pc1.Ip(), hasta );
			}
		}
		
		delete &caminosRes;
		delete &aux;
	}

	Conj<Lista<Compu> >& Red::CaminosQueEmpiezanConPcx(const Conj<Lista<Compu> >& caminos, const Compu& pcx) const {
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
	
	Conj<Lista<Compu> >& Red::CaminosQueTerminanConPcx(const Conj<Lista<Compu> >& caminos, const Compu& pcx) const {
		Conj<Lista<Compu> >* res = new Conj<Lista<Compu> >();
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
	
	bool Red::HayInterseccionDeCaminos(const Lista<Compu>& camino1,const Lista<Compu>& camino2) const {
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
	
	Lista<Compu>& Red::Concatenar(const Lista<Compu>& camino1, const Lista<Compu>& camino2) const {
		Lista<Compu>* res = new Lista<Compu>;
		Lista<Compu>::const_Iterador it1 = camino1.CrearIt();
		Lista<Compu>::const_Iterador it2 = camino2.CrearIt();
		while( it1.HaySiguiente() ) {
			res->AgregarAtras(it1.Siguiente());
			it1.Avanzar();
		}
		while( it2.HaySiguiente() ) {
			res->AgregarAtras(it2.Siguiente());
			it2.Avanzar();
		}
		return *res;
	}
	
	Lista<Compu>& Red::Reverso(const Lista<Compu>& camino) const {
		Lista<Compu>* arr = new Lista<Compu>();
		Lista<Compu>::const_Iterador it = camino.CrearItUlt();
		while( it.HayAnterior() ) {
			arr->AgregarAtras(it.Anterior());
			it.Retroceder();
		}
		return *arr;
	}

	//otras operaciones privadas
	bool Red::Esta (const Lista<Compu>& compus, const Compu& c) const {
		bool pertence = false;
		Lista<Compu>::const_Iterador it = compus.CrearIt();
		while(it.HaySiguiente() && !pertence) {
			pertence = ( it.Siguiente() == c );
			it.Avanzar();
		}
		return pertence;
	}

}