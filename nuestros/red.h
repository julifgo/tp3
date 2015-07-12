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

		Lista<Compu> computadoras;

		DiccString<Conj<Compu> > vecinos;
		
		DiccString<DiccString<Conj<Lista<Compu> > > > caminosMasCortos;
		
		DiccString<Arreglo<bool> > usaInterfaz;
		
		DiccString<DiccString<Nat> > interfaz;
		
		Conj<Lista<Compu> > caminos;
		
		Interfaz Max(const Conj<Interfaz>&) const;

		Arreglo<bool> ArmarArreglo(const Conj<Interfaz>&) const;
		
		void ActualizarCaminos(const Compu&, const Compu&);

		void ActualizarCaminosMasCortos(const Compu&, const Compu&);

		Conj<Lista<Compu> >& CaminosQueEmpiezanConPcx(const Conj<Lista<Compu> >&, const Compu&) const;
		
		Conj<Lista<Compu> >& CaminosQueTerminanConPcx(const Conj<Lista<Compu> >&, const Compu&) const;
		
		bool HayInterseccionDeCaminos(const Lista<Compu>&,const Lista<Compu>&) const;
		
		Lista<Compu>& Concatenar(const Lista<Compu>&, const Lista<Compu>&) const;
		
		Lista<Compu>& Reverso(const Lista<Compu>&) const;

		bool Esta (const Lista<Compu>&, const Compu&) const;

	public:

		Red();
		
		~Red();
		
		bool operator==(const Red&);
		
  		void AgCompu(const Compu&);
  		
  		Lista<Compu> Computadoras() const;
  		
  		bool Conectadas(const Compu&, const Compu&);
  		
  		Interfaz& InterfazUsada(const Compu&, const Compu&);
  		
  		Conj<Compu> Vecinos(const Compu&);
  		
  		bool UsaInterfaz(const Compu&,Nat);
  		
  		bool HayCamino(const Compu&, const Compu&);
  		
  		Conj<Lista<Compu> > CaminosMin(const Compu&, const Compu&);
  		
  		void Conectar(const Compu&, const Compu&, Nat&, Nat&);
	
	};
}
#endif
