/*
/ Desc: Clase para representar una computadora
/ Author: Grupo 17, AED2, 1C, 2015
/
*/

//PASAR IMPLEMENTACIONES A CPP

#ifndef DC_COMPU_H_
#define DC_COMPU_H_

#include <ostream>
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

		estr estr;

	public:
		Compu(const IP ip);//Equivalente en TP a operacion Crear(ip: ip)
		Compu(const Compu& otra);/// Crea por copia una compu (operación Copiar())
		~Compu();
		const IP Ip() const;
		const Conj<Interfaz>& Interfaces() const;
		void AgInterfaz(const Interfaz interfaz);
		bool operator==(const Compu& otra);/// Operacion de igualdad entre dos compus

  	
	};
}
#endif
