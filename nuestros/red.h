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
			DiccString<Vector<bool> > usaInterfaz;
			DiccString<DiccString<Nat> > interfaz;
			Conj<Lista<Compu> > caminos;
		};
		estr estr;

	public:
		Red();
		Red(const Red& otra);
		~Red();
  		bool operator==(const Red& otra);
	};
}
#endif
