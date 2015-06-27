/*
/ Desc: Clase para representar una computadora
/ Author: Grupo 17, AED2, 1C, 2015
/
*/

#ifndef AED2_CONJ_H_
#define AED2_CONJ_H_

#include <ostream>
#include "../aed2/TiposBasicos.h"
#include "../aed2/Conj.h"
using namespace aed2;
namespace dcnet{
	typedef Nat Interfaz;
	typedef String IP;

	class Compu{
	private:
		struct estr{
			IP ip;
			Conj<Interfaz> interfaces;
		};

	public:
		Compu(const IP ip);
		/// Crea por copia una compu (operación Copiar())
  		Compu(const Compu& otra);
		~Compu();
		const IP Ip() const;
		const Conj<Interfaz>& Interfaces() const; //Se devuelve res como referencia a las interfaces pero no son modificables
		void AgInterfaz(const Interfaz interfaz);
		/// Operacion de igualdad entre dos compus
  		Compu& operator==(const Compu& otra);
	};
}
#endif