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

	public:
		Red();
		Red(const Red& otra);
		//~Red();
		bool operator==(const Red& otra);
		const Red& operator=(const Red& otra); //TODO. Revisar la necesidad de esto. (Por ahora solo se usa en el constructor de dcnet. Tal vez bastaria con guardar solo referencias)
  		void AgCompu(const Compu& compu);
  		Lista<Compu> Computadoras();
  		bool Conectadas(const Compu& c1,const Compu& c2);

	};
}
#endif
