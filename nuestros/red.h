#ifndef DC_RED_H_
#define DC_RED_H_

#include <ostream>
using namespace aed2;
namespace dcnet{
	typedef String IP;

	class Red{
	private:
		struct estr{
			Lista<Compu> computadoras;
			DiccString<Conj<Compu>> vecinos;
			DiccString<DiccString<Conj<Lista<Compu>>>> caminosMasCortos;
			DiccString<Vector<bool>> usaInterfaz;
			DiccString<DiccString<Nat>> interfaz;
			Conj<Lista<Compu>> caminos;
		};
		estr estr;


	public:
		Red(){
		}

		Red(const Red& otra){
  		}

		~Red(){
			//TODO. Implementar
		}

		/// Operacion de igualdad entre dos compus
  		bool operator==(const Red& otra){
  		}


	};
}
#endif
