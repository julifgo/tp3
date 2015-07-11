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
		
		//operaciones privadas de caminos auxiliares

		//actualizarCaminos
		void ActualizarCaminos(const Compu&, const Compu&); //no lleva const al final porque recibe red como in/out

		//actualizarCaminosMasCortos
		void ActualizarCaminosMasCortos(const Compu&, const Compu&);

		//caminosQueEmpiezanConPcx
		Conj<Lista<Compu> >& CaminosQueEmpiezanConPcx(const Conj<Lista<Compu> >&, const Compu&) const;
		
		//caminosQueTerminanConPcx
		Conj<Lista<Compu> >& CaminosQueTerminanConPcx(const Conj<Lista<Compu> >&, const Compu&) const;
		
		//hayInterseccionDeCaminos
		bool HayInterseccionDeCaminos(const Lista<Compu>&,const Lista<Compu>&) const;
		
		//concatenar
		Lista<Compu>& Concatenar(const Lista<Compu>&, const Lista<Compu>&) const;
		
		//reverso
		Lista<Compu>& Reverso(const Lista<Compu>&) const;

		//otras operaciones privadas

		bool Esta (const Lista<Compu>&, const Compu&) const;

	public:
		Red();
		~Red();
		bool operator==(const Red& otra);
		//const Red& operator=(const Red& otra); //TODO. Revisar la necesidad de esto. (Por ahora solo se usa en el constructor de dcnet. Tal vez bastaria con guardar solo referencias)
  		void AgCompu(const Compu& compu);
  		Lista<Compu> Computadoras() const;
  		bool Conectadas(const Compu& c1,const Compu& c2);
  		Interfaz& InterfazUsada(const Compu& c1,const Compu& c2);
  		Conj<Compu> Vecinos(const Compu& c1);
  		bool UsaInterfaz(const Compu& c1,Nat i);
  		bool HayCamino(const Compu& c1, const Compu& c2);
  		Conj<Lista<Compu> > CaminosMin(const Compu& c1, const Compu& c2);
  		void Conectar(const Compu& c1, const Compu& c2,Nat i1,Nat i2);
	};
}
#endif
