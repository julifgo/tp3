#ifndef DC_RED_H_
#define DC_RED_H_

#include <iostream>
#include "../aed2.h"
#include "compu.h"

using namespace aed2;

namespace dcnet{
	typedef String IP;

	class Red{
	private:
		struct estr{
			Lista<Compu> computadoras;
			DiccString<Conj<Compu> > vecinos;
			DiccString<DiccString<Conj<Lista<Compu> > > > caminosMasCortos;
			DiccString<Arreglo<bool> > usaInterfaz;
			DiccString<DiccString<Nat> > interfaz;
			Conj<Lista<Compu> > caminos;
		};
		estr estr;
		Interfaz Max(const Conj<Interfaz>& conj) const;
		Arreglo<bool> ArmarArreglo(const Conj<Interfaz>& conj) const;
		
		//operaciones privadas de caminos auxiliares (Luis) ---------

		//actualizarCaminos
		void ActualizarCaminos(const Compu pc1, const Compu pc2); //no lleva const al final porque recibe red como in/out

		//actualizarCaminosMasCortos
		Conj<Lista<Compu> > ActualizarCaminosMasCortos(const Compu pc1, const Compu pc2) const;

		//caminosQueEmpiezanConPcx
		Conj<Lista<Compu> > CaminosQueEmpiezanConPcx(const Conj<Lista<Compu> > caminos, const Compu pcx) const;
		
		//caminosQueTerminanConPcx
		Conj<Lista<Compu> > CaminosQueTerminanConPcx(const Conj<Lista<Compu> > caminos, const Compu pcx) const;
		
		//hayInterseccionDeCaminos
		bool HayInterseccionDeCaminos(const Lista<Compu> camino1,const Lista<Compu> camino2) const;
		
		//concatenar
		void Concatenar(Lista<Compu> camino1, const Lista<Compu> camino2) const;
		
		//reverso
		Lista<Compu> Reverso(const Lista<Compu> camino) const;

	public:
		Red();
		Red(const Red& otra);
		//~Red();
		bool operator==(const Red& otra);
		const Red& operator=(const Red& otra); //TODO. Revisar la necesidad de esto. (Por ahora solo se usa en el constructor de dcnet. Tal vez bastaria con guardar solo referencias)
  		void AgCompu(const Compu& compu);
  		Lista<Compu> Computadoras() const;
  		bool Conectadas(const Compu& c1,const Compu& c2);
  		Interfaz InterfazUsada(const Compu& c1,const Compu& c2);
  		Conj<Compu> Vecinos(const Compu& c1);
  		bool UsaInterfaz(const Compu& c1,Nat i);
  		bool HayCamino(const Compu& c1, const Compu& c2);
  		Conj<Lista<Compu> > CaminosMin(const Compu& c1, const Compu& c2);
  		void Conectar(const Compu& c1, const Compu& c2,Nat i1,Nat i2);
	};
}
#endif
